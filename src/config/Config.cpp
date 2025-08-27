#include "config/Config.hpp"

const std::string& Config::getStrategy() const {
  return strategy;
}

const std::vector<std::string>& Config::getExcludeBranchPatterns() const {
  return excludeBranchPatterns;
}

const std::vector<std::string>& Config::getExcludeProjectPatterns() const {
  return excludeProjectPatterns;
}

const std::string& Config::getBranchSelectorType() const {
  return branchSelectorType;
}
const std::vector<std::string>& Config::getProjects() const {
  return projects;
}
