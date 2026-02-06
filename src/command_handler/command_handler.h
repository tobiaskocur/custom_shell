//
// Created by cxr on 2/4/26.
//

#ifndef SHELL_STARTER_CPP_COMMAND_HANDLER_H
#define SHELL_STARTER_CPP_COMMAND_HANDLER_H

#include "../command/command.h"
#include <iostream>

class command_handler {
    private:
        command commands[3];
        static void exit_cmd();

        static void type_cmd();
        static void echo_cmd();

    public:
        command_handler();
        ~command_handler();
        command* get_commands() {return commands;};
        command* get_commands(command_handler& cmd_handler) {return cmd_handler.commands;};
};

extern command_handler* g_handler;

#endif //SHELL_STARTER_CPP_COMMAND_HANDLER_H