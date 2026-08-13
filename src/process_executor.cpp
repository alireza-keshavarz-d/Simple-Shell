//
// Created by ka on 8/13/26.
//

#include "process_executor.h"

#include <cstring>
#include <iostream>
#include <sys/wait.h>
#include <unistd.h>

int ProcessExecutor::execute(const fs::path &executable, sv command,
                             const std::vector<sv> &args) const {
    const auto pid = fork();

    if (pid < 0) {
        std::cerr << "fork failed: " << std::strerror(errno) << "\n";
        return -1;
    }

    if (pid == 0) {
        // build argv
        std::vector<char *> argv;
        argv.reserve(1 + args.size() + 1); // executable args nullptr

        // argv[0] := executable name
        argv.push_back(const_cast<char *>(command.data()));

        // args...
        for (const auto arg : args) {
            argv.push_back(const_cast<char *>(arg.data()));
        }

        // for `execv()`
        argv.push_back(nullptr);

        execv(executable.c_str(), argv.data());

        // if execv fails
        std::cerr << "exec failed for '" << command << "': " << std::strerror(errno) << "\n";

        _exit(127);
    }

    int status = 0;

    if (waitpid(pid, &status, 0) < 0) {
        std::cerr << "waitpid failed: " << std::strerror(errno) << "\n";
        return -1;
    }

    if (WIFEXITED(status)) {
        return WEXITSTATUS(status);
    }

    if (WIFSIGNALED(status)) {
        return 128 + WTERMSIG(status);
    }

    return -1;
}
