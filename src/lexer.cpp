#include "lexer.h"

#include <ranges>
#include <string_view>
#include <vector>


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
            if (c == '\\') {
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

            if (
                std::isspace(static_cast<unsigned char>(c)) &&
                    !in_single_quote &&
                    !in_double_quote
            ) break;

            token += c;
            ++pos;
        }

        if (in_single_quote || in_double_quote) {
            throw std::runtime_error("unterminated quote");
        }

        tokens.emplace_back(TokenType::Word, token);
    }

    return tokens;
}
