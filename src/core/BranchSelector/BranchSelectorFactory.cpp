#include "core/BranchSelector/BranchSelectorFactory.hpp"
#include "core/BranchSelector/LatestBranchSelector.hpp"
#include "core/BranchSelector/MainBranchSelector.hpp"
#include "core/BranchSelector/AllBranchSelector.hpp"
#include "util/ErrorManager.hpp"

std::unique_ptr<BranchSelector> BranchSelectorFactory::create(const std::string& strategy) {
  if (strategy == "latest") {
    return std::make_unique<LatestBranchSelector>();
  }
  else if (strategy == "main") {
    return std::make_unique<MainBranchSelector>();
  }
  else if (strategy == "all") {
    return std::make_unique<AllBranchSelector>();
  }
  else {
    util::ErrorManager::exitWithError("Unknown branch strategy: " + strategy, 4);
  }
}
