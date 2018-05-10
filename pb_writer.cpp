//
// Created by icejoywoo on 2018/5/10.
//

#include <iostream>
#include <fstream>
#include <string>

#include "person.pb.h"

using namespace std;

int main() {
    // Verify that the version of the library that we linked against is
    // compatible with the version of the headers we compiled against.
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    tutorial::Person person;
    person.set_name("John");
    person.set_id(5);
    person.set_email("john@gmail.com");

    fstream output("./person.pb.dat", ios::out | ios::trunc | ios::binary);
    if (!person.SerializeToOstream(&output)) {
        cerr << "Failed to write address book." << endl;
        return -1;
    }

    return 0;
}