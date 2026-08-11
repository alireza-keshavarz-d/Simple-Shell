#include <algorithm>
#include <cstddef>
#include <functional>
#include <iostream>
#include <map>
#include <ranges>
#include <set>
#include <string>
#include <string_view>
#include <vector>

using CommandFunction =
    std::function<void(const std::vector<std::string_view> &)>;

std::set<std::string_view> builtin_commands = {"echo", "type", "exit"};

int main() {
  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  std::map<std::string_view, CommandFunction> commands = {
      {"exit", [&](const auto &args) { std::exit(0); }},
      {"echo",
       [&](const auto &args) {
         for (size_t i = 0; i < args.size(); ++i) {
           std::cout << args[i] << " ";
         }
         std::cout << std::endl;
       }},
      {
          "type",
          [&](const auto &args) {
            if (args.size() != 2)
              return;
            if (builtin_commands.contains(args[1])) {
              std::cout << args[1] << " is a shell builtin\n";
            } else {
              std::cout << args[1] << ": not found\n";
            }
          },
      }};

  while (true) {
    std::cout << "$ ";

    std::string line;
    std::getline(std::cin, line);

    auto tokens = std::string_view{line} | std::ranges::views::split(' ') |
                  std::ranges::views::transform([](auto &&subrange) {
                    return std::string_view{subrange.begin(), subrange.end()};
                  });

    auto it = tokens.begin();
    if (it == tokens.end())
      continue;

    auto cmd = *it;
    if (cmd.empty()) {
      do {
        ++it;
        if (it == tokens.end())
          continue;
      } while ((cmd = *it).empty());
    }

    if (cmd == "exit")
      break;
    else if (cmd == "echo") {
      for (++it; it != tokens.end(); ++it) {
        std::cout << *it << " ";
      }
      std::cout << std::endl;
    } else if (cmd == "type") {
      if (std::find(builtin_commands.begin(), builtin_commands.end(), *++it) !=
          builtin_commands.end()) {
        std::cout << *it << " is a shell builtin\n";
      } else {
        std::cout << *it << ": not found\n";
      }
    } else {
      std::cout << cmd << ": command not found\n";
    }
  }

  return 0;
}
