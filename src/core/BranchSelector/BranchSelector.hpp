#pragma once
#include "core/Project.hpp"
#include <string>

class BranchSelector {
public:
  virtual void selectBranch(Project& project, const std::vector<std::string>& excludePatterns) = 0;
  virtual ~BranchSelector()                                                                    = default;
  std::vector<std::string> getTargetBranches(const Project& project, const std::string additionalOption = "");
  std::vector<std::string> excludeBranches(const std::vector<std::string>& branches,
                                           const std::vector<std::string>& excludePatterns);
};
