#include "core/ProjectFactory.hpp"
#include "config/ConfigConstants.hpp"
#include <sqlite3.h>
#include <stdexcept>

ProjectFactory::ProjectFactory(std::string gitlabDataPath, std::string db_path, std::string db_table_name,
                               std::string index_key, std::string value_key)
    : db_(nullptr), gitlabDataPath(gitlabDataPath), db_table_name(db_table_name), index_key(index_key),
      value_key(value_key) {
  if (sqlite3_open(db_path.c_str(), (sqlite3**)&db_) != SQLITE_OK) {
    throw std::runtime_error("Failed to open project name DB");
  }
}

ProjectFactory::~ProjectFactory() {
  if (db_)
    sqlite3_close((sqlite3*)db_);
}

Project ProjectFactory::createProjectFromDB(std::filesystem::path repository_path) {
  Project project;
  project.path          = repository_path;
  project.name          = "???";
  const std::string sql = "SELECT " + value_key + " FROM " + db_table_name + " WHERE " + index_key + " = '" +
                          std::filesystem::relative(repository_path, gitlabDataPath).string() + "'";
  sqlite3_stmt* stmt = nullptr;
  if (sqlite3_prepare_v2((sqlite3*)db_, sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
    if (sqlite3_step(stmt) == SQLITE_ROW) {
      const char* name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
      if (name && *name)
        project.name = name;
    }
    sqlite3_finalize(stmt);
  }
  return project;
}
