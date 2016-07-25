
cmake_minimum_required(VERSION 3.2)

project("dbg-front-idl")

add_executable(dbgFrontIdl
  main.cpp
)

add_subdirectory(../../../src/front/idl idl)
add_subdirectory(../../../src/front-back front-back)
add_subdirectory(../../../3rdparty/cppformat cppformat)
add_subdirectory(../../../3rdparty/tiny-process-library tiny-process-library)
add_subdirectory(../../front-back dbg-front-back)

include_directories(../../../src)

target_link_libraries(dbgFrontIdl
  idl-front
  dbg-front-back
  idl-front-back
)

set_property(TARGET dbgFrontIdl PROPERTY CXX_STANDARD 11)
set_property(TARGET dbgFrontIdl PROPERTY CXX_STANDARD_REQUIRED ON)

