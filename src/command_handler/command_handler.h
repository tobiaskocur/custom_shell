//
// Created by cxr on 2/4/26.
//

#ifndef SHELL_STARTER_CPP_COMMAND_HANDLER_H
#define SHELL_STARTER_CPP_COMMAND_HANDLER_H

#include "../command/command.h"
#include <iostream>

class command_handler {
    public:
        int number_of_commands = 4;

    private:
        command commands[4];
        static void exit_cmd();

        static void type_cmd();
        static void echo_cmd();
        static void custom_exec_cmd(const std::string& cmd);
        static void pwd_cmd();


    public:
        command_handler();
        ~command_handler();
        command* get_commands() {return commands;};
        command* get_commands(command_handler& cmd_handler) {return cmd_handler.commands;};
        static std::string find_executable(const std::string &exe, bool output);
        static void error_msg(const std::string& cmd);
};

extern command_handler* g_handler;

#endif //SHELL_STARTER_CPP_COMMAND_HANDLER_H