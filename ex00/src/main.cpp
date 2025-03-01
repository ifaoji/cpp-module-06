#include <iostream>

#include "ScalarConverter.hpp"

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cout << "Bad arguments. Usage: " << argv[0] << " <input>"
                  << std::endl;

        return 1;
    }

    ScalarConverter::convert(argv[1]);
}
