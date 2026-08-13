//
// Created by ka on 8/13/26.
//
#include <catch2/catch_test_macros.hpp>

#include "process_executor.h"

#include <filesystem>
#include <string>
#include <string_view>
#include <vector>

namespace fs = std::filesystem;

TEST_CASE("ProcessExecutor passes argv correctly", "[process]") {
    ProcessExecutor executor;

    const fs::path executable = "./test_argv_helper";

    const std::string input = "test_argv Alice Alice";

    // These are intentionally views into the same larger string.
    const std::string_view command{
        input.data(),
        std::string_view{"test_argv"}.size()
    };

    const std::string_view arg{
        input.data() + command.size() + 1,
        std::string_view{"Alice"}.size()
    };

    const std::array<std::string_view, 1> args{arg};

    REQUIRE(
        executor.execute(executable, command, args) == 0
    );
}