#include <iostream>

#include "Data.hpp"
#include "Serializer.hpp"
#include "assert.hpp"

int main() {
    Data *data = new Data(42, "Marvin");

    std::cout << "Original: " << data << " => " << *data << std::endl;

    uintptr_t fake_serialized = Serializer::serialize(data);

    Data *fake_deserialized = Serializer::deserialize(fake_serialized);

    std::cout << "Fake    : " << fake_deserialized << " => "
              << *fake_deserialized << std::endl;

    std::cout << "Fake Serialized: " << fake_serialized << std::endl;

    std::cout << "Original PTR       : " << data << std::endl;
    std::cout << "Fake Serialized HEX: 0x" << std::hex << fake_serialized
              << std::endl;

    ASSERT_EQ(data, fake_deserialized,
              "Serialize & Deserialize should result in same pointer");

    delete data;
}
