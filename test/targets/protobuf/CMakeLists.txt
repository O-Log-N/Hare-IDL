
cmake_minimum_required(VERSION 3.2)

project("test-protobuf")

SET(gtest_force_shared_crt ON CACHE BOOL "Use shared (DLL) run-time lib even when Google Test is built as static lib.")
add_subdirectory(../../../3rdparty/googletest/googletest googletest)

add_subdirectory(basic-types)
add_subdirectory(packed-sequence)
