#include "cmd.h"
#include "lexer.h"

#include <filesystem>
#include <iostream>
#include <ranges>
#include <string>
#include <string_view>


namespace fs = std::filesystem;

int main() {
    // Flush after every std::cout / std:cerr
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;

    const auto command_controller = Command{};
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

        const auto command = command_controller.resolve(cmd);
        if (command.type == command_type::NotFound) {
            std::cout << cmd << ": command not found\n";
            continue;
        }

        command_controller.execute(command, args);
    }
}
