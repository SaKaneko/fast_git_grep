
#include "util/ProgressBar.hpp"
#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>

namespace util {

ProgressBar::ProgressBar(std::size_t total_, std::size_t width_) : total(total_), current(0), width(width_) {}

void ProgressBar::initBar(std::size_t total_, std::size_t width_) {
  total   = total_;
  current = 0;
  width   = width_;
  draw();
}

// 進捗を更新（0 <= value <= total）
void ProgressBar::update(std::size_t value) {
  if (value > total)
    value = total;
  current = value;
  draw();
  if (current == total)
    std::cout << std::endl; // 完了時に改行
}

// 1ステップ進める
void ProgressBar::tick() {
  update(current + 1);
}

void ProgressBar::draw() const {
  double ratio       = (total == 0) ? 0.0 : static_cast<double>(current) / total;
  std::size_t filled = static_cast<std::size_t>(std::round(ratio * width));

  std::cout << '\r' << "[";
  for (std::size_t i = 0; i < width; ++i) {
    if (i < filled)
      std::cout << "=";
    else if (i == filled)
      std::cout << ">";
    else
      std::cout << " ";
  }
  std::cout << "] " << std::setw(3) << current << "/" << total << " Projects" << std::flush;
}
} // namespace util