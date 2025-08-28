#include "core/BranchSelector/MainBranchSelector.hpp"
#include <iostream>

void MainBranchSelector::selectBranch(Project& project, const std::vector<std::string>& excludePatterns) {
  auto branches = getTargetBranches(project);
  branches      = excludeBranches(branches, excludePatterns);
  for (const auto& b : branches) {
    if (b == "main")
      project.setTargetBranches({b});
    return;
  }
  std::cout << "[Warning] this repository does not have a main branch. Search master branch." << std::endl;
  for (const auto& b : branches) {
    if (b == "master")
      project.setTargetBranches({b});
    return;
  }
}
