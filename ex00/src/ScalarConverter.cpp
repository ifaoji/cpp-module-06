#include <cstdlib>
#include <cstring>
#include <iostream>
#include <limits>

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
    if (std::isdigit(raw[0])) return false;

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

bool ScalarConverter::isFloatInput(const std::string &input) {
    if (input.empty()) return false;

    size_t i = 0;
    while (i < input.length() && std::isspace(input[i])) {
        i += 1;
    }

    const bool has_sign = input[i] == '+' || input[i] == '-';
    if (has_sign) i += 1;

    const bool only_has_sign = input.length() == i;
    if (only_has_sign) return false;

    const std::string after_sign = input.substr(i);

    if (strcasecmp(after_sign.c_str(), "nanf") == 0 ||
        strcasecmp(after_sign.c_str(), "inff") == 0)
        return true;

    bool has_digits   = false;
    bool has_dot      = false;
    bool has_exponent = false;
    while (i < input.length()) {
        const bool is_exponent_char = std::tolower(input[i]) == 'e';
        if (is_exponent_char) {
            if (has_exponent) return false;
            // `e` can only come after a digit
            if (!has_digits) return false;

            has_exponent = true;
            // Reset since after `e` there must be at least a single digit
            has_digits = false;

            const bool exponent_has_sign =
                i + 1 < input.length() &&
                (input[i + 1] == '+' || input[i + 1] == '-');
            if (exponent_has_sign) i += 1;

            i += 1;
            continue;
        }

        const bool is_dot_char = input[i] == '.';
        if (is_dot_char) {
            if (has_dot) return false;
            if (has_exponent) return false;
            // `.` can only come after a digit
            if (!has_digits) return false;

            has_dot = true;
            // Reset since after `.` there must be at least a single digit
            has_digits = false;

            i += 1;
            continue;
        }

        const bool is_f_char = std::tolower(input[i]) == 'f';
        if (is_f_char) {
            if (!has_dot && !has_exponent) return false;
            if (!has_digits) return false;

            if (i != input.length() - 1) return false;

            return true;
        }

        if (std::isdigit(input[i])) {
            has_digits = true;

            i += 1;
            continue;
        }

        return false;
    }

    return false;
}

bool ScalarConverter::isDoubleInput(const std::string &input) {
    if (input.empty()) return false;

    size_t i = 0;
    while (i < input.length() && std::isspace(input[i])) {
        i += 1;
    }

    const bool has_sign = input[i] == '+' || input[i] == '-';
    if (has_sign) i += 1;

    const bool only_has_sign = input.length() == i;
    if (only_has_sign) return false;

    const std::string after_sign = input.substr(i);

    if (strcasecmp(after_sign.c_str(), "nan") == 0 ||
        strcasecmp(after_sign.c_str(), "inf") == 0)
        return true;

    bool has_digits   = false;
    bool has_dot      = false;
    bool has_exponent = false;
    while (i < input.length()) {
        const bool is_exponent_char = std::tolower(input[i]) == 'e';
        if (is_exponent_char) {
            if (has_exponent) return false;
            // `e` can only come after a digit
            if (!has_digits) return false;

            has_exponent = true;
            // Reset since after `e` there must be at least a single digit
            has_digits = false;

            const bool exponent_has_sign =
                i + 1 < input.length() &&
                (input[i + 1] == '+' || input[i + 1] == '-');
            if (exponent_has_sign) i += 1;

            i += 1;
            continue;
        }

        const bool is_dot_char = input[i] == '.';
        if (is_dot_char) {
            if (has_dot) return false;
            if (has_exponent) return false;
            // `.` can only come after a digit
            if (!has_digits) return false;

            has_dot = true;
            // Reset since after `.` there must be at least a single digit
            has_digits = false;

            i += 1;
            continue;
        }

        if (std::isdigit(input[i])) {
            has_digits = true;

            i += 1;
            continue;
        }

        return false;
    }

    if (!has_dot && !has_exponent) return false;
    if (!has_digits) return false;

    return true;
}

// TODO: Maybe trim string?
ScalarConverter::InputType ScalarConverter::detectInputType(
    const std::string &input) {
    if (isCharInput(input)) return ScalarConverter::InputChar;
    if (isIntInput(input)) return ScalarConverter::InputInt;
    if (isFloatInput(input)) return ScalarConverter::InputFloat;
    if (isDoubleInput(input)) return ScalarConverter::InputDouble;

    return (ScalarConverter::InputInvalid);
}

void ScalarConverter::print(char input) {
    int    as_int    = static_cast<int>(input);
    float  as_float  = static_cast<float>(input);
    double as_double = static_cast<double>(input);

    std::cout << "char: '" << input << "'" << std::endl;
    std::cout << "int: " << as_int << std::endl;
    std::cout << "float: " << as_float << std::endl;
    std::cout << "double: " << as_double << std::endl;
}

void ScalarConverter::print(int input) {
    const bool fits_in_char = input >= std::numeric_limits<char>().min() &&
                              input <= std::numeric_limits<char>().max();
    if (!fits_in_char) {
        std::cout << "char: impossible" << std::endl;
    } else {
        char c = static_cast<char>(input);

        if (!std::isprint(c)) {
            std::cout << "char: Non displayable" << std::endl;
        } else {
            std::cout << "char: '" << c << "'" << std::endl;
        }
    }

    float  as_float  = static_cast<float>(input);
    double as_double = static_cast<double>(input);

    std::cout << "int: " << input << std::endl;
    std::cout << "float: " << as_float << std::endl;
    std::cout << "double: " << as_double << std::endl;
}

static bool parseInt(const std::string &raw, int &result) {
    char *end_ptr = NULL;
    result        = strtol(raw.c_str(), &end_ptr, 10);

    const bool is_at_end = *end_ptr == '\0';
    if (!is_at_end) {
        return false;
    }

    // `strtol` stops at long min/max, therefore a check with int limits is safe
    const bool underflow = result < std::numeric_limits<int>().min();
    const bool overflow  = result > std::numeric_limits<int>().max();
    if (underflow || overflow) {
        return false;
    }

    return true;
}

void ScalarConverter::convert(const std::string &raw) {
    ScalarConverter::InputType input_type = detectInputType(raw);
    switch (input_type) {
        case ScalarConverter::InputChar:
            print(raw[0]);

            break;
        case ScalarConverter::InputInt: {
            int number = 0;

            if (!parseInt(raw, number)) {
                std::cout << "Error: The provided input is not a valid "
                             "char/int/float/double: `"
                          << raw << "`" << std::endl;

                return;
            }

            print(number);

            break;
        }
        case ScalarConverter::InputFloat:
            std::cout << "Input is float" << std::endl;
            break;
        case ScalarConverter::InputDouble:
            std::cout << "Input is double" << std::endl;
            break;
        case ScalarConverter::InputInvalid:
            std::cout << "Error: The provided input is not a valid "
                         "char/int/float/double: `"
                      << raw << "`" << std::endl;

            return;
    }
}
