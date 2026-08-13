//
// Created by ka on 8/13/26.
//

#ifndef COMMAND_RESOLVER_RESULT_H
#define COMMAND_RESOLVER_RESULT_H

#include "typedefs.h"

enum class CommandType {
    Builtin,
    External,
    NotFound,
};

struct ResolvedCommand {
    CommandType             type;
    sv                      name;
    std::optional<fs::path> path;
};


#endif // COMMAND_RESOLVER_RESULT_H
