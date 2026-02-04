#include <iostream>
#include <string>

void error_message(const std::string &cmd) {
  std::cerr << cmd << " was not found" << std::endl;
}

int main() {
  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  // TODO: Uncomment the code below to pass the first stage
  std::cout << "$ ";

  std::string line;
  std::getline(std::cin, line);

  error_message(line);
}
