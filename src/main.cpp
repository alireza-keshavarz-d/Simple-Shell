#include "cmd.h"
#include "lexer.h"

#include <cstddef>
#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <ranges>
#include <set>
#include <string>
#include <string_view>


namespace fs = std::filesystem;

std::set<std::string_view> builtin_commands = {"echo", "type", "exit"};

int main() {
    // Flush after every std::cout / std:cerr
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;

    const auto command_controller = command{};
    const auto lexer = Lexer{};

    while (true) {
        std::cout << "$ ";

        std::string line;
        std::getline(std::cin, line);

        const auto tokens = lexer.lex(line, ' ');

        if (tokens.empty()) continue;

        const auto cmd = tokens.front();

        const auto args =
            std::vector<sv>{tokens.begin() + 1, tokens.end()};

        if (!command_controller.builtin_commands().contains(cmd) &&
            !command_controller.exec_commands().contains(cmd)) {
            std::cout << cmd << ": command not found\n";
            continue;
        }

        command_controller.execute(cmd, args);
    }
}
