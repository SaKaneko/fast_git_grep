#pragma once
#include <string>
#include <set>

namespace config {
bool debug = false;

constexpr const char* APP_NAME = "fast_git_grep";

constexpr const char* DEFAULT_CONFIG_FILE = "config.json";
constexpr const char* DEFAULT_STRATEGY    = "main";
constexpr const char* GITLAB_DATA_DIR     = "/home/ryngo/server/gitlab/data/git-data/repositories/@hashed";
constexpr const char* PROJECT_NAME_DB     = "/home/ryngo/working/fast_bbbgrep/fast_git_grep/test/sample.db";

constexpr const char* HELP_MESSAGE = "Usage: fast_git_grep [options] <args>\n"
                                     "Options:\n"
                                     "  --config=<file>   Specify config file (default: config.json)\n"
                                     "  --help            Show this help message\n";

const std::set<std::string> ACCEPTABLE_STRATEGIES = {"all", "latest", "main"};
} // namespace config
