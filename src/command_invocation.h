//
// Created by ka on 8/13/26.
//

#ifndef COMMAND_INVOCATION_H
#define COMMAND_INVOCATION_H
#include "typedefs.h"


class CommandInvocation {
public:
    CommandInvocation(sv name, std::span<const sv> args);

    [[nodiscard]] sv name() const noexcept;
    [[nodiscard]] std::span<const sv> args() const noexcept;

private:
    sv m_name;
    std::span<const sv> m_args;
};


#endif // COMMAND_INVOCATION_H
