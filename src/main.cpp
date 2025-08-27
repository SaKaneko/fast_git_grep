#include <iostream>
#include <thread>
#include "config/ConfigConstants.hpp"
#include "config/ConfigLoader.hpp"

#include "util/ProgressBar.hpp"
#include "util/ArgParser.hpp"
#include "util/ErrorManager.hpp"

#include "core/RepositoryScanner.hpp"
#include "core/ProjectFactory.hpp"

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
  return 0;
}