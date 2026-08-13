#include "cmd.h"
#include "common.h"
#include "process_executor.h"

#include <ranges>


Command::Command() :
    m_executable_resolver{std::getenv("PATH") != nullptr ? std::getenv("PATH") : ""} {
}

command Command::resolve(const sv cmd) const {
    if (const auto it = m_builtin_commands.find(std::string{cmd}); it != m_builtin_commands.end()) {
        return {
            .type = command_type::Builtin,
            .name = cmd,
            .path = std::nullopt,
        };
    }

    if (const auto path = m_executable_resolver.resolve(cmd); path.has_value()) {
        return {
            .type = command_type::External,
            .name = cmd,
            .path = *path,
        };
    }

    return {
        .type = command_type::NotFound,
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

