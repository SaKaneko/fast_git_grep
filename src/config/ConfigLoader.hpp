#pragma once
#include <string>
#include <vector>
#include "config/Config.hpp"

class ConfigLoader {
private:
  std::vector<std::string> parseMultipleArgs(const std::string& value);

public:
  Config loadConfig(const std::string& filePath);
  Config loadConfigByIniFile(const std::string& filePath);
};
