#pragma once
#include "core/BranchSelector/BranchSelector.hpp"
#include <vector>
#include <string>

class LatestBranchSelector : public BranchSelector {
public:
  void selectBranch(Project& project, const std::vector<std::string>& excludePatterns) override;
};
