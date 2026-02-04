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
        void (*function)();

        command(std::string n, std::string d, void (*exec)()) : name(std::move(n)),
                                                description(std::move(d)),
                                                function(exec){}

        void add_function(void (*exec)());
        void execute() const { this->function(); }
};


#endif //SHELL_STARTER_CPP_COMMAND_H