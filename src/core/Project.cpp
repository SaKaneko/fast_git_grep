#include "core/Project.hpp"

void Project::setTargetBranches(const std::vector<std::string>& branches) {
  target_branches = branches;
}

std::vector<std::string> Project::getTargetBranches() const {
  return target_branches;
}
