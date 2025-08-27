#include "core/ParallelSearchManager.hpp"

#include "core/GitGrepExecutor.hpp"
#include <thread>
#include <mutex>

std::vector<GrepResult> ParallelSearchManager::runParallelSearch(const std::vector<Project>& projects,
                                                                 const std::string& pattern) {
  std::vector<GrepResult> all_results;
  std::vector<std::thread> threads;
  std::mutex result_mutex;

  for (const auto& project : projects) {
    threads.emplace_back([&all_results, &result_mutex, &project, &pattern]() {
      GitGrepExecutor executor;
      auto results = executor.grep(project, pattern);
      std::lock_guard<std::mutex> lock(result_mutex);
      all_results.insert(all_results.end(), results.begin(), results.end());
    });
  }
  for (auto& t : threads) {
    if (t.joinable())
      t.join();
  }
  return all_results;
}
