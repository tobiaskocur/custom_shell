//
// Created by cxr on 2/4/26.
//

#include "command.h"

#include <utility>

command::command(std::string name, std::string description, void (*execute)) {
    this->name = std::move(name);
    this->description = std::move(description);
    this->execute = execute;
}
