//
// Created by ka on 8/13/26.
//

#include "executable_resolver.h"
#include "common.h"


ExecutableResolver::ExecutableResolver(const sv path) {
#ifdef _WIN32
    constexpr char delimiter = ';';
#else
    constexpr char delimiter = ':';
#endif

    std::size_t begin = 0;
    while (begin <= path.size()) {
        const auto end   = path.find(delimiter, begin);
        const auto entry = path.substr(begin, end == sv::npos ? sv::npos : end - begin);

        if (entry.empty()) {
            m_paths.emplace_back(".");
        } else {
            m_paths.emplace_back(entry);
        }

        if (end == sv::npos) {
            break;
        }

        begin = end + 1;
    }
}

std::optional<fs::path> ExecutableResolver::resolve(const sv command) const {
    for (const auto &dir : m_paths) {
        auto candidate = dir / command;

        std::error_code ec;

        if (!fs::is_regular_file(candidate, ec))
            continue;

        const auto perms = fs::status(candidate, ec).permissions();
        if (ec)
            continue;

        if (!has_exec_perm(perms))
            continue;

        return candidate;
    }
    return std::nullopt;
}
