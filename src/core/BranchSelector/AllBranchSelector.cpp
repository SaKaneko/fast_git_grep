#include "core/BranchSelector/AllBranchSelector.hpp"
#include <cstdlib>
#include <array>
#include <memory>
#include <stdexcept>
#include <sstream>

void AllBranchSelector::selectBranch(Project& project) {
  auto branches = getTargetBranches(project);
  project.setTargetBranches(branches);
}

std::vector<std::string> AllBranchSelector::getTargetBranches(const Project& project) {
  std::vector<std::string> result;
  std::string repoPath = project.path;
  std::string cmd      = "git --git-dir=" + repoPath + " branch --format='%(refname:short)'";
  std::array<char, 256> buffer;
  std::string output;
  FILE* pipe = popen(cmd.c_str(), "r");
  if (!pipe)
    return result;
  while (fgets(buffer.data(), buffer.size(), pipe) != nullptr) {
    output += buffer.data();
  }
  pclose(pipe);
  std::istringstream iss(output);
  std::string line;
  while (std::getline(iss, line)) {
    if (!line.empty()) {
      if (line.front() == '\'' && line.back() == '\'')
        line = line.substr(1, line.size() - 2);
      result.push_back(line);
    }
  }
  return result;
}
