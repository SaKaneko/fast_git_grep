#include "core/ProjectCache.hpp"
#include <fstream>
#include <iostream>

ProjectCache::ProjectCache(const std::filesystem::path& cache_file, seconds lifetime)
    : cache_file_(cache_file), lifetime_(lifetime) {}

static void writeString(std::ofstream& ofs, const std::string& s) {
  uint64_t len = s.size();
  ofs.write(reinterpret_cast<const char*>(&len), sizeof(len));
  if (len)
    ofs.write(s.data(), static_cast<std::streamsize>(len));
}

static bool readString(std::ifstream& ifs, std::string& out) {
  uint64_t len = 0;
  ifs.read(reinterpret_cast<char*>(&len), sizeof(len));
  if (!ifs)
    return false;
  out.clear();
  if (len) {
    out.resize(len);
    ifs.read(&out[0], static_cast<std::streamsize>(len));
    if (!ifs)
      return false;
  }
  return true;
}

bool ProjectCache::save(const CacheObj& cache) const {
  try {
    // ensure parent directory exists
    if (cache_file_.has_parent_path()) {
      std::error_code ec;
      std::filesystem::create_directories(cache_file_.parent_path(), ec);
      (void)ec;
    }
    // write to temp file first
    auto tmp = cache_file_;
    tmp += ".tmp";
    std::ofstream ofs(tmp, std::ios::binary | std::ios::trunc);
    if (!ofs)
      return false;
    // write header (magic + version)
    ofs.write(ProjectCache::FILE_MAGIC, 8);
    uint32_t ver = ProjectCache::FILE_VERSION;
    ofs.write(reinterpret_cast<const char*>(&ver), sizeof(ver));

    // write branch selector type and exclude branch patterns
    writeString(ofs, cache.branchSelectorType);
    uint64_t ex_count = cache.excludeBranchPatterns.size();
    ofs.write(reinterpret_cast<const char*>(&ex_count), sizeof(ex_count));
    for (const auto& p : cache.excludeBranchPatterns) {
      writeString(ofs, p);
    }

    uint64_t count = cache.projects.size();
    ofs.write(reinterpret_cast<const char*>(&count), sizeof(count));
    for (const auto& p : cache.projects) {
      writeString(ofs, p.path);
      writeString(ofs, p.name);
      auto branches   = p.getTargetBranches();
      uint64_t bcount = branches.size();
      ofs.write(reinterpret_cast<const char*>(&bcount), sizeof(bcount));
      for (const auto& b : branches) {
        writeString(ofs, b);
      }
    }
    ofs.flush();
    ofs.close();
    // atomic rename
    std::error_code rename_ec;
    std::filesystem::rename(tmp, cache_file_, rename_ec);
    if (rename_ec) {
      // try remove tmp
      std::filesystem::remove(tmp);
      return false;
    }
    return true;
  }
  catch (...) {
    return false;
  }
}

bool ProjectCache::load(CacheObj& out) const {
  if (!isFresh())
    return false;
  try {
    std::ifstream ifs(cache_file_, std::ios::binary);
    if (!ifs)
      return false;
    // read and validate header
    char magic[8] = {0};
    ifs.read(magic, 8);
    if (!ifs)
      return false;
    if (std::string(magic, 8) != std::string(ProjectCache::FILE_MAGIC, 8))
      return false;
    uint32_t ver = 0;
    ifs.read(reinterpret_cast<char*>(&ver), sizeof(ver));
    if (!ifs)
      return false;
    if (ver != ProjectCache::FILE_VERSION)
      return false;

    // read branch selector type and exclude patterns
    std::string bsel;
    if (!readString(ifs, bsel))
      return false;
    out.branchSelectorType = std::move(bsel);
    uint64_t ex_count      = 0;
    ifs.read(reinterpret_cast<char*>(&ex_count), sizeof(ex_count));
    if (!ifs)
      return false;
    for (uint64_t i = 0; i < ex_count; ++i) {
      std::string pat;
      if (!readString(ifs, pat))
        return false;
      out.excludeBranchPatterns.push_back(std::move(pat));
    }

    uint64_t count = 0;
    ifs.read(reinterpret_cast<char*>(&count), sizeof(count));
    if (!ifs)
      return false;
    out.projects.reserve(static_cast<size_t>(count));
    for (uint64_t i = 0; i < count; ++i) {
      std::string path, name;
      if (!readString(ifs, path))
        return false;
      if (!readString(ifs, name))
        return false;
      uint64_t bcount = 0;
      ifs.read(reinterpret_cast<char*>(&bcount), sizeof(bcount));
      if (!ifs)
        return false;
      std::vector<std::string> branches;
      branches.reserve(static_cast<size_t>(bcount));
      for (uint64_t j = 0; j < bcount; ++j) {
        std::string b;
        if (!readString(ifs, b))
          return false;
        branches.push_back(std::move(b));
      }
      Project p;
      p.path = path;
      p.name = name;
      p.setTargetBranches(branches);
      out.projects.push_back(std::move(p));
    }
    return true;
  }
  catch (...) {
    return false;
  }
}

bool ProjectCache::isFresh() const {
  try {
    if (!std::filesystem::exists(cache_file_))
      return false;
    auto mtime = std::filesystem::last_write_time(cache_file_);
    auto now   = std::filesystem::file_time_type::clock::now();
    auto age   = std::chrono::duration_cast<seconds>(now - mtime);
    return age <= lifetime_;
  }
  catch (...) {
    return false;
  }
}
