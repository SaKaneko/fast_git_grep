
#include "config/ConfigConstants.hpp"
#include <sstream>

namespace config {

std::string makeHelpMessage(const Config& config) {
  std::ostringstream oss;
  oss << "fast_git_grep — search string across GitLab bare repositories using git grep\n\n";
  oss << "Usage:\n";
  oss << "  fast_git_grep [options] <key>\n\n";
  oss << "Positional arguments:\n";
  oss << "  key                                 The search key (enclose with quotes if it contains spaces)\n\n";
  oss << "Options:\n";
  oss << "  -r, --nocache                       Ignore cache and force repository scan\n";
  oss << "  --branch_strategy <main|all|latest> Branch selection strategy (default: " << config.getBranchSelectorType()
      << ")\n";
  oss << "  --parallel_strategy <parallel|sequential> Search execution mode (default: " << config.getSearchManagerType()
      << ")\n";
  oss << "  --excluded_projects <pattern>       Comma-separated regex patterns to exclude projects (default: ";
  if (!config.getExcludeProjectPatterns().empty())
    oss << config.getExcludeProjectPatterns()[0];
  oss << ")\n";
  oss << "  --excluded_branches <pattern>       Comma-separated regex patterns to exclude branches (default: ";
  if (!config.getExcludeBranchPatterns().empty())
    oss << config.getExcludeBranchPatterns()[0];
  oss << ")\n";
  oss << "  --debug                             Enable verbose debug logging\n";
  oss << "  --help                              Show this help message\n\n";
  oss << "Examples:\n";
  oss << "  fast_git_grep 'TODO'                Search for TODO across all projects\n";
  oss << "  fast_git_grep -r \"fix bug\"         Force rescan and search for 'fix bug'\n";
  return oss.str();
}

bool debug = false;

} // namespace config
