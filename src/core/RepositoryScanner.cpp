#include "config/ConfigConstants.hpp"
#include "core/RepositoryScanner.hpp"
#include <iostream>
namespace fs = std::filesystem;

// GITLAB_DATA_DIR配下のベアリポジトリ（.gitディレクトリや.gitファイルが存在するディレクトリ）を再帰的にリストアップ
std::vector<fs::path> RepositoryScanner::listBareRepositories(const std::string& baseDir) {
  const int max_depth = 3; // 最大深さ
  std::vector<fs::path> repos;
  std::string root = baseDir.empty() ? config::GITLAB_DATA_DIR : baseDir;
  for (auto it = fs::recursive_directory_iterator(root); it != fs::recursive_directory_iterator(); ++it) {
    const auto& entry = *it;
    if (!entry.is_directory())
      continue;
    int depth = entry.path().lexically_relative(root).parent_path().string().size();
    if (depth >= max_depth) {
      it.disable_recursion_pending();
    }

    // ベアリポジトリは通常、ディレクトリ直下にHEADファイルやobjectsディレクトリがある
    bool hasHEAD    = fs::exists(entry.path() / "HEAD");
    bool hasObjects = fs::is_directory(entry.path() / "objects");
    if (hasHEAD && hasObjects && this->isWikiRepository(entry.path().string()) == false) {
      repos.push_back(entry.path());
    }
  }
  return repos;
}

std::vector<SearchResult> RepositoryScanner::scanAllRepositories(const std::string& pattern,
                                                                 const std::vector<std::string>& excludeBranches) {
  // 仮実装
  return {};
}

bool RepositoryScanner::isWikiRepository(const std::string& path) const {
  const std::string suffix = "wiki.git";
  if (path.size() < suffix.size())
    return false;
  return path.compare(path.size() - suffix.size(), suffix.size(), suffix) == 0;
}
