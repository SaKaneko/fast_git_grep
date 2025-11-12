#pragma once

#include "core/Project.hpp"
#include <string>
#include <vector>

struct CacheObj {
  std::vector<Project> projects;
  // branch selector type used when the cache was created (e.g. latest, main, all)
  std::string branchSelectorType;
  // exclude branch patterns used when the cache was created
  std::vector<std::string> excludeBranchPatterns;
};
