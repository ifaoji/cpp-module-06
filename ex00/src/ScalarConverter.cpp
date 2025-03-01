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

bool ScalarConverter::isCharInput(const std::string &raw) {
    if (raw.length() != 1) return false;

    if (!std::isprint(raw[0])) return false;

    return true;
}

bool ScalarConverter::isIntInput(const std::string &raw) {
    if (raw.empty()) return false;

    size_t i = 0;

    const bool has_sign = raw[0] == '+' || raw[0] == '-';
    if (has_sign) i += 1;

    const bool only_has_sign = raw.length() == i;
    if (only_has_sign) return false;

    while (i < raw.length()) {
        if (!std::isdigit(raw[i])) return false;

        i += 1;
    }

    return true;
}

// TODO: Maybe trim string?
ScalarConverter::InputType ScalarConverter::detectInputType(
    const std::string &input) {
    if (isCharInput(input)) return ScalarConverter::InputChar;
    if (isIntInput(input)) return ScalarConverter::InputInt;

    return (ScalarConverter::InputInvalid);
}

void ScalarConverter::convert(const std::string &raw) {
    ScalarConverter::InputType input_type = detectInputType(raw);
    switch (input_type) {
        case ScalarConverter::InputChar:
            std::cout << "Input is char" << std::endl;
            break;
        case ScalarConverter::InputInt:
            std::cout << "Input is int" << std::endl;
            break;
        case ScalarConverter::InputFloat:
            std::cout << "Input is float" << std::endl;
            break;
        case ScalarConverter::InputDouble:
            std::cout << "Input is double" << std::endl;
            break;
        case ScalarConverter::InputInvalid:
            std::cout << "Input is INVALID" << std::endl;
            break;
    }
}
