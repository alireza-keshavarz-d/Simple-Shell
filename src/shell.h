//
// Created by ka on 8/13/26.
//

#ifndef SHELL_H
#define SHELL_H

#include "command_invocation.h"
#include "command_resolver.h"
#include "lexer.h"
#include "process_executor.h"
#include "shell_context.h"
#include "typedefs.h"


class Shell {
public:
    explicit Shell(sv path);

    int run();

private:
    void execute(const ResolvedCommand &command, const CommandInvocation &invocation);

    Lexer           m_lexer;
    CommandResolver m_resolver;
    ProcessExecutor m_executor;
    ShellContext    m_context;
};


#endif // SHELL_H
