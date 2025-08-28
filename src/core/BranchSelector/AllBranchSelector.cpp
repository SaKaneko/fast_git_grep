#include "core/BranchSelector/AllBranchSelector.hpp"

void AllBranchSelector::selectBranch(Project& project, const std::vector<std::string>& excludePatterns) {
  auto branches = getTargetBranches(project);
  branches      = excludeBranches(branches, excludePatterns);
  project.setTargetBranches(branches);
}
