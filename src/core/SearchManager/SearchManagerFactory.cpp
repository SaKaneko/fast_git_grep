#include "core/SearchManager/SearchManagerFactory.hpp"
#include "core/SearchManager/SequentialSearchManager.hpp"
#include "core/SearchManager/ParallelSearchManager.hpp"
#include "util/ErrorManager.hpp"

std::unique_ptr<SearchManager> SearchManagerFactory::create(const std::string& strategy) {
  if (strategy == "sequential") {
    return std::make_unique<SequentialSearchManager>();
  }
  else if (strategy == "parallel") {
    return std::make_unique<ParallelSearchManager>();
  }
  else {
    util::ErrorManager::exitWithError("Unknown search manager strategy: " + strategy, 4);
    return nullptr;
  }
}
