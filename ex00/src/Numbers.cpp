#include <cmath>
#include <iostream>
#include <limits>

#include "Numbers.hpp"

Numbers::Numbers()
    : has_char_(false),
      has_int_(false),
      has_float_(false),
      has_double_(false),
      c_('\0'),
      i_(0),
      f_(0.0f),
      d_(0.0) {
}

Numbers::Numbers(const Numbers &other)
    : has_char_(other.has_char_),
      has_int_(other.has_int_),
      has_float_(other.has_float_),
      has_double_(other.has_double_),
      c_(other.c_),
      i_(other.i_),
      f_(other.f_),
      d_(other.d_) {
}

Numbers::~Numbers() {
}

Numbers &Numbers::operator=(const Numbers &) {
    return (*this);
}

Numbers::Numbers(char c)
    : has_char_(true),
      has_int_(true),
      has_float_(true),
      has_double_(true),
      c_(c),
      i_(static_cast<int>(c)),
      f_(static_cast<float>(c)),
      d_(static_cast<double>(c)) {
}

Numbers::Numbers(int i)
    : has_char_(false),
      has_int_(true),
      has_float_(true),
      has_double_(true),
      c_('\0'),
      i_(i),
      f_(static_cast<float>(i)),
      d_(static_cast<double>(i)) {
    const bool fits_in_char =
        i_ >= static_cast<int>(std::numeric_limits<char>().min()) &&
        i_ <= static_cast<int>(std::numeric_limits<char>().max());
    if (!fits_in_char) {
        return;
    }

    has_char_ = true;
    c_        = static_cast<char>(i_);
}

Numbers::Numbers(float f)
    : has_char_(false),
      has_int_(false),
      has_float_(true),
      has_double_(true),
      c_('\0'),
      i_(0),
      f_(f),
      d_(static_cast<double>(f)) {
    // Floats with fractions cannot be properly stored in an int
    float integral;
    bool  has_fraction = std::modf(f_, &integral) != 0.0;
    if (has_fraction) {
        return;
    }

    const bool fits_in_int =
        f_ >= static_cast<float>(std::numeric_limits<int>().min()) &&
        f_ <= static_cast<float>(std::numeric_limits<int>().max());
    if (!fits_in_int) {
        return;
    }

    has_int_ = true;
    i_       = static_cast<int>(f_);

    const bool fits_in_char =
        i_ >= static_cast<int>(std::numeric_limits<char>().min()) &&
        i_ <= static_cast<int>(std::numeric_limits<char>().max());
    if (!fits_in_char) {
        return;
    }

    has_char_ = true;
    c_        = static_cast<char>(i_);
}

Numbers::Numbers(double d)
    : has_char_(false),
      has_int_(false),
      has_float_(false),
      has_double_(true),
      c_('\0'),
      i_(0),
      f_(0.0f),
      d_(d) {
    const bool is_nan = d != d;
    if (is_nan) {
        has_float_ = true;
        f_         = std::numeric_limits<float>().quiet_NaN();

        return;
    }

    const bool is_infinity = d == std::numeric_limits<double>().infinity() ||
                             d == -std::numeric_limits<double>().infinity();
    if (is_infinity) {
        has_float_ = true;
        if (d >= 0) {
            f_ = std::numeric_limits<float>().infinity();
        } else {
            f_ = -std::numeric_limits<float>().infinity();
        }

        return;
    }

    const bool fits_in_float =
        d >= static_cast<double>(std::numeric_limits<float>().min()) &&
        d <= static_cast<double>(std::numeric_limits<float>().max());
    if (!fits_in_float) {
        return;
    }

    has_float_ = true;
    f_         = static_cast<float>(d);

    // Floats with fractions cannot be properly stored in an int
    float integral;
    bool  has_fraction = std::modf(f_, &integral) != 0.0;
    if (has_fraction) {
        return;
    }

    const bool fits_in_int =
        f_ >= static_cast<float>(std::numeric_limits<int>().min()) &&
        f_ <= static_cast<float>(std::numeric_limits<int>().max());
    if (!fits_in_int) {
        return;
    }

    has_int_ = true;
    i_       = static_cast<int>(f_);

    const bool fits_in_char =
        i_ >= static_cast<int>(std::numeric_limits<char>().min()) &&
        i_ <= static_cast<int>(std::numeric_limits<char>().max());
    if (!fits_in_char) {
        return;
    }

    has_char_ = true;
    c_        = static_cast<char>(i_);
}

void Numbers::print() const {
    std::cout << "char: ";
    if (!has_char_) {
        std::cout << "impossible" << std::endl;
    } else {
        if (std::isprint(c_)) {
            std::cout << "'" << c_ << "'" << std::endl;
        } else {
            std::cout << "Non displayable" << std::endl;
        }
    }

    std::cout << "int: ";
    if (!has_int_) {
        std::cout << "impossible" << std::endl;
    } else {
        std::cout << i_ << std::endl;
    }

    std::cout << "float: ";
    if (!has_float_) {
        std::cout << "impossible" << std::endl;
    } else {
        std::cout << f_ << std::endl;
    }

    std::cout << "double: ";
    if (!has_char_) {
        std::cout << "impossible" << std::endl;
    } else {
        std::cout << d_ << std::endl;
    }
}
