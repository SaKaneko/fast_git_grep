#include "core/BranchSelector/MainBranchSelector.hpp"
#include <iostream>
#include <cstdlib>
#include <array>
#include <memory>
#include <stdexcept>
#include <sstream>

void MainBranchSelector::selectBranch(Project& project) {
  auto branches = getTargetBranches(project);
  for (const auto& b : branches) {
    if (b == "main")
      project.setTargetBranches({b});
    return;
  }
  std::cout << "[Warning] this repository does not have a main branch. Search master branch." << std::endl;
  for (const auto& b : branches) {
    if (b == "master")
      project.setTargetBranches({b});
    return;
  }
}

std::vector<std::string> MainBranchSelector::getTargetBranches(const Project& project) {
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
