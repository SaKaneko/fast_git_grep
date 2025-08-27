#pragma once
#include "core/Project.hpp"
#include <string>

class BranchSelector {
public:
  virtual void selectBranch(Project& project) = 0;
  virtual ~BranchSelector()                   = default;
};
