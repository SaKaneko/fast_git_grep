#include "util/ErrorManager.hpp"
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

} // namespace util
