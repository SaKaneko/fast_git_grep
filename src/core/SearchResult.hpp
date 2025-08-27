#pragma once
#include <string>

class SearchResult {
private:
  std::string filePath;
  std::string lineContent;
  std::string branch;

public:
  const std::string& getFilePath() const;
  const std::string& getLineContent() const;
  const std::string& getBranch() const;
};
