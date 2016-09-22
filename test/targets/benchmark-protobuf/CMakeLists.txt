
cmake_minimum_required(VERSION 3.2)

project("benchmark-protobuf")

set(CMAKE_BUILD_TYPE Release)

foreach(flag_var
    CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_RELEASE)
  if(${flag_var} MATCHES "/MD")
    string(REGEX REPLACE "/MD" "/MT" ${flag_var} "${${flag_var}}")
  endif()
endforeach()

SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} /Ox /GL" )
SET( CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} /LTCG" )

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

