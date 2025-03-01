#pragma once

#ifndef SCALAR_CONVERTER_HPP_
#    define SCALAR_CONVERTER_HPP_

#    include <string>

class ScalarConverter {
   public:
    static void convert(const std::string &raw);

   private:
    ScalarConverter();
    ScalarConverter(const ScalarConverter &other);

    ~ScalarConverter();

    ScalarConverter &operator=(const ScalarConverter &rhs);

    enum InputType {
        InputChar,
        InputInt,
        InputFloat,
        InputDouble,
        InputInvalid,
    };

    static InputType detectInputType(const std::string &input);
    static bool      isCharInput(const std::string &raw);
};

#endif
