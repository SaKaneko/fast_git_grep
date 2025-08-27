#include "core/ProjectFactory.hpp"
#include "config/ConfigConstants.hpp"
#include <sqlite3.h>
#include <stdexcept>

ProjectFactory::ProjectFactory() : db_(nullptr) {
  if (sqlite3_open(config::PROJECT_NAME_DB, (sqlite3**)&db_) != SQLITE_OK) {
    throw std::runtime_error("Failed to open project name DB");
  }
}

ProjectFactory::~ProjectFactory() {
  if (db_)
    sqlite3_close((sqlite3*)db_);
}

Project ProjectFactory::createProjectFromDB(std::filesystem::path repository_path) {
  Project project;
  const std::string sql = "SELECT value FROM kv WHERE key = '" +
                          std::filesystem::relative(repository_path, config::GITLAB_DATA_DIR).string() + "'";
  sqlite3_stmt* stmt = nullptr;
  if (sqlite3_prepare_v2((sqlite3*)db_, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
    project.path = repository_path;
    project.name = "???";
    sqlite3_finalize(stmt);
    return project;
  }
  while (sqlite3_step(stmt) == SQLITE_ROW) {
    std::string name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
    if (name.empty())
      name = "???";
    project.path = repository_path;
    project.name = name;
  }
  sqlite3_finalize(stmt);
  return project;
}
