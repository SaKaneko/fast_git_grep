#include "core/GrepResult.hpp"

std::string GrepResult::toString(const std::string& baseUrl) const {
  std::string ret;
  for (const auto& line : line_contents) {
    ret += project_name + " " + this->pathToUrl(baseUrl, line) + "\n";
  }
  return ret;
}

/*
 * 文字列を以下の形式で変換
 * branch_name:file_path:linenumber:content -> baseurl/project_name/-/tree/branch/file_path?ref_type=heads#linenumber
 * content
 */
std::string GrepResult::pathToUrl(const std::string& baseUrl, const std::string& line) const {
  // 入力形式: file_path:linenumber:content
  size_t firstColon  = line.find(":");
  size_t secondColon = line.find(":", firstColon + 1);
  size_t thirdColon  = line.find(":", secondColon + 1);

  if (firstColon == std::string::npos || secondColon == std::string::npos || thirdColon == std::string::npos) {
    return "invalid result"; // 不正な形式の場合は空文字を返す
  }

  std::string filePath   = line.substr(firstColon + 1, secondColon - firstColon - 1);
  std::string lineNumber = line.substr(secondColon + 1, thirdColon - secondColon - 1);
  std::string content    = line.substr(thirdColon + 1);

  // URLを構築
  std::string url = baseUrl + "/" + project_name + "/-/tree/" + branch + "/" + filePath + "?ref_type=heads#" +
                    lineNumber + " " + content;
  return url;
}