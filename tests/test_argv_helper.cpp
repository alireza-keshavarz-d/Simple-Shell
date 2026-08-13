//
// Created by ka on 8/13/26.
//

#include <iostream>
#include <string_view>

int main(int argc, char* argv[]) {
    if (argc != 2)
        return 1;

    if (std::string_view{argv[0]} != "test_argv")
        return 2;

    if (std::string_view{argv[1]} != "Alice")
        return 3;

    return 0;
}