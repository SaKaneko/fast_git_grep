#pragma once
#include <vector>
#include <string>
#include "core/Project.hpp"
#include "core/SearchResult.hpp"
#include "core/BranchSelector.hpp"

class ParallelSearchManager {
public:
  std::vector<SearchResult> runParallelSearch(const std::vector<Project>& projects, const std::string& pattern,
                                              BranchSelector& branchSelector,
                                              const std::vector<std::string>& excludeBranches);
};
