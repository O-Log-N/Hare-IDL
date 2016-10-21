
cmake_minimum_required(VERSION 3.2)

add_custom_command(OUTPUT 
                   ${CMAKE_CURRENT_SOURCE_DIR}/output.cpp
                   ${CMAKE_CURRENT_SOURCE_DIR}/output.h
                   ${CMAKE_CURRENT_SOURCE_DIR}/output.pb.cpp
                   ${CMAKE_CURRENT_SOURCE_DIR}/output.pb.h
                   ${CMAKE_CURRENT_SOURCE_DIR}/dbg_helpers.h
                   BYPRODUCTS
                   ${CMAKE_CURRENT_SOURCE_DIR}/output_declare.h
                   ${CMAKE_CURRENT_SOURCE_DIR}/output.proto
                   ${CMAKE_CURRENT_SOURCE_DIR}/dbg_proto_helpers.h
                   COMMAND generate.bat
                   MAIN_DEPENDENCY idl_tree.h
                   WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                   COMMENT "Generating CXX sources"
)

add_executable(testGpbIdlTree
  main.cpp
  idl_tree.h
  output.h
  output.cpp
  output.pb.h
  output.pb.cc
  dbg_helpers.h
  ${BASELIB_INCLUDE}/protobuf/baselib.h
  ${BASELIB_CPP}/protobuf/baselib.cpp
)

include_directories(
  ../../../../src
  ${BASELIB_INCLUDE}
  ../../../../3rdparty/googletest/googletest/include
  ../../../../3rdparty/protobuf/src
)

target_link_libraries(testGpbIdlTree
  gtest
  libprotobuf
  cppformat
)

set_property(TARGET testGpbIdlTree PROPERTY CXX_STANDARD 11)
set_property(TARGET testGpbIdlTree PROPERTY CXX_STANDARD_REQUIRED ON)

