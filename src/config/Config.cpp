#include "config/Config.hpp"

const std::string& Config::getGitlabDataDir() const {
  return gitlabDataDir;
}

const std::string& Config::getHashMapDBFile() const {
  return hashMapDBFile;
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

const std::string& Config::getSearchManagerType() const {
  return searchManagerType;
}

std::vector<std::string> Config::parseMultipleArgs(const std::string& value) {
  std::vector<std::string> result;
  size_t start = 0;
  size_t end   = value.find(',');
  while (end != std::string::npos) {
    result.push_back(value.substr(start, end - start));
    start = end + 1;
    end   = value.find(',', start);
  }
  result.push_back(value.substr(start));
  return result;
}