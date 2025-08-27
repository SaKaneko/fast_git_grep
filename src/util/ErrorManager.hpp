#pragma once

#include <string>

namespace util {

class ErrorManager {
public:
  // 共通的な異常終了処理
  static void exitWithError(const std::string& message, int code = 1);

  // ディレクトリのread権限を確認し、なければ異常終了
  static void checkDirectoryReadable(const std::string& path);
};

} // namespace util
