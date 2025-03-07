#include "Data.hpp"

Data::Data() : foo_(0), bar_("") {
}

Data::Data(int foo, const std::string &bar) : foo_(foo), bar_(bar) {
}

Data::Data(const Data &other) : foo_(other.foo_), bar_(other.bar_) {
}

Data::~Data() {
}

Data &Data::operator=(const Data &) {
    return *this;
}

int Data::getFoo() const {
    return foo_;
}

const std::string &Data::getBar() const {
    return bar_;
}

std::ostream &operator<<(std::ostream &os, const Data &data) {
    os << "Data { foo: " << data.getFoo() << ", bar: \"" << data.getBar()
       << "\" }";

    return os;
}
