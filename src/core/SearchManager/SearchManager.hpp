#pragma once
#include <vector>
#include <string>
#include "core/Project.hpp"
#include "core/GrepResult.hpp"
#include "util/ProgressBar.hpp"

class SearchManager {
protected:
  util::ProgressBar progress_bar;

public:
  virtual ~SearchManager()                                                                                    = default;
  virtual std::vector<GrepResult> runSearch(const std::vector<Project>& projects, const std::string& pattern) = 0;
};
