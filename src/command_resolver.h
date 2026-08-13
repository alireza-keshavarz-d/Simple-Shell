//
// Created by ka on 8/12/26.
//

#ifndef COMMAND_RESOLVER_H
#define COMMAND_RESOLVER_H

#include "builtin_registry.h"
#include "command_resolver_result.h"
#include "executable_resolver.h"
#include "typedefs.h"

class BuiltinRegistry;
class ExecutableResolver;

class CommandResolver {
public:
    explicit CommandResolver(sv path);

    [[nodiscard]] ResolvedCommand resolve(sv command) const;
    [[nodiscard]] BuiltinRegistry builtins() const;

private:
    BuiltinRegistry    m_builtins;
    ExecutableResolver m_executables;
};


#endif // COMMAND_RESOLVER_H
