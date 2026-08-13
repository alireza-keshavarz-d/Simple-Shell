//
// Created by ka on 8/13/26.
//

#include "process_executor.h"

#include <vector>
#include <cstring>
#include <iostream>
#include <sys/wait.h>
#include <unistd.h>

int ProcessExecutor::execute(const fs::path &executable, sv command,
                             const std::span<const std::string> args) const {
    const auto pid = fork();

    if (pid < 0) {
        std::cerr << "fork failed: " << std::strerror(errno) << "\n";
        return -1;
    }

    // build argv
    std::vector<char *> argv;
    argv.reserve(1 + args.size() + 1); // executable args nullptr

    // argv[0] := executable name
    const auto command_name = std::string(command);
    argv.push_back(const_cast<char *>(command_name.data()));

    // args...
    std::vector<std::string> args_string;
    for (const auto arg : args) {
        const auto arg_name = std::string(arg);
        args_string.push_back(arg_name);
    }
    for (const auto& arg : args_string) {
        argv.push_back(const_cast<char *>(arg.data()));
    }

    // for `execv()`
    argv.push_back(nullptr);


    if (pid == 0) {
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
