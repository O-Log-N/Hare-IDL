
cmake_minimum_required(VERSION 3.2)

project("test-protobuf")

SET(gtest_force_shared_crt ON CACHE BOOL "Use shared (DLL) run-time lib even when Google Test is built as static lib.")
add_subdirectory(../../../3rdparty/googletest/googletest googletest)

SET(protobuf_BUILD_TESTS OFF CACHE BOOL "Build tests")
SET(protobuf_MSVC_STATIC_RUNTIME OFF CACHE BOOL "Link static runtime libraries")
add_subdirectory(../../../3rdparty/protobuf/cmake protobuf)

add_subdirectory(basic-types)
add_subdirectory(gpb-loop)
add_subdirectory(gpb-sequence-loop)
add_subdirectory(packed-sequence)
add_subdirectory(poly-ptr)

