find_package(Protobuf REQUIRED)
#link_libraries(${Protobuf})
message(STATUS "check protoc path: " ${PROTOBUF_PROTOC_EXECUTABLE})

FILE(GLOB protofiles "${CMAKE_CURRENT_SOURCE_DIR}/*.proto")
message(STATUS "proto files: " ${protofiles})

PROTOBUF_GENERATE_CPP(PROTOSRCS PROTOHDRS ${protofiles})
message(STATUS "proto headers: " ${PROTOHDRS})
message(STATUS "proto srcs: " ${PROTOSRCS})

add_library(proto STATIC ${PROTOSRCS} ${PROTOHDRS})
target_link_libraries(proto protobuf)
target_include_directories(proto PUBLIC ${CMAKE_CURRENT_BINARY_DIR})