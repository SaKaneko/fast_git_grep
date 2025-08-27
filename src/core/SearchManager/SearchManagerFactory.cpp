#include "core/SearchManager/SearchManagerFactory.hpp"
#include "core/SearchManager/SequentialSearchManager.hpp"
#include "core/SearchManager/ParallelSearchManager.hpp"

std::unique_ptr<SearchManager> SearchManagerFactory::create(const std::string& strategy) {
  if (strategy == "sequential") {
    return std::make_unique<SequentialSearchManager>();
  }
  else if (strategy == "parallel") {
    return std::make_unique<ParallelSearchManager>();
  }
  return nullptr;
}
