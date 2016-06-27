
cmake_minimum_required(VERSION 3.2)

project("dbg-protobuf")

link_directories(../../../protobuf/protobuf-2.6.1/vsprojects/Debug)

add_executable(dbgProtobuf
  main.cpp
  output.h
  output.cpp
  output.pb.h
  output.pb.cc
  ../../src/targets/cpp/include/protobuf/baselib.h
  ../../src/targets/cpp/libsrc/protobuf/baselib.cpp
)

include_directories(
  ../../src
  ../../src/targets/cpp/include
  ../../../protobuf/protobuf-2.6.1/src
)

add_definitions(-D_SCL_SECURE_NO_WARNINGS)

target_link_libraries(dbgProtobuf
  libprotobuf
)

set_property(TARGET dbgProtobuf PROPERTY CXX_STANDARD 11)
set_property(TARGET dbgProtobuf PROPERTY CXX_STANDARD_REQUIRED ON)

