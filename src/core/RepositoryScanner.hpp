#pragma once
#include <string>
#include <vector>
#include <filesystem>
#include "core/Project.hpp"
#include "core/ParallelSearchManager.hpp"
#include "config/ConfigLoader.hpp"

class RepositoryScanner {
private:
  std::string rootPath;
  // ConfigLoader configLoader;
  bool isWikiRepository(const std::string& path) const;

public:
  std::vector<SearchResult> scanAllRepositories(const std::string& pattern,
                                                const std::vector<std::string>& excludeBranches);

  // GITLAB_DATA_DIR配下のベアリポジトリパス一覧を取得
  std::vector<std::filesystem::path> listBareRepositories(const std::string& baseDir = "");
};
