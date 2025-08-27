#include "util/ArgParser.hpp"
#include <iostream>

namespace util {

ArgParser::ArgParser(int argc, char* argv[]) {
  parse(argc, argv);
}

std::string ArgParser::getOption(const std::string& name, const std::string& defaultValue) const {
  auto it = options.find(name);
  if (it != options.end())
    return it->second;
  return defaultValue;
}

bool ArgParser::hasFlag(const std::string& name) const {
  return options.count(name) > 0 && options.at(name).empty();
}

const std::vector<std::string>& ArgParser::getArgs() const {
  return args;
}

void ArgParser::debugPrint() const {
  std::cout << "[Options]\n";
  for (auto& kv : options) {
    std::cout << "  " << kv.first << " = " << kv.second << "\n";
  }
  std::cout << "[Args]\n";
  for (auto& a : args) {
    std::cout << "  " << a << "\n";
  }
}

void ArgParser::parse(int argc, char* argv[]) {
  for (int i = 1; i < argc; ++i) {
    std::string token = argv[i];
    if (token.rfind("--", 0) == 0) {
      // --option または --option=value
      auto eqPos = token.find('=');
      if (eqPos != std::string::npos) {
        std::string key   = token.substr(2, eqPos - 2);
        std::string value = token.substr(eqPos + 1);
        options[key]      = value;
      }
      else {
        // 次が値かもしれない
        if (i + 1 < argc && argv[i + 1][0] != '-') {
          options[token.substr(2)] = argv[++i];
        }
        else {
          options[token.substr(2)] = ""; // フラグ扱い
        }
      }
    }
    else if (token.rfind("-", 0) == 0 && token.size() > 1) {
      // -o value
      std::string key = token.substr(1);
      if (i + 1 < argc && argv[i + 1][0] != '-') {
        options[key] = argv[++i];
      }
      else {
        options[key] = ""; // フラグ扱い
      }
    }
    else {
      // 位置引数
      args.push_back(token);
    }
  }
}

}