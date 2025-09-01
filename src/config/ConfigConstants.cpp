#include "config/ConfigConstants.hpp"
#include <sstream>

namespace config {
std::string makeHelpMessage(const Config& config) {
	std::ostringstream oss;
	oss << "Usage: fast_git_grep key [options]\n";
	oss << "Options:\n";
	oss << "  --branch_strategy <main|all|latest> Specify branch strategy (default: " << config.getBranchSelectorType() << ")\n";
	oss << "  --parallel_strategy <parallel|sequential> Specify parallel strategy (default: " << config.getSearchManagerType() << ")\n";
	oss << "  --excluded_projects <pattern>       Specify patterns to exclude projects by regex (default: ";
	if (!config.getExcludeProjectPatterns().empty())
		oss << config.getExcludeProjectPatterns()[0];
	oss << ")\n";
	oss << "  --excluded_branches <pattern>       Specify patterns to exclude branches by regex (default: ";
	if (!config.getExcludeBranchPatterns().empty())
		oss << config.getExcludeBranchPatterns()[0];
	oss << ")\n";
	oss << "  --debug                             Enable debug mode\n";
	oss << "  --help                              Show this help message\n";
	return oss.str();
}
} // namespace config
// ConfigConstants.cpp
#include "config/ConfigConstants.hpp"

namespace config {
bool debug = false;
} // namespace config
