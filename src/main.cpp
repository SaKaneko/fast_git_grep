#include <iostream>
#include <thread>
#include <chrono>
#include "config/ConfigConstants.hpp"
#include "config/ConfigLoader.hpp"

#include "util/ProgressBar.hpp"
#include "util/ArgParser.hpp"
#include "util/ErrorManager.hpp"

#include "core/RepositoryScanner.hpp"
#include "core/ProjectFactory.hpp"
#include "core/BranchSelector/BranchSelectorFactory.hpp"
#include "core/SearchManager/SearchManagerFactory.hpp"

std::string makeHelpMessage(const Config& config) {
  std::ostringstream oss;
  oss << "Usage: fast_git_grep key [options]\n";
  oss << "Options:\n";
  oss << "  --branch_strategy <main|all|latest> Specify branch strategy (default: " << config.getBranchSelectorType()
      << ")\n";
  oss << "  --parallel_strategy <parallel|sequential> Specify parallel strategy (default: "
      << config.getSearchManagerType() << ")\n";
  oss << "  --excluded_projects <pattern>       Specify patterns to exclude projects by regex (default: ";
  if (!config.getExcludeProjectPatterns().empty())
    oss << config.getExcludeProjectPatterns()[0];
  oss << ")\n";
  oss << "  --excluded_branches <pattern>       Specify patterns to exclude branches by regex (default: ";
  if (!config.getExcludeBranchPatterns().empty())
    oss << config.getExcludeBranchPatterns()[0];
  oss << ")\n";
  oss << "  --debug                             Enable debug mode\n";
  oss << "  --help                              Show this help message\n";
  return oss.str();
}

int main(int argc, char* argv[]) {
  util::ArgParser argParser(argc, argv);
  if (argParser.isDebugMode()) {
    std::cout << "Debug mode is enabled.\n";
    argParser.debugPrint();
    config::debug = true;
  }
  if (argParser.hasFlag("help")) {
    ConfigLoader configLoader;
    auto config = configLoader.loadConfig("/etc/fast_git_grep/ini.config");
    std::cout << config::makeHelpMessage(config);
    return 0;
  }
  ConfigLoader configLoader;
  auto config = configLoader.loadConfig("/etc/fast_git_grep/ini.config");

  // コマンドライン引数の指定で設定ファイルによる設定を上書き
  {
    if (argParser.getOption("branch_strategy") != "") {
      config.setBranchSelectorType(argParser.getOption("branch_strategy"));
    }
    if (argParser.getOption("parallel_strategy") != "") {
      config.setSearchManagerType(argParser.getOption("parallel_strategy"));
    }
    if (argParser.getOption("excluded_projects") != "") {
      config.setExcludeProjectPatterns(argParser.getOption("excluded_projects"));
    }
    if (argParser.getOption("excluded_branches") != "") {
      config.setExcludeBranchPatterns(argParser.getOption("excluded_branches"));
    }
  }

  // 初期状態のエラーチェック
  {
    util::ErrorManager::checkDirectoryReadable(config.getGitlabDataDir());
    util::ErrorManager::checkSingleArgument(argParser.getArgs(), config);
    util::ErrorManager::checkMinArgumentLength(argParser.getArgs(), config::MINIMAL_ARGUMENT_LENGTH, config);
  }
  auto key   = argParser.getArgs()[0];
  auto start = std::chrono::steady_clock::now();
  // ベアリポジトリから探索対象のリポジトリを収集
  std::vector<Project> projects;
  {
    RepositoryScanner scanner;
    auto repos = scanner.listBareRepositories(config.getGitlabDataDir());

    ProjectFactory projectFactory(config.getGitlabDataDir(), config.getHashMapDBFile(), config.getDBTableName(),
                                  config.getDBIndexKey(), config.getDBValueKey());
    for (const auto& repo : repos) {
      if (config::debug) {
        std::cout << "Found bare repository: " << repo.string() << std::endl;
      }
      auto project = projectFactory.createProjectFromDB(repo);
      if (project.isProjectExcluded(config.getExcludeProjectPatterns()))
        continue;
      projects.push_back(project);
    }
  }
  auto point1 = std::chrono::steady_clock::now();
  // 対象のブランチを選択
  {
    auto branch_selector = BranchSelectorFactory::create(config.getBranchSelectorType());
    for (auto& project : projects) {
      branch_selector->selectBranch(project, config.getExcludeBranchPatterns());
      if (config::debug) {
        std::cout << "Project: " << project.name << ", Path: " << project.path << std::endl;
        auto branches = project.getTargetBranches();
        std::cout << "  Target branches: ";
        for (const auto& branch : branches) {
          std::cout << branch << " ";
        }
        std::cout << std::endl;
      }
    }
  }
  double point1_elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(point1 - start).count() / 1000.0;
  std::cout << "Repository scanning elapsed: " << point1_elapsed << " sec" << std::endl;
  SearchManagerFactory search_manager_factory;
  auto search_manager   = search_manager_factory.create(config.getSearchManagerType());
  auto results          = search_manager->runSearch(projects, key);
  auto end              = std::chrono::steady_clock::now();
  double point2_elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - point1).count() / 1000.0;
  std::cout << "runSearch elapsed: " << point2_elapsed << " sec" << std::endl;
  for (const auto& res : results) {
    std::cout << res.toString();
  }
  return 0;
}