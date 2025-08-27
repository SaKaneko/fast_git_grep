#include <iostream>
#include <thread>
#include "config/ConfigLoader.hpp"
#include "util/ProgressBar.hpp"

int main() {
  ConfigLoader configLoader;
  Config config = configLoader.loadConfig("config.json");

  std::cout << "Hello, World!" << std::endl;

  // Progress bar example
  util::ProgressBar progressBar(90);
  for (std::size_t i = 0; i < 90; ++i) {
    progressBar.tick();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }

  return 0;
}