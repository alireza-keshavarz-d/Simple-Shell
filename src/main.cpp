#include "cmd.h"
#include "lexer.h"
#include "shell_context.h"
#include "typedefs.h"

#include <filesystem>
#include <iostream>
#include <ranges>
#include <string>
#include <string_view>


int main() {
    // Flush after every std::cout / std:cerr
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;

    const auto command_controller = Command{};
    auto       context = ShellContext{.resolver = command_controller.resolver(), .running = true};
    const auto lexer   = Lexer{};

    while (context.running) {
        std::cout << "$ ";

        std::string line;
        std::getline(std::cin, line);

        const auto tokens = lexer.lex(line, ' ');
        if (tokens.empty())
            continue;

        const auto cmd      = tokens.front();
        const auto args     = std::vector<sv>{tokens.begin() + 1, tokens.end()};
        const auto resolved = command_controller.resolve(cmd);

        if (resolved.type == CommandType::NotFound) {
            std::cout << cmd << ": command not found\n";
            continue;
        }

        command_controller.execute(context, resolved, args);
    }
}
