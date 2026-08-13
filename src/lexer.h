//
// Created by ka on 8/13/25.
//

#ifndef LEXER_H
#define LEXER_H

#include "typedefs.h"
#include "token.h"

#include <vector>


class Lexer {
public:
    [[nodiscard]] std::vector<Token> lex(sv input) const;
};

#endif // LEXER_H
