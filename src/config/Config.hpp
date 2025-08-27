#pragma once
#include <string>
#include <vector>

class Config {
private:
  std::string pattern;
  std::vector<std::string> excludeBranches;
  std::string branchSelectorType;
  std::vector<std::string> projects;

public:
  Config(std::string pattern, std::vector<std::string> excludeBranches, std::string branchSelectorType,
         std::vector<std::string> projects)
      : pattern(std::move(pattern)), excludeBranches(std::move(excludeBranches)),
        branchSelectorType(std::move(branchSelectorType)), projects(std::move(projects)) {}
  Config() {}

  const std::string& getPattern() const;
  const std::vector<std::string>& getExcludeBranches() const;
  const std::string& getBranchSelectorType() const;
  const std::vector<std::string>& getProjects() const;
};
