//
// Created by ka on 8/13/26.
//

#ifndef EXECUTABLE_RESOLVER_H
#define EXECUTABLE_RESOLVER_H

#include "typedefs.h"

#include <vector>


class ExecutableResolver {
public:
    explicit ExecutableResolver(sv path);

    [[nodiscard]] std::optional<fs::path> resolve(sv command) const;

private:
    std::vector<fs::path> m_paths;
};


#endif // EXECUTABLE_RESOLVER_H
