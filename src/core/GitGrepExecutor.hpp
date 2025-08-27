#pragma once
#include <string>
#include <vector>
#include "core/Project.hpp"
#include "core/GrepResult.hpp"

class GitGrepExecutor {
public:
  std::vector<GrepResult> grep(const Project& project, const std::string& pattern);
};
