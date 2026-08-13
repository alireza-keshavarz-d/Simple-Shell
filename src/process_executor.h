//
// Created by ka on 8/13/26.
//

#ifndef PROCESS_EXECUTOR_H
#define PROCESS_EXECUTOR_H

#include <vector>
#include "typedefs.h"


class ProcessExecutor {
public:
    int execute(const fs::path &executable, sv command, const std::vector<sv> &args) const;
};


#endif // PROCESS_EXECUTOR_H
