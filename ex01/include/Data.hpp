#pragma once

#ifndef DATA_HPP_
#    define DATA_HPP_

#    include <iostream>
#    include <string>

struct Data {
   public:
    Data(int foo, const std::string &bar);
    Data(const Data &other);

    ~Data();

    int                getFoo() const;
    const std::string &getBar() const;

   private:
    Data();
    Data &operator=(const Data &rhs);

    const int         foo_;
    const std::string bar_;
};

std::ostream &operator<<(std::ostream &os, const Data &data);

#endif
