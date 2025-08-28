#pragma once
#include <string>
#include <set>
#include <vector>

namespace config {
extern bool debug;

const int MINIMAL_ARGUMENT_LENGTH = 3;
constexpr const char* APP_NAME    = "fast_git_grep";

constexpr const char* HELP_MESSAGE =
    "Usage: fast_git_grep key [options]\n"
    "Options:\n"
    "  --branch_strategy <main|all|latest> Specify branch strategy (default: latest)\n"
    "  --parallel_strategy <parallel|sequential> Specify parallel strategy (default: parallel)\n"
    "  --excluded_projects <pattern>       Specify patterns to exclude projects by regex (default: ^obsoleted)\n"
    "  --excluded_branches <pattern>       Specify patterns to exclude branches by regex (default: ^obsoleted)\n"
    "  --debug                             Enable debug mode\n"
    "  --help                              Show this help message\n";

} // namespace config
