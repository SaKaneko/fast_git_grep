#pragma once
#include <vector>
#include <string>
#include "core/Project.hpp"
#include "core/GrepResult.hpp"
#include "util/ProgressBar.hpp"
#include "core/SearchManager/SearchManager.hpp"

class SequentialSearchManager : public SearchManager {
public:
  std::vector<GrepResult> runSequentialSearch(const std::vector<Project>& projects, const std::string& pattern);
  std::vector<GrepResult> runSearch(const std::vector<Project>& projects, const std::string& pattern) override;
};
