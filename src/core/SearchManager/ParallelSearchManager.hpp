#pragma once
#include <vector>
#include <string>
#include "core/Project.hpp"
#include "core/GrepResult.hpp"
#include "util/ProgressBar.hpp"
#include "core/SearchManager/SearchManager.hpp"

class ParallelSearchManager : public SearchManager {
public:
  std::vector<GrepResult> runSearch(const std::vector<Project>& projects, const std::string& pattern) override;
  std::vector<GrepResult> runParallelSearch(const std::vector<Project>& projects, const std::string& pattern);
};
