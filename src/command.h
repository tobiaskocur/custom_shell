//
// Created by cxr on 2/4/26.
//

#ifndef SHELL_STARTER_CPP_COMMAND_H
#define SHELL_STARTER_CPP_COMMAND_H
#include <string>


class command {
    public:
        std::string name;
        std::string description;
        void *execute;

        command(std::string name, std::string description, void (*execute));
};


#endif //SHELL_STARTER_CPP_COMMAND_H