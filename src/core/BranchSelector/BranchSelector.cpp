#include "core/BranchSelector/BranchSelector.hpp"
#include <array>
#include <sstream>
#include <regex>

std::vector<std::string> BranchSelector::getTargetBranches(const Project& project, const std::string additionalOption) {
  std::vector<std::string> result;
  std::string repoPath = project.path;
  std::string cmd      = "git --git-dir=" + repoPath + " branch" + additionalOption + " --format='%(refname:short)'";
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

std::vector<std::string> BranchSelector::excludeBranches(const std::vector<std::string>& branches,
                                                         const std::vector<std::string>& excludePatterns) {
  std::vector<std::string> result = branches;
  for (const auto& pattern : excludePatterns) {
    result.erase(std::remove_if(result.begin(), result.end(),
                                [&pattern](const std::string& branch) {
                                  try {
                                    std::regex re(pattern);
                                    return std::regex_search(branch, re);
                                  }
                                  catch (const std::regex_error&) {
                                    // 無効な正規表現は無視
                                    return false;
                                  }
                                }),
                 result.end());
  }
  return result;
}