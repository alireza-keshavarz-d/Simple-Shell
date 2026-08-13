#include "lexer.h"

#include <ranges>
#include <string_view>
#include <vector>


std::vector<sv> Lexer::lex(std::string_view input, char delimiter) const {
    auto tokens = input | std::views::split(delimiter) |
                  std::views::filter([](auto &&subrange) { return !subrange.empty(); }) |
                  std::views::transform([](auto &&subrange) {
                      return sv{&*subrange.begin(),
                                static_cast<std::size_t>(std::ranges::distance(subrange))};
                  });

    return std::ranges::to<std::vector<sv>>(tokens);
}
