#include <cstdlib>

#include "A.hpp"
#include "B.hpp"
#include "Base.hpp"
#include "C.hpp"
#include "assert.hpp"

Base::~Base() {
}

static int random_number(int min, int max) {
    int random_number = min + (rand() % (max - min + 1));

    return random_number;
}

Base *generate() {
    switch (random_number(0, 2)) {
        case 0:
            std::cout << "Generating an instance of A" << std::endl;

            return new A();
        case 1:
            std::cout << "Generating an instance of B" << std::endl;

            return new B();
        case 2:
            std::cout << "Generating an instance of C" << std::endl;

            return new C();

        default:
            UNREACHABLE("Generated number outside for available classes");
    }
}

void identify(Base *p) {
    A *as_a = dynamic_cast<A *>(p);
    if (as_a != NULL) {
        std::cout << "Identified a ptr to class A" << std::endl;

        return;
    }

    B *as_b = dynamic_cast<B *>(p);
    if (as_b != NULL) {
        std::cout << "Identified a ptr to class B" << std::endl;

        return;
    }

    C *as_c = dynamic_cast<C *>(p);
    if (as_c != NULL) {
        std::cout << "Identified a ptr to class C" << std::endl;

        return;
    }

    std::cout << "Not a ptr to class A, B, or C" << std::endl;
}

void identify(Base &p) {
    try {
        A as_a = dynamic_cast<A &>(p);

        std::cout << "Identified a ref to class A" << std::endl;

        return;
    } catch (std::exception) {
    }

    try {
        B as_b = dynamic_cast<B &>(p);

        std::cout << "Identified a ref to class B" << std::endl;

        return;
    } catch (std::exception) {
    }

    try {
        C as_c = dynamic_cast<C &>(p);

        std::cout << "Identified a ref to class C" << std::endl;

        return;
    } catch (std::exception) {
    }

    std::cout << "Not a ref to class A, B, or C" << std::endl;
}
