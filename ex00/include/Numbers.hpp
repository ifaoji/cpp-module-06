#pragma once

#ifndef NUMBERS_HPP_
#    define NUMBERS_HPP_

class Numbers {
   public:
    Numbers(char c);
    Numbers(int i);
    Numbers(float f);
    Numbers(double d);
    Numbers(const Numbers &other);

    ~Numbers();

    void print() const;

   private:
    Numbers();
    Numbers &operator=(const Numbers &rhs);

    bool has_char_;
    bool has_int_;
    bool has_float_;
    bool has_double_;

    char   c_;
    int    i_;
    float  f_;
    double d_;
};

#endif
