//
// Created by ka on 8/14/26.
//

#ifndef COMMAND_AST_H
#define COMMAND_AST_H
#include <string>
#include <vector>

struct Redirection {
    enum class Type {
        Input,
        Output,
        Append,
    };

    std::string target;
    Type type;
};

struct SimpleCommand {
    std::vector<std::string> words;
    std::vector<Redirection> redirections;
};

struct Pipeline {
    std::vector<SimpleCommand> commands;
};

#endif // COMMAND_AST_H
