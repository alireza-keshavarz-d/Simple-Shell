//
// Created by ka on 8/13/26.
//

#include "lexer.h"
#include "parser.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("parser creates command invocation") {
    const Lexer lexer;
    const Parser parser;

    const auto tokens =
        lexer.lex("echo hello world");

    const auto invocation =
        parser.parse(tokens);

    REQUIRE(invocation.has_value());

    REQUIRE(invocation->name() == "echo");

    const auto& args = invocation->args();

    REQUIRE(args.size() == 2);
    REQUIRE(args[0] == "hello");
    REQUIRE(args[1] == "world");
}