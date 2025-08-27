#pragma once
#include <string>
#include <vector>
#include "core/Project.hpp"
#include "core/ParallelSearchManager.hpp"
#include "config/ConfigLoader.hpp"

class RepositoryScanner {
private:
  std::string rootPath;
  ConfigLoader configLoader;

public:
  std::vector<SearchResult> scanAllRepositories(const std::string& pattern, BranchSelector& branchSelector,
                                                const std::vector<std::string>& excludeBranches);
};
