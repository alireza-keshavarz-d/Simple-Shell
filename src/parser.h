//
// Created by ka on 8/13/26.
//

#ifndef PARSER_H
#define PARSER_H


#include "command_ast.h"
#include "parse_error.h"
#include "command_invocation.h"
#include "token.h"

#include <expected>



class Parser {
public:
    [[nodiscard]] std::expected<Pipeline, ParseError>
    parse(const std::vector<Token> &tokens) const;
};


#endif // PARSER_H
