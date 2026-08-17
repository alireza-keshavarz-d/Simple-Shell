//
// Created by ka on 8/13/26.
//

#include "parser.h"

#include <utility>

std::expected<Pipeline, ParseError>
Parser::parse(const std::vector<Token> &tokens) const {
    if (tokens.empty()) {
        return std::unexpected{
            ParseError{ParseErrorCode::ExpectedCommand, "empty command"}
        };
    }

    auto pipeline = Pipeline{};
    auto current = SimpleCommand{};

    for (auto i = 0; i < tokens.size(); ++i) {
        auto& token = tokens[i];
        switch (token.type()) {
            case TokenType::Word:
                current.words.emplace_back(token.value());
                break;
            case TokenType::Pipe:
                if (current.words.empty()) {
                    return std::unexpected{
                        ParseError{
                            ParseErrorCode::EmptyPipelineCommand,
                            "expected command before '|'"
                        }
                    };
                }
                pipeline.commands.push_back(std::move(current));
                current = {};
                break;
            case TokenType::RedirectInput:
            case TokenType::RedirectOutput:
            case TokenType::RedirectAppend:
                if (current.words.empty()) {
                    return std::unexpected{
                        ParseError{ParseErrorCode::ExpectedCommand, "redirection without command"}
                    };
                }
                if (tokens.size() <= i + 1 || tokens[i+1].type() != TokenType::Word) {
                    return std::unexpected{
                        ParseError{ParseErrorCode::ExpectedRedirectionTarget, "expected filename after redirection"}
                    };
                }

                auto type = Redirection::Type{};
                switch (token.type()) {
                    case TokenType::RedirectInput:
                        type = Redirection::Type::Input;
                        break;
                    case TokenType::RedirectOutput:
                        type = Redirection::Type::Output;
                        break;
                    case TokenType::RedirectAppend:
                        type = Redirection::Type::Append;
                        break;
                    default:
                        std::unreachable();
                }

                current.redirections.push_back({
                    .target = std::string{tokens[++i].value()},
                    .type = type,
                });

                break;
        }
    }

    if (current.words.empty()) {
        return std::unexpected{
            ParseError{ParseErrorCode::EmptyPipelineCommand, "expected command after '|'",}
        };
    }

    pipeline.commands.push_back(std::move(current));
    return pipeline;
}
