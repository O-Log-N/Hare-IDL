
cmake_minimum_required(VERSION 3.2)

project("dbg-front-idl")

add_executable(dbgFrontIdl
  main.cpp
  debug.cpp
  debug.h
)

add_subdirectory(../../../src/front/idl idl)
add_subdirectory(../../../3rdparty/cppformat cppformat)

include_directories(../../../src)

target_link_libraries(dbgFrontIdl
  front-idl
  cppformat
)

# file(COPY sample.idl DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# install(TARGETS hare RUNTIME DESTINATION bin)
