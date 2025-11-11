#pragma once

#include "core/Project.hpp"
#include <filesystem>
#include <chrono>
#include <string>
#include <vector>

class ProjectCache {
public:
  using seconds = std::chrono::seconds;

  ProjectCache(const std::filesystem::path& cache_file, seconds lifetime = seconds{300});

  // ロードに成功し、かつキャッシュが有効期限内であれば true を返し
  // out に読み込んだ projects を格納する。無効またはエラー時は false を返す。
  bool load(std::vector<Project>& out) const;

  // projects をバイナリ形式で保存する。成功時 true。
  bool save(const std::vector<Project>& projects) const;

  // キャッシュファイルが存在し、有効期限以内か
  bool isFresh() const;

private:
  std::filesystem::path cache_file_;
  seconds lifetime_;

  // cache file header
  static constexpr const char* FILE_MAGIC = "PGTCACHE"; // 8 bytes ideally
  static constexpr uint32_t FILE_VERSION  = 1;
};
