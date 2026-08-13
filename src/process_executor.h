//
// Created by ka on 8/13/26.
//

#ifndef PROCESS_EXECUTOR_H
#define PROCESS_EXECUTOR_H

#include "typedefs.h"

#include <span>


class ProcessExecutor {
public:
    int execute(const fs::path &executable, sv command, const std::span<const std::string> args) const;
};


#endif // PROCESS_EXECUTOR_H
