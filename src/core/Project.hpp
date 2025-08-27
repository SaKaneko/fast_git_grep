#pragma once
#include <string>
#include <vector>

class Project {
private:
  std::string path;

public:
  std::vector<std::string> getBranches() const;
  std::string getLatestBranch() const;
  std::string getMainBranch() const;
};
