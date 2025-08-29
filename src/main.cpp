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

int main(int argc, char* argv[]) {
  util::ArgParser argParser(argc, argv);
  if (argParser.isDebugMode()) {
    std::cout << "Debug mode is enabled.\n";
    argParser.debugPrint();
    config::debug = true;
  }
  if (argParser.hasFlag("help")) {
    std::cout << config::HELP_MESSAGE;
    return 0;
  }
  ConfigLoader configLoader;
  auto config = configLoader.loadConfig("/home/ryngo/working/fast_bbbgrep/fast_git_grep/etc/ini.config");

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
    util::ErrorManager::checkSingleArgument(argParser.getArgs());
    util::ErrorManager::checkMinArgumentLength(argParser.getArgs(), config::MINIMAL_ARGUMENT_LENGTH);
  }
  auto key = argParser.getArgs()[0];

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
  SearchManagerFactory search_manager_factory;
  auto search_manager = search_manager_factory.create(config.getSearchManagerType());
  auto start          = std::chrono::steady_clock::now();
  auto results        = search_manager->runSearch(projects, key);
  auto end            = std::chrono::steady_clock::now();
  double elapsed      = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() / 1000.0;
  std::cout << "runSearch elapsed: " << elapsed << " sec" << std::endl;
  for (const auto& res : results) {
    std::cout << res.toString();
  }
  return 0;
}