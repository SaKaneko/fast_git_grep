#pragma once
#include <string>
#include <memory>
#include "core/SearchManager/SearchManager.hpp"

class SearchManagerFactory {
public:
  static std::unique_ptr<SearchManager> create(const std::string& strategy);
};
