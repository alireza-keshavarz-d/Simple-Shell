//
// Created by ka on 8/13/26.
//


#include "lexer.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("Lexer split words") {
    const Lexer lexer;
    const auto tokens = lexer.lex("echo hello world");
    REQUIRE(tokens.size() == 3);
    REQUIRE(tokens[0].value() == "echo");
    REQUIRE(tokens[1].value() == "hello");
    REQUIRE(tokens[2].value() == "world");
}

TEST_CASE("Lexer ignores repeated spaces") {
    const Lexer lexer;
    const auto tokens = lexer.lex("echo   hello   world");
    REQUIRE(tokens.size() == 3);
    REQUIRE(tokens[0].value() == "echo");
    REQUIRE(tokens[1].value() == "hello");
    REQUIRE(tokens[2].value() == "world");
}

TEST_CASE("Lexer handles empty") {
    const Lexer lexer;
    const auto tokens = lexer.lex("");
    REQUIRE(tokens.empty());
}

TEST_CASE("Lexer handles whitespace-only input") {
    const Lexer lexer;
    const auto tokens = lexer.lex("     ");
    REQUIRE(tokens.empty());
}