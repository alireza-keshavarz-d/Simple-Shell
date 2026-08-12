#include "cmd.h"

#include <iostream>
#include <ranges>
#include <sys/wait.h>
#include <unistd.h>
#include "common.h"
#include "lexer.h"


command::command() {
    m_paths      = parse_path_entries();
    m_path_execs = parse_execs_in_path();

    for (const auto &exec : m_path_execs | std::views::keys) {
        m_exec_commands_set.insert(exec);
    }
}
std::set<sv> command::builtin_commands() const { return m_builtin_commands_set; }
std::set<sv> command::exec_commands() const { return m_exec_commands_set; }

void command::execute(const sv &cmd, const std::vector<sv> &args) const {
    if (m_builtin_commands_set.contains(cmd)) {
        const auto func = m_builtin_commands.at(cmd);
        func(args);
    } else if (m_exec_commands_set.contains(cmd)) {
        auto pid     = fork();
        auto command = std::string{};
        command += cmd;

        for (auto [i, view] : std::views::enumerate(args)) {
            command += ' ';
            command += view;
        }

        if (pid == 0) { // child
            std::system(command.c_str());
        }
        if (pid > 0) { // parent
            int status;
            waitpid(pid, &status, 0);
        }
    }
}

std::vector<sv> command::parse_path_entries() const {
#if defined(__WIN32__)
    return split(m_PATH, ';');
#elif defined(__linux)
    return split(m_PATH, ':');
#endif
}

std::map<std::string, fs::path> command::parse_execs_in_path() const {
    std::map<std::string, fs::path> map;

    for (auto const &entry : m_paths) {
        if (!fs::exists(entry))
            continue;

        const auto perms = fs::status(entry).permissions();
        if (!has_read_perm(perms) || !has_exec_perm(perms)) {
            continue;
        }

        for (auto const &dir_entry : fs::directory_iterator(entry)) {
            if (!dir_entry.is_regular_file() || !has_exec_perm(dir_entry.status().permissions()))
                continue;
            const auto last_element = dir_entry.path().filename().string();
            map.try_emplace(last_element, dir_entry.path());
        }
    }
    return map;
}
