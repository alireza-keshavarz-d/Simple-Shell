#include "cmd.h"
#include "common.h"
#include "lexer.h"

#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <map>
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

    while (true) {
        std::cout << "$ ";

        std::string line;
        std::getline(std::cin, line);

        auto tokens = sv{line} | std::views::split(' ') |
                      std::views::filter([](auto &&subrange) { return !subrange.empty(); }) |
                      std::views::transform([](auto &&subrange) {
                          return sv{&*subrange.begin(), static_cast<std::size_t>(std::ranges::distance(subrange))};
                      });

        auto       it  = tokens.begin();
        const auto cmd = sv{*it++};

        auto args = std::ranges::to<std::vector<sv>>(std::ranges::subrange(it, tokens.end()));

        if (!command_controller.builtin_commands().contains(cmd)) {
            std::cout << cmd << ": command not found\n";
        }

        command_controller.execute(cmd, args);

        // if (cmd == "exit")
        //     break;
        // else if (cmd == "echo") {
        //     for (++it; it != tokens.end(); ++it) {
        //         std::cout << *it << " ";
        //     }
        //     std::cout << std::endl;
        // } else if (cmd == "type") {
        //     if (builtin_commands.contains(*++it)) {
        //         std::cout << *it << " is a shell builtin\n";
        //     } else {
        //         std::cout << *it << ": not found\n";
        //     }
        // } else {
        // }
    }

    return 0;
}
