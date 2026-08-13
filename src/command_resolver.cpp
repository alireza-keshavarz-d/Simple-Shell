//
// Created by ka on 8/12/26.
//

#include "command_resolver.h"
#include "builtin_registry.h"
#include "executable_resolver.h"


CommandResolver::CommandResolver(const sv path) : m_builtins{}, m_executables{path} {}

ResolvedCommand CommandResolver::resolve(const sv command) const {
    if (m_builtins.contains(command)) {
        return {
            .type = CommandType::Builtin,
            .name = command,
            .path = std::nullopt,
        };
    }

    if (const auto path = m_executables.resolve(command)) {
        return {
            .type = CommandType::External,
            .name = command,
            .path = *path,
        };
    }

    return {
        .type = CommandType::NotFound,
        .name = command,
        .path = std::nullopt,
    };
}
BuiltinRegistry CommandResolver::builtins() const { return m_builtins; }
