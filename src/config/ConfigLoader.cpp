#include "config/ConfigLoader.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <algorithm>

Config ConfigLoader::loadConfig(const std::string& filePath) {
  return this->loadConfigByIniFile(filePath);
}

Config ConfigLoader::loadConfigByIniFile(const std::string& filePath) {
  std::map<std::string, std::string> config;
  std::ifstream file(filePath);
  std::string line;

  while (std::getline(file, line)) {
    // コメント行と空行をスキップ
    if (line.empty() || line[0] == '#')
      continue;

    // 前後の空白を削除
    line.erase(line.begin(),
               std::find_if(line.begin(), line.end(), [](unsigned char ch) { return !std::isspace(ch); }));
    line.erase(std::find_if(line.rbegin(), line.rend(), [](unsigned char ch) { return !std::isspace(ch); }).base(),
               line.end());

    // key=value 形式をパース
    auto pos = line.find('=');
    if (pos == std::string::npos)
      continue;

    std::string key   = line.substr(0, pos);
    std::string value = line.substr(pos + 1);

    // keyとvalueの前後空白を削除
    key.erase(key.begin(), std::find_if(key.begin(), key.end(), [](unsigned char ch) { return !std::isspace(ch); }));
    key.erase(std::find_if(key.rbegin(), key.rend(), [](unsigned char ch) { return !std::isspace(ch); }).base(),
              key.end());
    value.erase(value.begin(),
                std::find_if(value.begin(), value.end(), [](unsigned char ch) { return !std::isspace(ch); }));
    value.erase(std::find_if(value.rbegin(), value.rend(), [](unsigned char ch) { return !std::isspace(ch); }).base(),
                value.end());

    config[key] = value;
  }

  return Config();
}
