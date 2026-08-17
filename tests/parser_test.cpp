//
// Created by ka on 8/13/26.
//

#include "lexer.h"
#include "parser.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("parser parses simple command") {
    const Lexer lexer;
    const Parser parser;

    const auto tokens =
        lexer.lex("echo hello world");

    const auto result =
        parser.parse(tokens);

    REQUIRE(result.has_value());

    const auto& pipeline = *result;

    REQUIRE(pipeline.commands.size() == 1);

    const auto& command =
        pipeline.commands[0];

    REQUIRE(command.words.size() == 3);
    REQUIRE(command.words[0] == "echo");
    REQUIRE(command.words[1] == "hello");
    REQUIRE(command.words[2] == "world");

    REQUIRE(command.redirections.empty());
}

TEST_CASE("parser parses pipeline") {
    const Lexer lexer;
    const Parser parser;

    const auto tokens =
        lexer.lex("echo hello | grep hello");

    const auto result =
        parser.parse(tokens);

    REQUIRE(result.has_value());

    const auto& pipeline = *result;

    REQUIRE(pipeline.commands.size() == 2);

    REQUIRE(pipeline.commands[0].words[0] == "echo");
    REQUIRE(pipeline.commands[0].words[1] == "hello");

    REQUIRE(pipeline.commands[1].words[0] == "grep");
    REQUIRE(pipeline.commands[1].words[1] == "hello");
}

TEST_CASE("parser parses output redirection") {
    const Lexer lexer;
    const Parser parser;

    const auto tokens =
        lexer.lex("echo hello > output.txt");

    const auto result =
        parser.parse(tokens);

    REQUIRE(result.has_value());

    const auto& command =
        result->commands[0];

    REQUIRE(command.words.size() == 2);

    REQUIRE(command.redirections.size() == 1);

    REQUIRE(
        command.redirections[0].type ==
        Redirection::Type::Output);

    REQUIRE(
        command.redirections[0].target ==
        "output.txt");
}

TEST_CASE("parser parses append redirection") {
    const Lexer lexer;
    const Parser parser;

    const auto result =
        parser.parse(
            lexer.lex("echo hello >> output.txt"));

    REQUIRE(result.has_value());

    const auto& redirection =
        result->commands[0].redirections[0];

    REQUIRE(
        redirection.type ==
        Redirection::Type::Append);

    REQUIRE(redirection.target == "output.txt");
}

TEST_CASE("parser rejects leading pipe") {
    const Lexer lexer;
    const Parser parser;

    const auto result =
        parser.parse(
            lexer.lex("| echo hello"));

    REQUIRE_FALSE(result.has_value());

    REQUIRE(
        result.error().code ==
        ParseErrorCode::EmptyPipelineCommand);
}

TEST_CASE("parser rejects trailing pipe") {
    const Lexer lexer;
    const Parser parser;

    const auto result =
        parser.parse(
            lexer.lex("echo hello |"));

    REQUIRE_FALSE(result.has_value());
}

TEST_CASE("parser rejects missing redirection target") {
    const Lexer lexer;
    const Parser parser;

    const auto result =
        parser.parse(
            lexer.lex("echo hello >"));

    REQUIRE_FALSE(result.has_value());

    REQUIRE(
        result.error().code ==
        ParseErrorCode::ExpectedRedirectionTarget);
}

TEST_CASE("parser rejects redirection without command") {
    const Lexer lexer;
    const Parser parser;

    const auto result =
        parser.parse(
            lexer.lex("> output.txt"));

    REQUIRE_FALSE(result.has_value());
}