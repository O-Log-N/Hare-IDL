
cmake_minimum_required(VERSION 3.2)

project("dbg-protobuf")

SET(protobuf_BUILD_TESTS OFF CACHE BOOL "Build tests")
SET(protobuf_MSVC_STATIC_RUNTIME OFF CACHE BOOL "Link static runtime libraries")
add_subdirectory(../../3rdparty/protobuf/cmake protobuf)
add_subdirectory(../../3rdparty/cppformat cppformat)

SET(BASELIB_INCLUDE ../../src/targets/cpp/baselib_mb)
SET(BASELIB_CPP ../../src/targets/cpp/baselib_mb)

#SET(BASELIB_INCLUDE ../../src/targets/cpp/include)
#SET(BASELIB_CPP ../../src/targets/cpp/libsrc)


add_executable(dbgProtobuf
  main.cpp
  sample.h
  output.h
  output.cpp
  output.pb.h
  output.pb.cc
  dbg_helpers.h
  dbg_proto_helpers.h
  ${BASELIB_INCLUDE}/protobuf/baselib.h
  ${BASELIB_CPP}/protobuf/baselib.cpp
)

include_directories(
  ../../src
  ${BASELIB_INCLUDE}
  ../../3rdparty/protobuf/src
)

target_link_libraries(dbgProtobuf
  libprotobuf
  cppformat
)

set_property(TARGET dbgProtobuf PROPERTY CXX_STANDARD 11)
set_property(TARGET dbgProtobuf PROPERTY CXX_STANDARD_REQUIRED ON)

