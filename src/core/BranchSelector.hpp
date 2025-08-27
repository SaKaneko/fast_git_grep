#pragma once
#include "core/Project.hpp"
#include <string>

class BranchSelector {
public:
  virtual std::string selectBranch(const Project& project) = 0;
  virtual ~BranchSelector()                                = default;
};
