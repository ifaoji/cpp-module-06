#include <cstdlib>
#include <ctime>
#include <iostream>

#include "Base.hpp"

void PrintHeader(const std::string &header) {
    std::cout << "----" << std::endl
              << header << std::endl
              << "----" << std::endl;
}

int main() {
    srand(time(NULL));

    {
        PrintHeader("Testing random identifying");

        for (int i = 0; i < 10; i++) {
            Base *unknown = generate();

            identify(unknown);
            identify(*unknown);

            std::cout << "=" << std::endl;

            delete unknown;
        }
    }

    {
        PrintHeader("Invalid type identify");

        Base *invalid = new Base();

        identify(invalid);
        identify(*invalid);

        delete invalid;
    }
}
