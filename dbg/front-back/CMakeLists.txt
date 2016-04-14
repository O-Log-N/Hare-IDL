
cmake_minimum_required(VERSION 3.2)

add_library(dbg-front-back
  debug.h
  debug.cpp
)

include_directories(../../src)

set_property(TARGET dbg-front-back PROPERTY CXX_STANDARD 11)
set_property(TARGET dbg-front-back PROPERTY CXX_STANDARD_REQUIRED ON)

target_link_libraries(dbg-front-back
  cppformat
)

