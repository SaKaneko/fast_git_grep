#pragma once
#include <string>
#include <vector>

class GrepResult {
public:
  std::string project_name;
  std::string branch;
  std::vector<std::string> line_contents;

  std::string toString() const;
};
