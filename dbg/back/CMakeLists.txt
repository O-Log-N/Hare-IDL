
cmake_minimum_required(VERSION 3.2)

project("dbg-back")

add_executable(dbgBack
  main.cpp
)

add_subdirectory(../../src/back back)
add_subdirectory(../../src/front-back front-back)
add_subdirectory(../../3rdparty/cppformat cppformat)
add_subdirectory(../front-back dbg-front-back)

include_directories(../../src)

target_link_libraries(dbgBack
  idl-back
  idl-front-back
  dbg-front-back
)

set_property(TARGET dbgBack PROPERTY CXX_STANDARD 11)
set_property(TARGET dbgBack PROPERTY CXX_STANDARD_REQUIRED ON)
