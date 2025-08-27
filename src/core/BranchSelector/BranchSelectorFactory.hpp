#pragma once
#include <string>
#include <memory>
#include "core/BranchSelector/BranchSelector.hpp"

class BranchSelectorFactory {
public:
  static std::unique_ptr<BranchSelector> create(const std::string& strategy);
};
