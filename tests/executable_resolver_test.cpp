//
// Created by ka on 8/13/26.
//

#include "executable_resolver.h"

#include <catch2/catch_test_macros.hpp>

#include <cstdlib>


TEST_CASE("resolver finds an executable") {
    const auto path = std::getenv("PATH");
    REQUIRE(path != nullptr);

    const ExecutableResolver resolver{path};
    const auto result = resolver.resolve("sh");
    REQUIRE(result.has_value());
}

TEST_CASE("resolver does not find nonexistent executable") {
    const auto path = std::getenv("PATH");

    REQUIRE(path != nullptr);

    const ExecutableResolver resolver{path};

    const auto result =
        resolver.resolve("this-command-definitely-does-not-exist");

    REQUIRE_FALSE(result.has_value());
}