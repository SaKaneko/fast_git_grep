#include "config/Config.hpp"

const std::string& Config::getPattern() const {
  return pattern;
}
const std::vector<std::string>& Config::getExcludeBranches() const {
  return excludeBranches;
}
const std::string& Config::getBranchSelectorType() const {
  return branchSelectorType;
}
const std::vector<std::string>& Config::getProjects() const {
  return projects;
}
