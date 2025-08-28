#pragma once
#include <string>
#include <vector>

namespace util {

class ErrorManager {
public:
  // 共通的な異常終了処理
  static void exitWithError(const std::string& message, int code = 1);

  // ディレクトリのread権限を確認し、なければ異常終了
  static void checkDirectoryReadable(const std::string& path);

  // 引数がオプションを除き1つあることを確認し、そうでなければ異常終了
  static void checkSingleArgument(const std::vector<std::string>& args);

  // 引数がX文字以上であることを確認し、そうでなければ異常終了
  static void checkMinArgumentLength(const std::vector<std::string>& args, size_t minLength);
};

} // namespace util
