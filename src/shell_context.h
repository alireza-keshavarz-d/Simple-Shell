//
// Created by ka on 8/13/26.
//

#ifndef SHELL_CONTEXT_H
#define SHELL_CONTEXT_H
#include <string>

#include "typedefs.h"

class CommandResolver;

struct ShellContext {
    const CommandResolver &resolver;
    fs::path               current_working_directory = fs::current_path();
    bool                   running = true;
};


#endif // SHELL_CONTEXT_H
