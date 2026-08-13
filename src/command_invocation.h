//
// Created by ka on 8/13/26.
//

#ifndef COMMAND_INVOCATION_H
#define COMMAND_INVOCATION_H

#include "typedefs.h"
#include <vector>


class CommandInvocation {
public:
    explicit CommandInvocation(std::vector<std::string> tokens);

    [[nodiscard]] sv name() const noexcept;
    [[nodiscard]] std::span<const std::string> args() const noexcept;

private:
    std::vector<std::string> m_tokens;
};


#endif // COMMAND_INVOCATION_H
