
cmake_minimum_required(VERSION 3.2)

project("benchmark-protobuf")

set(CMAKE_BUILD_TYPE Release)

if(WIN32)
 
  foreach(flag_var
      CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_RELEASE)
    if(${flag_var} MATCHES "/MD")
      string(REGEX REPLACE "/MD" "/MT" ${flag_var} "${${flag_var}}")
    endif()
  endforeach()

  SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} /Ox /GL" )
  SET( CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} /LTCG" )
endif()

if(UNIX)
  SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -m64 -Ofast -march=native -funroll-loops" )
endif()


# SET(protobuf_BUILD_TESTS OFF CACHE BOOL "Build tests")
# SET(protobuf_MSVC_STATIC_RUNTIME OFF CACHE BOOL "Link static runtime libraries")
# add_subdirectory(../../../3rdparty/protobuf/cmake protobuf)

add_subdirectory(../../../3rdparty/benchmark benchmark EXCLUDE_FROM_ALL)

add_executable(benchmarkProtobuf
  main.cpp
  baselib_func_benchmark.h
  baselib_func_benchmark.cpp
)

include_directories(
  ../../../src
  ../../../src/targets/cpp/include
  ../../../3rdparty/benchmark/include
)

target_link_libraries(benchmarkProtobuf
  benchmark
)

set_property(TARGET benchmarkProtobuf PROPERTY CXX_STANDARD 11)
set_property(TARGET benchmarkProtobuf PROPERTY CXX_STANDARD_REQUIRED ON)

