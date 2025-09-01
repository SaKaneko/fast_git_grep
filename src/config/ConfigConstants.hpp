
#include "config/Config.hpp"
#include <string>

namespace config {
std::string makeHelpMessage(const Config& config);
}
#pragma once
#include <string>
#include <set>
#include <vector>

namespace config {
extern bool debug;

const int MINIMAL_ARGUMENT_LENGTH = 3;
constexpr const char* APP_NAME    = "fast_git_grep";



} // namespace config
