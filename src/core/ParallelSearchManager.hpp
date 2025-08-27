#pragma once
#include <vector>
#include <string>
#include "core/Project.hpp"
#include "core/SearchResult.hpp"

class ParallelSearchManager {
public:
  std::vector<SearchResult> runParallelSearch(const std::vector<Project>& projects, const std::string& pattern,
                                              const std::vector<std::string>& excludeBranches);
};
