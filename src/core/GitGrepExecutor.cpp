#include "core/GitGrepExecutor.hpp"
#include <cstdio>
#include <memory>
#include <array>
#include <sstream>

std::vector<GrepResult> GitGrepExecutor::grep(const Project& project, const std::string& pattern) {
  std::vector<GrepResult> results;
  for (const auto& branch : project.getTargetBranches()) {
    // gitコマンドの組み立て
    GrepResult res;
    res.project_name = project.name;
    res.branch       = branch;
    std::string cmd  = "git --git-dir='" + project.path + "' grep --color=always -n '" + pattern + "' " + branch;
    std::array<char, 4096> buffer;
    std::string output;
    FILE* pipe = popen(cmd.c_str(), "r");
    if (!pipe)
      continue;
    while (fgets(buffer.data(), buffer.size(), pipe) != nullptr) {
      output += buffer.data();
    }
    pclose(pipe);
    std::istringstream iss(output);
    std::string line;
    while (std::getline(iss, line)) {
      if (!line.empty()) {
        res.line_contents.push_back(line);
      }
    }
    results.push_back(res);
  }
  return results;
}
