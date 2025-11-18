#include "config/ConfigLoader.hpp"
#include "config/ConfigConstants.hpp"
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
  Config cfg;
  if (config.find("EXCLUDE_BRANCH_PATTERN") != config.end()) {
    cfg.setExcludeBranchPatterns(parseMultipleArgs(config["EXCLUDE_BRANCH_PATTERN"]));
  }
  if (config.find("EXCLUDE_PROJECT_PATTERN") != config.end()) {
    cfg.setExcludeProjectPatterns(parseMultipleArgs(config["EXCLUDE_PROJECT_PATTERN"]));
  }
  if (config.find("DEFAULT_BRANCH_SELECTOR_TYPE") != config.end()) {
    cfg.setBranchSelectorType(config["DEFAULT_BRANCH_SELECTOR_TYPE"]);
  }
  if (config.find("DEFAULT_SEARCH_MANAGER_TYPE") != config.end()) {
    cfg.setSearchManagerType(config["DEFAULT_SEARCH_MANAGER_TYPE"]);
  }
  if (config.find("GITLAB_DATA_DIR") != config.end()) {
    cfg.setGitlabDataDir(config["GITLAB_DATA_DIR"]);
  }
  if (config.find("HASHMAP_DB_FILE") != config.end()) {
    cfg.setHashMapDBFile(config["HASHMAP_DB_FILE"]);
  }
  if (config.find("DB_TABLE_NAME") != config.end()) {
    cfg.setDBTableName(config["DB_TABLE_NAME"]);
  }
  if (config.find("DB_INDEX_KEY") != config.end()) {
    cfg.setDBIndexKey(config["DB_INDEX_KEY"]);
  }
  if (config.find("DB_VALUE_KEY") != config.end()) {
    cfg.setDBValueKey(config["DB_VALUE_KEY"]);
  }
  if (config.find("CACHE_FILE") != config.end()) {
    cfg.setCacheFilePath(config["CACHE_FILE"]);
  }
  if (config.find("CACHE_LIFETIME_SECONDS") != config.end()) {
    try {
      unsigned int s = static_cast<unsigned int>(std::stoul(config["CACHE_LIFETIME_SECONDS"]));
      cfg.setCacheLifetimeSeconds(s);
    }
    catch (...) {
      // ignore parse errors, keep default
      cfg.setCacheLifetimeSeconds(10800); // default 3 hours
    }
  }
  if (config.find("BASE_URL") != config.end()) {
    cfg.setBaseUrl(config["BASE_URL"]);
  }

  if (config::debug) {
    std::cout << cfg.getBranchSelectorType() << std::endl;
    for (auto pattern : cfg.getExcludeBranchPatterns()) {
      std::cout << "  Exclude branch pattern: " << pattern << std::endl;
    }
    for (auto pattern : cfg.getExcludeProjectPatterns()) {
      std::cout << "  Exclude project pattern: " << pattern << std::endl;
    }
    std::cout << "  GitLab data directory: " << cfg.getGitlabDataDir() << std::endl;
    std::cout << "  HashMap DB file: " << cfg.getHashMapDBFile() << std::endl;
    std::cout << "  Search manager type: " << cfg.getSearchManagerType() << std::endl;
    std::cout << "  Branch selector type: " << cfg.getBranchSelectorType() << std::endl;
    std::cout << "  DB Table Name: " << cfg.getDBTableName() << std::endl;
    std::cout << "  DB Index Key: " << cfg.getDBIndexKey() << std::endl;
    std::cout << "  DB Value Key: " << cfg.getDBValueKey() << std::endl;
    std::cout << "  Cache File Path: " << cfg.getCacheFilePath() << std::endl;
    std::cout << "  Cache Lifetime Seconds: " << cfg.getCacheLifetimeSeconds() << std::endl;
    std::cout << "  Base URL: " << cfg.getBaseUrl() << std::endl;
  }

  return cfg;
}

std::vector<std::string> ConfigLoader::parseMultipleArgs(const std::string& value) {
  std::vector<std::string> result;
  size_t start = 0;
  size_t end   = value.find(',');
  while (end != std::string::npos) {
    result.push_back(value.substr(start, end - start));
    start = end + 1;
    end   = value.find(',', start);
  }
  result.push_back(value.substr(start));
  return result;
}
