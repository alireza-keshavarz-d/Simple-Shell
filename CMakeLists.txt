cmake_minimum_required(VERSION 3.13)

project(Simple-Shell)

set(CMAKE_CXX_STANDARD 23) # Enable the C++23 standard

add_executable(shell
        src/main.cpp
        src/shell.cpp
        src/lexer.cpp
        src/parser.cpp
        src/command_resolver.cpp
        src/executable_resolver.cpp
        src/process_executor.cpp
        src/builtin_registry.cpp
        src/shell_context.cpp
)

target_link_libraries(shell PRIVATE readline)


if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    find_package(Catch2 REQUIRED)

    add_executable(test_argv_helper
            tests/test_argv_helper.cpp
    )
    add_executable(shell_tests
            tests/lexer_test.cpp
            tests/executable_resolver_test.cpp
            tests/command_invocation.cpp
            tests/parser_test.cpp

            src/lexer.cpp
            src/parser.cpp
            src/executable_resolver.cpp
            src/command_invocation.cpp
            src/process_executor.cpp
    )
    target_include_directories(shell_tests
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/src/
    )

    target_link_libraries(shell_tests
        PRIVATE
            Catch2::Catch2WithMain
    )
endif ()