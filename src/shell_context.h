//
// Created by ka on 8/13/26.
//

#ifndef SHELL_CONTEXT_H
#define SHELL_CONTEXT_H

class CommandResolver;

struct ShellContext {
    const CommandResolver &resolver;
    bool                   running = true;
};


#endif // SHELL_CONTEXT_H
