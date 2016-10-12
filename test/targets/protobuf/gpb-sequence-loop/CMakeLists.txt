
cmake_minimum_required(VERSION 3.2)

add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/output.cpp ${CMAKE_CURRENT_SOURCE_DIR}/output.h
                   ${CMAKE_CURRENT_SOURCE_DIR}/output.pb.h ${CMAKE_CURRENT_SOURCE_DIR}/output.pb.cc
                   ${CMAKE_CURRENT_SOURCE_DIR}/dbg_helpers.h
                   ${CMAKE_CURRENT_SOURCE_DIR}/dbg_proto_helpers.h
                   ${CMAKE_CURRENT_SOURCE_DIR}/output.proto
                   COMMAND generate.bat
                   MAIN_DEPENDENCY test.h
                   WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                   COMMENT "Generating CXX sources"
)

add_executable(testGpbSequenceLoop
  main.cpp
  test.h
  output.h
  output.cpp
  output.pb.h
  output.pb.cc
  dbg_helpers.h
  dbg_proto_helpers.h
  ../../../../src/targets/cpp/include/protobuf/baselib.h
  ../../../../src/targets/cpp/libsrc/protobuf/baselib.cpp
)

include_directories(
  ../../../../src
  ../../../../src/targets/cpp/include
  ../../../../3rdparty/googletest/googletest/include
  ../../../../3rdparty/protobuf/src
)

target_link_libraries(testGpbSequenceLoop
  gtest
  libprotobuf
  cppformat
)

set_property(TARGET testGpbSequenceLoop PROPERTY CXX_STANDARD 11)
set_property(TARGET testGpbSequenceLoop PROPERTY CXX_STANDARD_REQUIRED ON)

