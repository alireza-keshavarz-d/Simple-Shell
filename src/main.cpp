#include "shell.h"


int main() {
    const auto path = std::getenv("PATH");
    Shell shell{
        path != nullptr ? path : ""
    };

    return shell.run();
}
