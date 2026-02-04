#include <functional>
#include <iostream>
#include <string>
#include <cstdlib>
#include "command.h"

typedef std::function<void()>(*Action);
typedef void (*cmd_one_param)(std::string param);
void error_message(const std::string &cmd) {
  std::cerr << cmd << ": command not found" << std::endl;
}

std::string commands[] = {"exit", "echo"};

void exitd() {
  std::exit(0);
}

void echo() {
  std::string buffer;
  std::getline(std::cin, buffer);
  std::cout << buffer.substr(1, buffer.length()-1) << std::endl;
}



std::vector<command> commandos = {
  command("echo", "test", echo),

};

int main() {
  // Flush after every std::cout / std:cerr

  void (*functions[])() = {exitd, echo};
  while (true) {
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;

    std::cout << "$ ";

    std::string cmd;
    std::cin >> cmd;

    for (int i = 0; i < commands->length(); i++) {
      if (cmd == commands[i]) {
        functions[i]();
        break;
      }
      if (i == commands->length()-1 && cmd != commands[i]) {
        error_message(cmd);
      }
    }
  }
}
