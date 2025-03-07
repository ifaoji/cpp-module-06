#include "Serializer.hpp"

Serializer::Serializer() {
}

Serializer::Serializer(const Serializer &) {
}

Serializer::~Serializer() {
}

Serializer &Serializer::operator=(const Serializer &) {
    return *this;
}

uintptr_t Serializer::serialize(Data *ptr) {
    uintptr_t as_number = reinterpret_cast<uintptr_t>(ptr);

    return as_number;
}

Data *Serializer::deserialize(uintptr_t raw) {
    Data *as_data = reinterpret_cast<Data *>(raw);

    return as_data;
}
