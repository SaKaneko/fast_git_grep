// ConfigConstants.cpp
#include "config/ConfigConstants.hpp"

namespace config {
bool debug                                         = false;
std::vector<std::string> excluded_project_patterns = {"obsoleted*"};
std::vector<std::string> excluded_branch_patterns  = {"obsoleted*"};
} // namespace config
