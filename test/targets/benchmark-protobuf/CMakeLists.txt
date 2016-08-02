
cmake_minimum_required(VERSION 3.2)

project("benchmark-protobuf")

set(CMAKE_BUILD_TYPE Release)

# SET(protobuf_BUILD_TESTS OFF CACHE BOOL "Build tests")
# SET(protobuf_MSVC_STATIC_RUNTIME OFF CACHE BOOL "Link static runtime libraries")
# add_subdirectory(../../../3rdparty/protobuf/cmake protobuf)

add_subdirectory(../../../3rdparty/benchmark benchmark)

add_executable(benchmarkProtobuf
  main.cpp
  ../../../src/targets/cpp/include/protobuf/baselib.h
  ../../../src/targets/cpp/libsrc/protobuf/baselib.cpp
  ../../../src/targets/cpp/include/protobuf/baselib2.h
  ../../../src/targets/cpp/libsrc/protobuf/baselib2.cpp
)

include_directories(
  ../../../src
  ../../../src/targets/cpp/include
  ../../../3rdparty/benchmark/include
)

add_definitions(-D_SCL_SECURE_NO_WARNINGS)

target_link_libraries(benchmarkProtobuf
  benchmark
)

set_property(TARGET benchmarkProtobuf PROPERTY CXX_STANDARD 11)
set_property(TARGET benchmarkProtobuf PROPERTY CXX_STANDARD_REQUIRED ON)

