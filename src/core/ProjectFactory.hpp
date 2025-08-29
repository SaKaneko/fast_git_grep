#pragma once
#include <string>
#include <vector>
#include <memory>
#include <filesystem>
#include "core/Project.hpp"

class ProjectFactory {
public:
  ProjectFactory(std::string gitlabDataPath, std::string db_path, std::string db_table_name, std::string index_key,
                 std::string value_key);
  ~ProjectFactory();
  Project createProjectFromDB(std::filesystem::path repository_path);

private:
  void* db_; // sqlite3* の前方宣言（ヘッダでsqlite3.hに依存しないためvoid*）
  std::string gitlabDataPath;
  std::string db_table_name;
  std::string index_key;
  std::string value_key;
};
