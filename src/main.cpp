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
        if (it == tokens.end()) continue;
        auto cmd = sv{*it++};

        if (cmd.empty()) {
            do {
                ++it;
                if (it == tokens.end())
                    continue;
            } while ((cmd = sv{*it}).empty());
        }

        auto args = std::ranges::to<std::vector<sv>>(std::ranges::subrange(it, tokens.end()));

        if (!command_controller.builtin_commands().contains(cmd) &&
            !command_controller.exec_commands().contains(cmd)) {
            std::cout << cmd << ": command not found\n";
            continue;
        }

        command_controller.execute(cmd, args);
    }

    return 0;
}
