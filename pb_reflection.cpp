//
// Created by icejoywoo on 2018/5/10.
//

#include <iostream>
#include <fstream>

#include "google/protobuf/descriptor.h"
#include "google/protobuf/dynamic_message.h"
#include "google/protobuf/compiler/importer.h"

int main() {
    std::string schema = "proto/person.proto;Person";
    // parse schema
    int pos = schema.find_first_of(';');
    if (std::string::npos == pos) {
        printf("%s is illega schema. Can't find delimiter \";\"!\n", schema.c_str());
        return 1;
    }
    std::string file = schema.substr(0, pos);
    std::string entry_message = schema.substr(pos + 1);
    ///< add by wenjurong
    if (entry_message.size() > 0 &&  entry_message[entry_message.size() - 1] == '\n') {
        entry_message.erase(entry_message.size() - 1, 1);
    }

    printf("schema: %s, file: %s, entry_message: %s\n", schema.c_str(), file.c_str(), entry_message.c_str());

    google::protobuf::compiler::DiskSourceTree dst;
    dst.MapPath("", "");
    google::protobuf::compiler::Importer* m_importer = new google::protobuf::compiler::Importer(&dst, NULL);
    const google::protobuf::FileDescriptor *fd = m_importer->Import(file);
    if (NULL == fd) {
        printf("Get %s's FileDescripitor with entry message %s failed\n", file.c_str(), entry_message.c_str());
        return 1;
    }
    const google::protobuf::Descriptor *desc = fd->FindMessageTypeByName(entry_message);
    if (NULL == desc) {
        printf("Get entry message %s's descriptor from %s failed\n", entry_message.c_str(), file.c_str());
        return 1;
    }
    const google::protobuf::DescriptorPool *m_dpool = google::protobuf::DescriptorPool::generated_pool();
    google::protobuf::DynamicMessageFactory *m_factory = new google::protobuf::DynamicMessageFactory(m_dpool);
    google::protobuf::Message *message = m_factory->GetPrototype(desc)->New();

    std::fstream input("./person.pb.dat", std::ios::in | std::ios::binary);
    message->ParseFromIstream(&input);

    const google::protobuf::Reflection *reflection = message->GetReflection();
    const google::protobuf::FieldDescriptor *name_field = message->GetDescriptor()->FindFieldByName("name");
    const google::protobuf::FieldDescriptor *id_field = message->GetDescriptor()->FindFieldByName("id");
    const google::protobuf::FieldDescriptor *email_field = message->GetDescriptor()->FindFieldByName("email");

    std::cout << "name: " << (name_field->cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_STRING)
              << ", value: " << reflection->GetString(*message, name_field) << std::endl;
    std::cout << "id: " << (id_field->cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_INT32)
              << ", value: " << reflection->GetInt32(*message, id_field) << std::endl;
    std::cout << "email: " << (email_field->cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_STRING)
              << ", value: " << reflection->GetString(*message, email_field) << std::endl;

    return 0;
}