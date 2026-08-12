#include "cmd.h"

#include <ranges>
#include "common.h"
#include "lexer.h"
#include "process_executor.h"


Command::Command() {
    m_paths      = parse_path_entries();
    m_path_execs = parse_execs_in_path();

}

command Command::resolve(const sv cmd) const {
    if (const auto it = m_builtin_commands.find(std::string{cmd}); it != m_builtin_commands.end()) {
        return {
            .type =  command_type::Builtin,
            .name = cmd,
            .path = std::nullopt,
        };
    }


    if (const auto it = m_path_execs.find(std::string{cmd}); it != m_path_execs.end()) {
        return {
            .type =  command_type::External,
            .name = cmd,
            .path = it->second,
        };
    }

    return {
        .type  = command_type::NotFound,
        .name = cmd,
        .path = std::nullopt,
    };
}

void Command::execute(const command &cmd, const std::vector<sv> &args) const {
    if (cmd.type == command_type::Builtin) {
        const auto func = m_builtin_commands.at(cmd.name);
        func(args);
        return;
    }

    if (cmd.type == command_type::External) {
        const ProcessExecutor executor;
        executor.execute(*cmd.path, cmd.name, args);
    }
}

std::vector<sv> Command::parse_path_entries() const {
    const auto lexer = Lexer{};
#if defined(__WIN32__)
    return lexer.lex(m_PATH, ';');
#elif defined(__linux)
    return lexer.lex(m_PATH, ':');
#endif
}

std::map<std::string, fs::path> Command::parse_execs_in_path() const {
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
