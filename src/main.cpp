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
#include "core/ProjectCache.hpp"

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
  std::vector<Project> projects;
  // キャッシュ利用: Config からパス/期限を取得してキャッシュが新しければ読み込む
  std::filesystem::path cache_path;
  if (!config.getCacheFilePath().empty()) {
    cache_path = config.getCacheFilePath();
  }
  else {
    // デフォルトは GitLab データディレクトリ直下の project_cache.bin
    cache_path = std::filesystem::path(config.getGitlabDataDir()) / "project_cache.bin";
  }
  ProjectCache cache(cache_path, ProjectCache::seconds{static_cast<int>(config.getCacheLifetimeSeconds())});
  bool ignore_cache = argParser.hasFlag("r") || argParser.hasFlag("nocache");
  if (ignore_cache) {
    if (config::debug)
      std::cout << "Ignoring project cache due to CLI flag\n";
  }

  bool used_cache = false;
  CacheObj loaded;
  if (!ignore_cache && cache.load(loaded)) {
    if (loaded.branchSelectorType == config.getBranchSelectorType() &&
        loaded.excludeBranchPatterns == config.getExcludeBranchPatterns())
    {
      projects   = std::move(loaded.projects);
      used_cache = true;
      std::cout << "Loaded projects from cache (matched selector+patterns): " << cache_path << std::endl;
      std::cout << "If you want to ignore the cache, use -r or --nocache option." << std::endl;
    }
    else {
      if (config::debug) {
        std::cout << "Cache present but branch selector/patterns differ; ignoring cache\n";
      }
    }
  }

  if (!used_cache) {
    // ベアリポジトリから探索対象のリポジトリを収集
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
  }
  // after branch selection: if we scanned (didn't use cache) and caching not ignored, save cache with selected branches
  if (!ignore_cache && !used_cache) {
    CacheObj to_save;
    to_save.branchSelectorType    = config.getBranchSelectorType();
    to_save.excludeBranchPatterns = config.getExcludeBranchPatterns();
    to_save.projects              = projects;
    if (!cache.save(to_save) && config::debug) {
      std::cerr << "Warning: failed to write project cache: " << cache_path << std::endl;
    }
  }
  auto point1           = std::chrono::steady_clock::now();
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