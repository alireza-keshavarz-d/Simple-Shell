cmake_minimum_required(VERSION 3.13)

project(shell-starter-cpp)

set(CMAKE_CXX_STANDARD 23) # Enable the C++23 standard

add_executable(shell
        src/main.cpp
        src/process_executor.cpp
        src/lexer.cpp
        src/cmd.cpp
        src/executable_resolver.cpp
)

target_link_libraries(shell PRIVATE readline)
