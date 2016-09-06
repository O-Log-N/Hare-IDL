
cmake_minimum_required(VERSION 3.2)

add_custom_command(OUTPUT 
                   ${CMAKE_CURRENT_SOURCE_DIR}/output.cpp
                   ${CMAKE_CURRENT_SOURCE_DIR}/output.h
                   ${CMAKE_CURRENT_SOURCE_DIR}/dbg_helpers.h
                   BYPRODUCTS
                   ${CMAKE_CURRENT_SOURCE_DIR}/output_declare.h
                   ${CMAKE_CURRENT_SOURCE_DIR}/output.proto
                   ${CMAKE_CURRENT_SOURCE_DIR}/dbg_proto_helpers.h
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
  dbg_helpers.h
  ../../../../src/targets/cpp/include/protobuf/baselib.h
  ../../../../src/targets/cpp/libsrc/protobuf/baselib.cpp
)

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

