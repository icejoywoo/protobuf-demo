cmake_minimum_required(VERSION 2.8)
project(protobuf_demo)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(proto)
add_executable(demo main.cpp)
target_link_libraries(demo proto)

add_executable(pb_reflection pb_reflection.cpp)
target_link_libraries(pb_reflection protobuf)

add_executable(pb_writer pb_writer.cpp)
target_link_libraries(pb_writer proto)

# protobuf 编译参考：http://chen-tao.github.io/2015/11/07/cmakeprotoprotobuf-cpp/
# 使用 foreach 命令来编译 pb
#FILE(GLOB proto_files ${CMAKE_CURRENT_SOURCE_DIR}/proto/*.proto)
#FOREACH(proto_file ${proto_files})
#    STRING(REGEX REPLACE "[^/]proto" "" proto_file_name ${proto_file})
#    LIST(APPEND PROTO_SRCS "${proto_file_name}.pb.cc")
#    ADD_CUSTOM_COMMAND(
#            OUTPUT "${proto_file_name}.pb.h" "${proto_file_name}.pb.cc"
#            COMMAND protoc --proto_path=${CMAKE_CURRENT_SOURCE_DIR}/proto
#            --cpp_out=${CMAKE_CURRENT_SOURCE_DIR}/proto/ ${proto_file}
#            DEPENDS ${proto_file}
#    )
#ENDFOREACH(proto_file)
#message(STATUS ${PROTO_SRCS})
#include_directories(proto)
#add_executable(demo main.cpp ${PROTO_SRCS})
#target_link_libraries(demo protobuf)

