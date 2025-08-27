#include <map>
#include <string>
#include <vector>

namespace util {

class ArgParser {
private:
  std::map<std::string, std::string> options; // オプションと値
  std::vector<std::string> args;              // 位置引数

public:
  ArgParser(int argc, char* argv[]);

  // 値付きオプション取得（なければ defaultValue）
  std::string getOption(const std::string& name, const std::string& defaultValue = "") const;

  // フラグオプションが存在するか
  bool hasFlag(const std::string& name) const;

  // 位置引数（ファイル名など）
  const std::vector<std::string>& getArgs() const;

  // デバッグ用出力
  void debugPrint() const;

  bool isDebugMode() const;

private:
  void parse(int argc, char* argv[]);
};

} // namespace util