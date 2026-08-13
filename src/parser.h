//
// Created by ka on 8/13/26.
//

#ifndef PARSER_H
#define PARSER_H


#include "token.h"
#include "command_invocation.h"

#include <optional>


class Parser {
public:
    [[nodiscard]] std::optional<CommandInvocation>
    parse(const std::vector<Token> &tokens) const;
};


#endif // PARSER_H
