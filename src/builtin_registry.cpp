//
// Created by ka on 8/13/26.
//

#include "builtin_registry.h"
#include "command_resolver.h"
#include "shell_context.h"

#include <iostream>


BuiltinRegistry::BuiltinRegistry() {
    m_builtins.emplace("exit",
                       [](ShellContext &context, const auto &) { context.running = false; });

    m_builtins.emplace("echo", [](ShellContext &, const auto &args) {
        for (const auto &arg : args)
            std::cout << arg << ' ';
        std::cout << '\n';
    });

    m_builtins.emplace("type", [](const ShellContext &context, const auto &args) {
        const auto [type, name, path] = context.resolver.resolve(args[0]);
        switch (type) {
            case CommandType::Builtin:
                std::cout << name << " is a shell builtin\n";
                break;
            case CommandType::External:
                std::cout << name << " is " << path->c_str() << "\n";
                break;
            case CommandType::NotFound:
                std::cout << name << ": not found\n";
                break;
        }
    });

    m_builtins.emplace("pwd", [](const ShellContext &context, const auto& args) {
        std::cout << context.current_working_directory.c_str() << "\n";
    });
}

bool BuiltinRegistry::contains(const sv name) const { return m_builtins.contains(name); }

void BuiltinRegistry::execute(const sv name, ShellContext &context,
                              const std::span<const sv> &args) const {
    const auto it = m_builtins.find(name);
    if (it == m_builtins.end())
        throw std::runtime_error("Unknown builtin type");

    it->second(context, args);
}
