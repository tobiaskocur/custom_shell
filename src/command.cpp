//
// Created by cxr on 2/4/26.
//

#include "command.h"

void command::add_function(void (*exec)()) {
    this->function = exec;
};
