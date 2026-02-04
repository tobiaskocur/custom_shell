#include <functional>
#include <iostream>
#include <string>
#include <cstdlib>
#include <filesystem>
#include <fstream>

#include "command.h"

void error_message(const std::string &cmd) {
  std::cerr << cmd << ": command not found" << std::endl;
}

void exit_cmd() {
  std::exit(0);
}

void echo_cmd() {
  std::string buffer;
  std::getline(std::cin, buffer);
  std::cout << buffer.substr(1, buffer.length()-1) << std::endl;
}



command commands[] = {
  command("echo", "echo is a shell builtin", echo_cmd),
  command("exit", "exit is a shell builtin", exit_cmd),
  command("type", "type is a shell builtin", nullptr),
};

void type_cmd() {
  std::string buffer;
  std::getline(std::cin, buffer);
  buffer = buffer.substr(1, buffer.length()-1);

  for (int i = 0; i < std::size(commands); i++) {
    if (buffer == commands[i].name) {
      std::cout << commands[i].description << std::endl;
      break;
    }

    if (i == std::size(commands)-1 && buffer != commands[i].name) {
      std::string path = std::getenv("PATH");

      std::string bufferx;
      std::string result;
      while (!path.empty()) {
        bufferx = path.substr(0, path.find(':'));
        path = path.substr(path.find(':')+1, path.length());
        std::cout << bufferx << std::endl;

        for ( auto &p : std::filesystem::directory_iterator(bufferx)) {
          if (p.path().string().substr(5, p.path().string().length()) == buffer) {
            result = p.path().string();
            break;
          }
        }

      //  if (result != "") { std::cout << buffer << " is " << result << std::endl; break; };
      }
      if (result == "") {
        std::cerr << buffer << ": not found" << std::endl;
      }
    }
  }

};

int main() {
  // Flush after every std::cout / std:cerr
  commands[2].function = type_cmd;
  while (true) {
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;

    std::cout << "$ ";

    std::string cmd;
    std::cin >> cmd;


    for (int i = 0; i < std::size(commands); i++) {
      if (cmd == commands[i].name) {
        commands[i].execute();
        break;
      }
      if (i == std::size(commands)-1 && cmd != commands[i].name) {
        error_message(cmd);
      }
    }
  }
}
