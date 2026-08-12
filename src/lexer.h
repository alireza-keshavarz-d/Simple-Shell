//
// Created by ka on 8/13/25.
//

#ifndef LEXER_H
#define LEXER_H

#include <string_view>
#include <vector>

using sv = std::string_view;

class Lexer {
public:
    [[nodiscard]] std::vector<sv> lex(std::string_view input, char delimiter) const;
};

#endif // LEXER_H