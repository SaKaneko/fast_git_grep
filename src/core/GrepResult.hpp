#pragma once
#include <string>
#include <vector>

class GrepResult {
public:
  std::string project_name;
  std::string branch;
  std::vector<std::string> line_contents;

  std::string toString(const std::string& baseUrl) const;

private:
  std::string pathToUrl(const std::string& baseUrl, const std::string& line) const;
};
