#include <iostream>

#include "person.pb.h"

int main() {
    // Verify that the version of the library that we linked against is
    // compatible with the version of the headers we compiled against.
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    tutorial::Person person;
    person.set_name("John");
    person.set_id(5);
    person.set_email("john@gmail.com");

    std::cout << person.DebugString() << std::endl;

    std::cout << "Hello, World!" << std::endl;
    return 0;
}