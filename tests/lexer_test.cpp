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

TEST_CASE("lexer recognizes pipe") {
    const Lexer lexer;

    const auto tokens =
        lexer.lex("echo hello | grep hello");

    REQUIRE(tokens.size() == 5);

    REQUIRE(tokens[0].type() == TokenType::Word);
    REQUIRE(tokens[1].type() == TokenType::Word);
    REQUIRE(tokens[2].type() == TokenType::Pipe);
    REQUIRE(tokens[3].type() == TokenType::Word);
    REQUIRE(tokens[4].type() == TokenType::Word);
}

TEST_CASE("lexer recognizes output redirection") {
    const Lexer lexer;

    const auto tokens =
        lexer.lex("echo hello > output.txt");

    REQUIRE(tokens.size() == 4);

    REQUIRE(tokens[2].type() ==
            TokenType::RedirectOutput);

    REQUIRE(tokens[2].value() == ">");
}

TEST_CASE("lexer recognizes input redirection") {
    const Lexer lexer;

    const auto tokens =
        lexer.lex("cat < input.txt");

    REQUIRE(tokens.size() == 3);

    REQUIRE(tokens[1].type() ==
            TokenType::RedirectInput);
}

TEST_CASE("lexer recognizes append redirection") {
    const Lexer lexer;

    const auto tokens =
        lexer.lex("echo hello >> output.txt");

    REQUIRE(tokens.size() == 4);

    REQUIRE(tokens[2].type() ==
            TokenType::RedirectAppend);

    REQUIRE(tokens[2].value() == ">>");
}

TEST_CASE("lexer recognizes adjacent operators") {
    const Lexer lexer;

    const auto tokens =
        lexer.lex("echo hello>file");

    REQUIRE(tokens.size() == 4);

    REQUIRE(tokens[2].type() ==
            TokenType::RedirectOutput);

    REQUIRE(tokens[3].value() == "file");
}

TEST_CASE("lexer does not recognize operators inside quotes") {
    const Lexer lexer;

    const auto tokens =
        lexer.lex(R"(echo "hello | world")");

    REQUIRE(tokens.size() == 2);

    REQUIRE(tokens[0].value() == "echo");
    REQUIRE(tokens[1].value() == "hello | world");

    REQUIRE(tokens[1].type() ==
            TokenType::Word);
}

TEST_CASE("lexer does not recognize redirection inside quotes") {
    const Lexer lexer;

    const auto tokens =
        lexer.lex(R"(echo "hello > world")");

    REQUIRE(tokens.size() == 2);
    REQUIRE(tokens[1].value() == "hello > world");
}