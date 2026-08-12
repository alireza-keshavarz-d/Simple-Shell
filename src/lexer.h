#pragma once

#include <string_view>
#include <vector>

std::vector<std::string_view> split(const std::string_view &line, char delimiter);

auto lex(const std::string_view &line);
