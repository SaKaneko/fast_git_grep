#include "core/GrepResult.hpp"

std::string GrepResult::toString() const {
  std::string ret;
  for (const auto& line : line_contents) {
    ret += project_name + " " + line + "\n";
  }
  return ret;
}