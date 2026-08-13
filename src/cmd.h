#ifndef CMD_H
#define CMD_H

#include "command_resolver.h"
#include "common.h"
#include "executable_resolver.h"
#include "typedefs.h"

#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <map>
#include <string_view>
#include <vector>


class Command {
public:
    explicit Command();

    [[nodiscard]] command resolve(sv cmd) const;

    void execute(const command &cmd, const std::vector<sv> &args) const;

private:
    ExecutableResolver m_executable_resolver;

    std::vector<sv> m_paths;

    std::map<sv, CommandFunction> m_builtin_commands{
        {"exit", [&](const auto &args) { std::exit(0); }},
        {"echo",
         [&](const std::vector<sv> &args) {
             for (auto const &arg : args) {
                 std::cout << arg << " ";
             }
             std::cout << std::endl;
         }},
        {"type",
         [&](const std::vector<sv> &args) {
             if (args.empty())
                 return;

             const auto [type, name, path] = resolve(args[0]);
             switch (type) {
                 case command_type::Builtin:
                     std::cout << name << " is shell a builtin\n";
                     break;
                 case command_type::External:
                     std::cout << name << " is " << path->c_str() << "\n";
                     break;
                 case command_type::NotFound:
                     std::cout << name << " not found\n";
                     break;
             }
         }},
    };
};

#endif // CMD_H
