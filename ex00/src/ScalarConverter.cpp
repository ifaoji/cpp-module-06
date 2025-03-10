#include <cerrno>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <limits>

#include "Numbers.hpp"
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

static bool parseInt(const std::string &raw, int &result) {
    errno         = 0;
    char *end_ptr = NULL;
    long  parsed  = strtol(raw.c_str(), &end_ptr, 10);

    const bool is_at_end = *end_ptr == '\0';
    if (!is_at_end) {
        return false;
    }

    // `strtol` stops at long min/max, therefore a check with int limits is safe
    const bool underflow = parsed < std::numeric_limits<int>().min();
    const bool overflow  = parsed > std::numeric_limits<int>().max();
    if (underflow || overflow || errno == ERANGE) {
        return false;
    }

    result = static_cast<int>(parsed);

    return true;
}

static bool parseFloat(const std::string &raw, float &result) {
    errno         = 0;
    char *end_ptr = NULL;
    result        = strtof(raw.c_str(), &end_ptr);

    const bool is_at_end = end_ptr[0] == 'f' && end_ptr[1] == '\0';
    if (!is_at_end) {
        return false;
    }

    if (errno == ERANGE) {
        return false;
    }

    return true;
}

static bool parseDouble(const std::string &raw, double &result) {
    errno         = 0;
    char *end_ptr = NULL;
    result        = strtod(raw.c_str(), &end_ptr);

    const bool is_at_end = *end_ptr == '\0';
    if (!is_at_end) {
        return false;
    }

    if (errno == ERANGE) {
        return false;
    }

    return true;
}

void ScalarConverter::convert(const std::string &raw) {
    ScalarConverter::InputType input_type = detectInputType(raw);
    switch (input_type) {
        case ScalarConverter::InputChar: {
            Numbers(raw[0]).print();

            return;
        }
        case ScalarConverter::InputInt: {
            int number = 0;

            if (!parseInt(raw, number)) {
                break;
            }

            Numbers(number).print();

            return;
        }
        case ScalarConverter::InputFloat: {
            float number = 0.0f;

            if (!parseFloat(raw, number)) {
                break;
            }

            Numbers(number).print();

            return;
        }
        case ScalarConverter::InputDouble: {
            double number = 0.0f;

            if (!parseDouble(raw, number)) {
                break;
            }

            Numbers(number).print();

            return;
        }
        case ScalarConverter::InputInvalid:
            break;
    }

    std::cout << "Error: The provided input is not a valid "
                 "char/int/float/double: `"
              << raw << "`" << std::endl;
}
