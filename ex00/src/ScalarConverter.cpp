#include <iostream>

#include "ScalarConverter.hpp"

ScalarConverter::ScalarConverter() {
}

ScalarConverter::ScalarConverter(const ScalarConverter &) {
}

ScalarConverter::~ScalarConverter() {
}

ScalarConverter &ScalarConverter::operator=(const ScalarConverter &) {
    return *this;
}

enum InputType {
    InputChar,
    InputInt,
    InputFloat,
    InputDouble,
    InputInvalid,
};

// TODO: Maybe trim string?
static InputType detectInputType(const std::string &input) {
    if (isCharInput(input)) return InputChar;

    return (InputInvalid);
}

void ScalarConverter::convert(const std::string &raw) {
    InputType input_type = detectInputType(raw);
    switch (input_type) {
        case InputChar:
            std::cout << "Input is char" << std::endl;
            break;
        case InputInt:
            std::cout << "Input is int" << std::endl;
            break;
        case InputFloat:
            std::cout << "Input is float" << std::endl;
            break;
        case InputDouble:
            std::cout << "Input is double" << std::endl;
            break;
        case InputInvalid:
            std::cout << "Input is INVALID" << std::endl;
            break;
    }
}
