
cmake_minimum_required(VERSION 3.2)

project("test-protobuf")

SET(gtest_force_shared_crt ON CACHE BOOL "Use shared (DLL) run-time lib even when Google Test is built as static lib.")
add_subdirectory(../../../3rdparty/googletest/googletest googletest)

SET(protobuf_BUILD_TESTS OFF CACHE BOOL "Build tests")
SET(protobuf_MSVC_STATIC_RUNTIME OFF CACHE BOOL "Link static runtime libraries")
add_subdirectory(../../../3rdparty/protobuf/cmake protobuf)

add_subdirectory(../../../3rdparty/cppformat cppformat)

#SET(BASELIB_INCLUDE ../../../../src/targets/cpp/baselib_mb)
#SET(BASELIB_CPP ../../../../src/targets/cpp/baselib_mb)

SET(BASELIB_INCLUDE ../../../../src/targets/cpp/include)
SET(BASELIB_CPP ../../../../src/targets/cpp/libsrc)


add_subdirectory(basic-types)
add_subdirectory(discriminated-union)
add_subdirectory(extrapolation)
add_subdirectory(gpb-idl-tree)
add_subdirectory(gpb-loop)
add_subdirectory(gpb-sequence-loop)
add_subdirectory(idl-primitive)
add_subdirectory(packed-sequence)
add_subdirectory(poly-ptr)

configure_file(run_all.bat . COPYONLY)
