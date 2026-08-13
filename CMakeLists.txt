cmake_minimum_required(VERSION 3.13)

project(shell-starter-cpp)

set(CMAKE_CXX_STANDARD 23) # Enable the C++23 standard

add_executable(shell
        src/main.cpp
        src/shell.cpp
        src/lexer.cpp
        src/command_resolver.cpp
        src/executable_resolver.cpp
        src/process_executor.cpp
        src/builtin_registry.cpp
        src/shell_context.cpp
)

target_link_libraries(shell PRIVATE readline)
