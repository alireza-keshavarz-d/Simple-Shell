//
// Created by ka on 8/13/26.
//

#include "command_invocation.h"

#include <catch2/catch_test_macros.hpp>


TEST_CASE("command invocation exposes command and arguments")
{
    const std::vector<sv> tokens{
        "echo",
        "hello",
        "world"
    };

    const CommandInvocation invocation{
        tokens.front(),
        std::span{tokens}.subspan(1)
    };

    REQUIRE(invocation.name() == "echo");

    const auto args = invocation.args();

    REQUIRE(args.size() == 2);
    REQUIRE(args[0] == "hello");
    REQUIRE(args[1] == "world");
}