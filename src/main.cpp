#include <iostream>
#include "./comparisons/comparisons.hpp"

int main(int argc, char** argv) {
  for (int i = 0; i < argc; ++i) {
    std::cout << "{" << argv[i] << "}" << std::endl;
  }
  return 0;
}