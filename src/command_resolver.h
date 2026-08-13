//
// Created by ka on 8/12/26.
//

#ifndef SHELL_STARTER_CPP_COMMAND_RESOLVER_H
#define SHELL_STARTER_CPP_COMMAND_RESOLVER_H

#include "typedefs.h"

#include <filesystem>
#include <string>


enum class command_type {
    Builtin,
    External,
    NotFound,
};

struct command {
    command_type type;
    sv name;
    std::optional<fs::path> path;
};

#endif // SHELL_STARTER_CPP_COMMAND_RESOLVER_H
