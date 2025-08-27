#include "core/SearchResult.hpp"

const std::string& SearchResult::getFilePath() const {
  return filePath;
}
const std::string& SearchResult::getLineContent() const {
  return lineContent;
}
const std::string& SearchResult::getBranch() const {
  return branch;
}
