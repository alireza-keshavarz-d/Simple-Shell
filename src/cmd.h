#ifndef CMD_H
#define CMD_H

#include "builtin_registry.h"
#include "command_resolver.h"
#include "executable_resolver.h"
#include "typedefs.h"

#include <string_view>
#include <vector>

#include "process_executor.h"


class Command {
public:
    explicit Command();

    [[nodiscard]] const CommandResolver &resolver() const;

    [[nodiscard]] ResolvedCommand resolve(sv cmd) const;

    void execute(ShellContext &context, const ResolvedCommand &cmd,
                 const std::vector<sv> &args) const;

private:
    ProcessExecutor m_executor;
    CommandResolver m_resolver;
};

#endif // CMD_H
