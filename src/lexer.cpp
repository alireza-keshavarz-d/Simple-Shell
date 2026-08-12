#include "lexer.h"

#include <ranges>
#include <string_view>
#include <vector>

std::vector<std::string_view> split(const std::string_view &line,
                                    char delimiter) {
  std::vector<std::string_view> result;
  for (auto subrange : line | std::views::split(delimiter)) {
    result.emplace_back(subrange);
  }
  return result;
}

auto lex(const std::string_view &line) { return split(line, ' '); }
