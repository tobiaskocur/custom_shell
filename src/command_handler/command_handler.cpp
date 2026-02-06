//
// Created by cxr on 2/4/26.
//

#include "command_handler.h"

#include <filesystem>

command_handler* g_handler;

command_handler::command_handler() : commands{ command("echo", "echo is a shell builtin", echo_cmd),
        command("exit", "exit is a shell builtin", exit_cmd),
        command("type", "type is a shell builtin", type_cmd)} {
        g_handler = this;
}

std::string find_executable(const std::string& exe, bool output) {
        std::string path = std::getenv("PATH");

        std::string buffer;
        std::string result;
        while (!path.empty()) {
                size_t colon_pos = path.find(':');

                if (colon_pos == std::string::npos) {
                        buffer = path;
                        path.clear();
                } else {
                        buffer = path.substr(0, colon_pos);
                        path = path.substr(colon_pos + 1);
                }

                for ( auto &p : std::filesystem::directory_iterator(buffer)) {
                        if (p.path().filename().string() == exe) {
                                std::filesystem::perms px = std::filesystem::status(p.path()).permissions();
                                if (std::filesystem::perms::none != (std::filesystem::perms::others_exec & px)) {
                                        if (p.path().extension() == ".exe") {
                                                result = p.path().string() + ".exe";
                                        } else {
                                                result = p.path().string();
                                        }
                                        break;
                                }
                        }
                }

                if (!result.empty()) {
                        if (output) {
                                std::cout << exe << " is " << result << std::endl;
                        }
                        return result;
                };
        }
        if (result.empty()) {
                if (output) {
                        std::cerr << exe << ": not found" << std::endl;
                }
                return "";
        }
        return "";
}

void command_handler::echo_cmd() {
        std::string buffer;
        std::getline(std::cin, buffer);
        std::cout << buffer.substr(1, buffer.length()-1) << std::endl;
}

void command_handler::exit_cmd() {
        std::exit(1);
}

void command_handler::type_cmd() {
        std::string buffer;
        std::getline(std::cin, buffer);

        if (buffer.empty()) { return; }

        buffer = buffer.substr(1, buffer.length()-1);

        command* cmds = g_handler->get_commands();

        for (int i = 0; i < 3; i++) {
                if (buffer == cmds[i].name) {
                        std::cout << cmds[i].description << std::endl;
                        break;
                }

                if (i == 2 && buffer != cmds[i].name) {
                        if (!find_executable(buffer, true).empty()) {
                                return;
                        }
                        continue;
                }
        }
}


command_handler::~command_handler() {
        delete g_handler;
}
