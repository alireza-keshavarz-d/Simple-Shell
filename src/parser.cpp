//
// Created by ka on 8/13/26.
//

#include "parser.h"

std::optional<CommandInvocation>
Parser::parse(const std::vector<Token> &tokens) const {
    if (tokens.empty()) return std::nullopt;

    std::vector<std::string> words;
    words.reserve(tokens.size());

    for (const auto& token : tokens) {
        if (token.type() != TokenType::Word) continue;

        words.emplace_back(token.value());
    }

    if (words.empty()) return std::nullopt;

    return CommandInvocation(std::move(words));
}
