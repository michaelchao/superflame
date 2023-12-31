#include "superflame/fixed_string.h"
#include <iostream>

void showcase_01() {
  superflame::fixed_string<8> str;
  const char * raw_str {"1234567890"};
  str.assign(raw_str, 7);
  std::cout << __func__ << ": size: " << str.size() << std::endl;
  std::cout << __func__ << ": c_str: " << str.c_str() << std::endl;
}

int main() {
    showcase_01();
    return 0;
}