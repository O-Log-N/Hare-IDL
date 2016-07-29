
cmake_minimum_required(VERSION 3.2)

# project("test-basic-types")

add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/output.cpp ${CMAKE_CURRENT_SOURCE_DIR}/output.h
                   COMMAND generate.bat
                   MAIN_DEPENDENCY test.h
                   WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                   COMMENT "Generating CXX sources"
)

add_executable(testBasicTypes
  main.cpp
  test.h
  output.h
  output.cpp
  ../../../../src/targets/cpp/include/protobuf/baselib.h
  ../../../../src/targets/cpp/libsrc/protobuf/baselib.cpp
)

# SET(gtest_force_shared_crt ON CACHE BOOL "Use shared (DLL) run-time lib even when Google Test is built as static lib.")
# add_subdirectory(../../../../3rdparty/googletest/googletest googletest)

include_directories(
  ../../../../src
  ../../../../src/targets/cpp/include
  ../../../../3rdparty/googletest/googletest/include
)

add_definitions(-D_SCL_SECURE_NO_WARNINGS)

target_link_libraries(testBasicTypes
  gtest
)

set_property(TARGET testBasicTypes PROPERTY CXX_STANDARD 11)
set_property(TARGET testBasicTypes PROPERTY CXX_STANDARD_REQUIRED ON)

