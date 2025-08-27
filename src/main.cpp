#include <iostream>
#include <thread>
#include "config/ConfigConstants.hpp"
#include "config/ConfigLoader.hpp"

#include "util/ProgressBar.hpp"
#include "util/ArgParser.hpp"
#include "util/ErrorManager.hpp"

#include "core/RepositoryScanner.hpp"
#include "core/ProjectFactory.hpp"
#include "core/BranchSelector/BranchSelectorFactory.hpp"
#include "core/ParallelSearchManager.hpp"

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

  // 初期状態のエラーチェック
  {
    util::ErrorManager::checkDirectoryReadable(config::GITLAB_DATA_DIR);
  }

  RepositoryScanner scanner;
  auto repos = scanner.listBareRepositories();
  std::vector<Project> projects;
  ProjectFactory projectFactory;
  for (const auto& repo : repos) {
    if (config::debug) {
      std::cout << "Found bare repository: " << repo.string() << std::endl;
    }
    projects.push_back(projectFactory.createProjectFromDB(repo));
  }
  auto branch_selector = BranchSelectorFactory::create("all");
  for (auto& project : projects) {
    branch_selector->selectBranch(project);
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

  ParallelSearchManager search_manager;
  auto results = search_manager.runParallelSearch(projects, "Getting started");
  for (const auto& res : results) {
    std::cout << res.toString();
  }

  return 0;
}