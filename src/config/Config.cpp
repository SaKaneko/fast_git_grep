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

const std::string& Config::getDBTableName() const {
  return dbTableName;
}

const std::string& Config::getDBIndexKey() const {
  return dbIndexKey;
}

const std::string& Config::getDBValueKey() const {
  return dbValueKey;
}

const std::string& Config::getCacheFilePath() const {
  return cacheFilePath;
}

unsigned int Config::getCacheLifetimeSeconds() const {
  return cacheLifetimeSeconds;
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