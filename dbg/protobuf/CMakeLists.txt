
cmake_minimum_required(VERSION 3.2)

project("dbg-protobuf")

SET(protobuf_BUILD_TESTS OFF CACHE BOOL "Build tests")
SET(protobuf_MSVC_STATIC_RUNTIME OFF CACHE BOOL "Link static runtime libraries")
add_subdirectory(../../3rdparty/protobuf/cmake protobuf)

add_executable(dbgProtobuf
  main.cpp
  sample.h
  output.h
  output.cpp
  output.pb.h
  output.pb.cc
  dbg_assert_equal.h
  dbg_print.h
  ../../src/front-back/idl_tree.h
  ../../src/front-back/idl_tree_serializer.cpp
  ../../src/front-back/idl_tree_serializer.h
  ../../src/targets/cpp/include/protobuf/baselib.h
  ../../src/targets/cpp/libsrc/protobuf/baselib.cpp
)

include_directories(
  ../../src
  ../../src/targets/cpp/include
  ../../3rdparty/protobuf/src
)

add_definitions(-D_SCL_SECURE_NO_WARNINGS)

target_link_libraries(dbgProtobuf
  libprotobuf
)

set_property(TARGET dbgProtobuf PROPERTY CXX_STANDARD 11)
set_property(TARGET dbgProtobuf PROPERTY CXX_STANDARD_REQUIRED ON)

