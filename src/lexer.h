#pragma once

#include <string_view>

auto split(const std::string_view &line, char delimiter);

auto lex(const std::string_view &line);
