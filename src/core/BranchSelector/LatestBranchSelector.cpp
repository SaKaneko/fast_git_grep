#include "core/BranchSelector/LatestBranchSelector.hpp"

void LatestBranchSelector::selectBranch(Project& project, const std::vector<std::string>& excludePatterns) {
  auto branches = getTargetBranches(project, " --sort=-committerdate");
  branches      = excludeBranches(branches, excludePatterns);
  if (!branches.empty())
    project.setTargetBranches({branches.front()});
}
