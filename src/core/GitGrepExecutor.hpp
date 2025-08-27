#pragma once
#include <string>
#include <vector>
#include "core/SearchResult.hpp"

class GitGrepExecutor {
public:
  std::vector<SearchResult> grep(const std::string& pattern, const std::string& branch,
                                 const std::vector<std::string>& excludeBranches);
};
