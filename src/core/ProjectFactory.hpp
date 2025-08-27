#pragma once
#include <string>
#include <vector>
#include <memory>
#include <filesystem>
#include "core/Project.hpp"

class ProjectFactory {
public:
  ProjectFactory();
  ~ProjectFactory();
  Project createProjectFromDB(std::filesystem::path repository_path);

private:
  void* db_; // sqlite3* の前方宣言（ヘッダでsqlite3.hに依存しないためvoid*）
};
