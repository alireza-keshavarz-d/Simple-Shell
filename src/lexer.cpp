#include "lexer.h"

#include <ranges>
#include <string_view>
#include <vector>

namespace {
bool is_operator(char c) {
    return c == '|' || c == '>' || c == '<';
}

TokenType operator_type(const sv input, std::size_t& index) {
    switch (input[index]) {
    case '|':   // |
        ++index;
        return TokenType::Pipe;
    case '<':   // <
        ++index;
        return TokenType::RedirectInput;
    case '>':
        if (index + 1 < input.size() && input[index+1] == '>') { // >>
            index += 2;
            return TokenType::RedirectAppend;
        }
        // >
        ++index;
        return TokenType::RedirectOutput;
    }
    throw std::logic_error("not at operator");
}
}

std::vector<Token> Lexer::lex(const sv input) const {
    std::vector<Token> tokens;
    std::size_t pos = 0;

    while (pos < input.size()) {
        // whitespace
        while (pos < input.size() && std::isspace(static_cast<unsigned char>(input[pos]))) {
            ++pos;
        }

        if (pos == input.size()) break;

        auto token = std::string{};
        bool in_single_quote = false;
        bool in_double_quote = false;

        while (pos < input.size()) {
            const char c = input[pos];

            if (!in_single_quote && !in_double_quote && is_operator(c)) {
                if (!token.empty()) break;

                const auto begin = pos;
                const auto type = operator_type(input, pos);
                tokens.emplace_back(type, std::string{input.substr(begin, pos - begin)});
                continue;
            }

            if (
                (std::isspace(static_cast<unsigned char>(c)) || is_operator(c)) &&
                    !in_single_quote &&
                    !in_double_quote
            ) break;

            if (c == '\\' && !in_single_quote) {
                ++pos;
                token += input[pos++];
                continue;
            }
            if (c == '\'' && !in_double_quote) {
                in_single_quote = !in_single_quote;
                ++pos;
                continue;
            }

            if (c == '"' && !in_single_quote) {
                in_double_quote = !in_double_quote;
                ++pos;
                continue;
            }

            token += c;
            ++pos;
        }

        if (in_single_quote || in_double_quote) {
            throw std::runtime_error("unterminated quote");
        }

        if (!token.empty())
            tokens.emplace_back(TokenType::Word, token);
    }

    return tokens;
}
