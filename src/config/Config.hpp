#pragma once
#include <string>
#include <vector>

class Config {
private:
  std::string strategy;
  std::vector<std::string> excludeBranchPatterns;
  std::vector<std::string> excludeProjectPatterns;
  std::string branchSelectorType;
  std::vector<std::string> projects;

public:
  Config(std::string strategy, std::vector<std::string> excludeBranchPatterns,
         std::vector<std::string> excludeProjectPatterns, std::string branchSelectorType,
         std::vector<std::string> projects)
      : strategy(std::move(strategy)), excludeBranchPatterns(std::move(excludeBranchPatterns)),
        excludeProjectPatterns(std::move(excludeProjectPatterns)), branchSelectorType(std::move(branchSelectorType)),
        projects(std::move(projects)) {}
  Config() {}

  const std::string& getStrategy() const;
  const std::vector<std::string>& getExcludeBranchPatterns() const;
  const std::vector<std::string>& getExcludeProjectPatterns() const;
  const std::string& getBranchSelectorType() const;
  const std::vector<std::string>& getProjects() const;
};
