#pragma once
#include <string>
#include <vector>

class Project {
private:
  std::vector<std::string> target_branches;

public:
  std::string path;
  std::string name;
  void setTargetBranches(const std::vector<std::string>& branches);
  std::vector<std::string> getTargetBranches() const;
};
