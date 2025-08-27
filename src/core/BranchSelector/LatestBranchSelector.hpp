#pragma once
#include "core/BranchSelector/BranchSelector.hpp"
#include <vector>
#include <string>

class LatestBranchSelector : public BranchSelector {
public:
  void selectBranch(Project& project) override;
  std::vector<std::string> getTargetBranches(const Project& project);
};
