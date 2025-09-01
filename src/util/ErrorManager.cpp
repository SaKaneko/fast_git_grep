#include "util/ErrorManager.hpp"
#include "config/ConfigConstants.hpp"
#include <iostream>
#include <cstdlib>  // exit
#include <unistd.h> // access, R_OK

namespace util {

void ErrorManager::exitWithError(const std::string& message, int code) {
  std::cerr << "Error: " << message << std::endl;
  std::exit(code);
}

void ErrorManager::checkDirectoryReadable(const std::string& path) {
  if (access(path.c_str(), R_OK) != 0) {
    exitWithError("Directory not readable. Please check your rights: " + path, 1);
  }
}

void ErrorManager::checkSingleArgument(const std::vector<std::string>& args, const Config& config) {
  if (args.size() != 1) {
    std::cout << config::makeHelpMessage(config) << std::endl;
    exitWithError("Single argument expected.", 2);
  }
}

void ErrorManager::checkMinArgumentLength(const std::vector<std::string>& args, size_t minLength,
                                          const Config& config) {
  if (args.empty() || args[0].length() < minLength) {
    std::cout << config::makeHelpMessage(config) << std::endl;
    exitWithError("Argument must be at least " + std::to_string(minLength) + " characters long.", 3);
  }
}
} // namespace util
