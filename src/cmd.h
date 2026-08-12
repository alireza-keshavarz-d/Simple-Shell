#ifndef CMD_H
#define CMD_H

#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <map>
#include <set>
#include <string_view>
#include <vector>

#include "common.h"
#include "command_resolver.h"

using sv     = std::string_view;
namespace fs = std::filesystem;


class Command {
public:
    explicit Command();

    [[nodiscard]] command resolve(sv cmd) const;

    void execute(const command &cmd, const std::vector<sv> &args) const;

private:
    [[nodiscard]] std::vector<sv>                 parse_path_entries() const;
    [[nodiscard]] std::map<std::string, fs::path> parse_execs_in_path() const;

    const std::string_view          m_PATH = std::getenv("PATH");
    std::vector<sv>                 m_paths;
    std::map<std::string, fs::path> m_path_execs; // exec : path

    std::map<sv, CommandFunction> m_builtin_commands{
        {"exit", [&](const auto &args) { std::exit(0); }},
        {"echo",
         [&](const std::vector<sv> &args) {
             for (auto const &arg : args) {
                 std::cout << arg << " ";
             }
             std::cout << std::endl;
         }},
        {
            "type",
            [&](const std::vector<sv> &args) {
                if (args.empty())
                    return;
                if (const auto it = m_builtin_commands.find(std::string{args[0]});
                    it != m_builtin_commands.end()
                ) {
                    std::cout << args[0] << " is a shell builtin\n";
                } else if (m_path_execs.contains(std::string{args[0]})) {
                    std::cout << args[0] << " is " << m_path_execs[std::string{args[0]}].c_str()
                              << "\n";
                } else {
                    std::cout << args[0] << ": not found\n";
                }
            },
        }};
};

#endif // CMD_H
