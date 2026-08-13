#include "cmd.h"
#include "process_executor.h"

#include <ranges>


Command::Command() : m_resolver{std::getenv("PATH") != nullptr ? std::getenv("PATH") : ""} {}

const CommandResolver &Command::resolver() const { return m_resolver; }

ResolvedCommand Command::resolve(const sv cmd) const { return m_resolver.resolve(cmd); }

void Command::execute(ShellContext &context, const ResolvedCommand &cmd,
                      const std::vector<sv> &args) const {
    if (cmd.type == CommandType::Builtin) {
        m_resolver.builtins().execute(cmd.name, context, args);
        return;
    }

    if (cmd.type == CommandType::External) {
        (void) m_executor.execute(*cmd.path, cmd.name, args);
    }
}
