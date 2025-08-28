#pragma once
#include <string>
#include <vector>

class Config {
private:
  std::string gitlabDataDir;
  std::string hashMapDBFile;
  std::vector<std::string> excludeBranchPatterns;
  std::vector<std::string> excludeProjectPatterns;
  std::string branchSelectorType;
  std::string searchManagerType;
  std::vector<std::string> parseMultipleArgs(const std::string& value);

public:
  Config() {}

  void setGitlabDataDir(const std::string& dir) {
    gitlabDataDir = dir;
  }
  void setHashMapDBFile(const std::string& file) {
    hashMapDBFile = file;
  }
  void setSearchManagerType(const std::string& type) {
    searchManagerType = type;
  }
  void setBranchSelectorType(const std::string& type) {
    branchSelectorType = type;
  }
  void setExcludeBranchPatterns(const std::vector<std::string>& patterns) {
    excludeBranchPatterns = patterns;
  }

  void setExcludeProjectPatterns(const std::vector<std::string>& patterns) {
    excludeProjectPatterns = patterns;
  }

  void setExcludeBranchPatterns(const std::string& patterns) {
    excludeBranchPatterns = parseMultipleArgs(patterns);
  }

  void setExcludeProjectPatterns(const std::string& patterns) {
    excludeProjectPatterns = parseMultipleArgs(patterns);
  }

  const std::string& getGitlabDataDir() const;
  const std::string& getHashMapDBFile() const;
  const std::string& getSearchManagerType() const;
  const std::string& getBranchSelectorType() const;
  const std::vector<std::string>& getExcludeBranchPatterns() const;
  const std::vector<std::string>& getExcludeProjectPatterns() const;
};
