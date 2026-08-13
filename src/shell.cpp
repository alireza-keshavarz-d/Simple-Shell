//
// Created by ka on 8/13/26.
//

#include "shell.h"

#include <iostream>

#include "command_invocation.h"


Shell::Shell(const sv path) : m_lexer{}, m_resolver{path}, m_executor{}, m_context{m_resolver} {}

int Shell::run() {
    // Flush after every std::cout / std:cerr
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;

    while (m_context.running) {
        std::cout << "$ ";

        std::string line;
        if (!std::getline(std::cin, line))
            break;

        const auto tokens = m_lexer.lex(line, ' ');
        if (tokens.empty())
            continue;

        CommandInvocation invocation {
            tokens.front(),
            std::span{tokens}.subspan(1)
        };

        const auto command = m_resolver.resolve(invocation.name());

        if (command.type == CommandType::NotFound) {
            std::cout << invocation.name() << ": command not found\n";
            continue;
        }

        execute(command, invocation);
    }

    return 0;
}

void Shell::execute(const ResolvedCommand &command, const CommandInvocation &invocation) {
    if (command.type == CommandType::Builtin) {
        m_resolver.builtins().execute(command.name, m_context, invocation.args());
        return;
    }

    if (command.type == CommandType::External) {
        (void)m_executor.execute(*command.path, command.name, invocation.args());
        return;
    }
}

