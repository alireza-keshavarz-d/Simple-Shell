//
// Created by ka on 8/13/26.
//

#ifndef BUILTIN_REGISTRY_H
#define BUILTIN_REGISTRY_H

#include "typedefs.h"

#include <functional>
#include <map>

class ShellContext;

using BuiltinFunction = std::function<void(ShellContext &, const std::vector<sv> &)>;

class BuiltinRegistry {
public:
    BuiltinRegistry();

    [[nodiscard]] bool contains(sv name) const;
    void               execute(sv name, ShellContext &context, const std::vector<sv> &args) const;

private:
    std::map<sv, BuiltinFunction> m_builtins;
};


#endif // BUILTIN_REGISTRY_H
