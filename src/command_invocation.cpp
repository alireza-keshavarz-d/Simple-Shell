//
// Created by ka on 8/13/26.
//

#include "command_invocation.h"
CommandInvocation::CommandInvocation(sv name, std::span<const sv> args)
    : m_name(name), m_args(args)
{}

sv CommandInvocation::name() const noexcept {
    return m_name;
}

std::span<const sv> CommandInvocation::args() const noexcept {
    return m_args;
}

