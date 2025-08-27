#pragma once
#include <cstddef>

namespace util {

class ProgressBar {
private:
  std::size_t total;
  std::size_t current;
  std::size_t width;

public:
  ProgressBar(std::size_t total_, std::size_t width_ = 50);
  void update(std::size_t value);
  void tick();

private:
  void draw() const;
};
} // namespace util