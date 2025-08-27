#pragma once
#include <vector>
#include <string>
#include "core/Project.hpp"
#include "core/GrepResult.hpp"
#include "util/ProgressBar.hpp"

class ParallelSearchManager {
private:
  util::ProgressBar progress_bar;

public:
  std::vector<GrepResult> runParallelSearch(const std::vector<Project>& projects, const std::string& pattern);
};
