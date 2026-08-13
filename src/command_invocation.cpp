//
// Created by ka on 8/13/26.
//

#include "command_invocation.h"

CommandInvocation::CommandInvocation(std::vector<std::string> tokens)
    : m_tokens(std::move(tokens))
{}

sv CommandInvocation::name() const noexcept {
    return m_tokens.front();
}

std::span<const std::string> CommandInvocation::args() const noexcept {
    return std::span{m_tokens}.subspan(1);
}
