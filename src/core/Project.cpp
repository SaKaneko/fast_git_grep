#include "core/Project.hpp"
#include <regex>

void Project::setTargetBranches(const std::vector<std::string>& branches) {
  target_branches = branches;
}

std::vector<std::string> Project::getTargetBranches() const {
  return target_branches;
}

bool Project::isProjectExcluded(const std::vector<std::string>& excludePatterns) const {
  // 正規表現でマッチングするか調べる
  for (const auto& pattern : excludePatterns) {
    try {
      std::regex re(pattern);
      if (std::regex_search(this->name, re)) {
        return true;
      }
    }
    catch (const std::regex_error&) {
      // 無効な正規表現は無視
      continue;
    }
  }
  return false;
}
