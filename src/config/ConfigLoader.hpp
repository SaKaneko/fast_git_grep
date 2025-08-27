#pragma once
#include <string>
#include "config/Config.hpp"

class ConfigLoader {
public:
  Config loadConfig(const std::string& filePath);
  Config loadConfigByIniFile(const std::string& filePath);
};
