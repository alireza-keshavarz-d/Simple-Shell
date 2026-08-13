#ifndef COMMON_H
#define COMMON_H


#include "typedefs.h"

#include <expected>
#include <filesystem>
#include <functional>


constexpr auto read_perm = fs::perms::others_read | fs::perms::group_read | fs::perms::owner_read;
constexpr auto exec_perm = fs::perms::others_exec | fs::perms::group_exec | fs::perms::owner_exec;

using CommandFunction = std::function<void(const std::vector<sv> &)>;

constexpr bool has_exec_perm(const fs::perms &perms) {
    return fs::perms::none != (perms & exec_perm);
}

constexpr bool has_read_perm(const fs::perms &perms) {
    return fs::perms::none != (perms & read_perm);
}

#endif // COMMON_H
