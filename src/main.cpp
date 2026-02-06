#include <functional>
#include <iostream>
#include <string>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <unistd.h>
#include <sys/wait.h>
#include "command/command.h"
#include "command_handler/command_handler.h"


int main() {
  command_handler handler{};
  while (true) {
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;

    std::cout << "$ ";

    std::string cmd;
    std::cin >> cmd;


    for (int i = 0; i < 3; i++) {
      if (cmd == handler.get_commands()[i].name) {
        handler.get_commands()[i].execute();
        break;
      }

      std::string exe_path = handler.find_executable(cmd, false);

      if (!exe_path.empty()) {
        std::string remaining;
        std::getline(std::cin, remaining);

        std::vector<std::string> args;
        args.push_back(cmd);

        std::istringstream iss(remaining);
        std::string arg;
        while (iss >> arg) {
          args.push_back(arg);
        }

        std::vector<char *> argv;
        for (auto &a : args) {
          argv.push_back(const_cast<char *>(a.c_str()));
        }

        argv.push_back(nullptr);

        pid_t pid = fork();
        if (pid == 0) {
          execvp(exe_path.c_str(), argv.data());
          exit(1);
        } else if (pid > 0) {
          waitpid(pid, nullptr, 0);
          break;
        }
      }

      if (i == handler.number_of_commands && cmd != handler.get_commands()[i].name) {
        command_handler::error_msg(cmd);
      }
    }
  }
}
