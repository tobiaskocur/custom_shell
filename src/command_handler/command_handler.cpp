//
// Created by cxr on 2/4/26.
//

#include "command_handler.h"

#include <filesystem>
#include <unistd.h>
#include <vector>
#include <sys/wait.h>

command_handler *g_handler;

command_handler::command_handler() : commands{
    command("echo", "echo is a shell builtin", echo_cmd),
    command("exit", "exit is a shell builtin", exit_cmd),
    command("type", "type is a shell builtin", type_cmd),
    command("pwd", "pwd is a shell builtin", pwd_cmd)
} {
    g_handler = this;
}

void command_handler::error_msg(const std::string& cmd) {
    std::cerr << cmd << ": not found" << std::endl;
}

std::string command_handler::find_executable(const std::string &exe, const bool output) {
    std::string path = std::getenv("PATH");

    std::string buffer;
    std::string result;
    while (!path.empty()) {
        if (const size_t colon_pos = path.find(':'); colon_pos == std::string::npos) {
            buffer = path;
            path.clear();
        } else {
            buffer = path.substr(0, colon_pos);
            path = path.substr(colon_pos + 1);
        }

        std::filesystem::path exe_path(buffer);

        if (!std::filesystem::exists(exe_path) || !std::filesystem::is_directory(exe_path)) {
            continue;
        }

        for (auto &p: std::filesystem::directory_iterator(buffer)) {
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
    std::cout << buffer.substr(1, buffer.length() - 1) << std::endl;
}

void command_handler::exit_cmd() {
    std::exit(0);
}

void command_handler::pwd_cmd() {
    std::filesystem::path path = std::getenv("PWD");
    std::cout << path.string() << std::endl;
}

void command_handler::type_cmd() {
    std::string buffer;
    std::getline(std::cin, buffer);

    if (buffer.empty()) { return; }

    buffer = buffer.substr(1, buffer.length() - 1);

    command *cmds = g_handler->get_commands();

    for (int i = 0; i < g_handler->number_of_commands; i++) {
        if (buffer == cmds[i].name) {
            std::cout << cmds[i].description << std::endl;
            break;
        }

        if (i == g_handler->number_of_commands-1 && buffer != cmds[i].name) {
            if (!find_executable(buffer, true).empty()) {
                return;
            }
            continue;
        }
    }
}

void command_handler::custom_exec_cmd(const std::string& cmd) {
    std::string exe_path = find_executable(cmd, true);
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
        for (auto &a: args) {
            argv.push_back(const_cast<char *>(a.c_str()));
        }

        argv.push_back(nullptr);

        pid_t pid = fork();
        if (pid == 0) {
            execvp(exe_path.c_str(), argv.data());
            exit(1);
        } else if (pid > 0) {
            waitpid(pid, nullptr, 0);
            return;
        }
    }
}


command_handler::~command_handler() {
    delete g_handler;
}
