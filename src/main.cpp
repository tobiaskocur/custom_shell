#include <iostream>
#include <string>

void error_message(const std::string &cmd) {
  std::cerr << cmd << ": command not found" << std::endl;
}

int main() {
  // Flush after every std::cout / std:cerr
  while (true) {
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;

    std::cout << "$ ";

    std::string line;
    std::getline(std::cin, line);

    error_message(line);
  }
}
