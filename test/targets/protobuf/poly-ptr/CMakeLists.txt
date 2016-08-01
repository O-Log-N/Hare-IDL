
cmake_minimum_required(VERSION 3.2)

add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/output.cpp ${CMAKE_CURRENT_SOURCE_DIR}/output.h
                   BYPRODUCTS ${CMAKE_CURRENT_SOURCE_DIR}/output.proto
                   COMMAND generate.bat
                   MAIN_DEPENDENCY test.h
                   WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                   COMMENT "Generating CXX sources"
)

add_executable(testPolyPtr
  main.cpp
  test.h
  output.h
  output.cpp
  ../../../../src/targets/cpp/include/protobuf/baselib.h
  ../../../../src/targets/cpp/libsrc/protobuf/baselib.cpp
)

include_directories(
  ../../../../src
  ../../../../src/targets/cpp/include
  ../../../../3rdparty/googletest/googletest/include
)

add_definitions(-D_SCL_SECURE_NO_WARNINGS)

target_link_libraries(testPolyPtr
  gtest
)

set_property(TARGET testPolyPtr PROPERTY CXX_STANDARD 11)
set_property(TARGET testPolyPtr PROPERTY CXX_STANDARD_REQUIRED ON)

