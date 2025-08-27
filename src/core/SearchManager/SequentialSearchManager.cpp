#include "core/SearchManager/SequentialSearchManager.hpp"
#include "core/GitGrepExecutor.hpp"

std::vector<GrepResult> SequentialSearchManager::runSearch(const std::vector<Project>& projects,
                                                           const std::string& pattern) {
  return runSequentialSearch(projects, pattern);
}

std::vector<GrepResult> SequentialSearchManager::runSequentialSearch(const std::vector<Project>& projects,
                                                                     const std::string& pattern) {
  progress_bar.initBar(projects.size());
  std::vector<GrepResult> results;
  GitGrepExecutor executor;
  for (const auto& project : projects) {
    auto project_results = executor.grep(project, pattern);
    results.insert(results.end(), project_results.begin(), project_results.end());
    progress_bar.tick();
  }
  return results;
}