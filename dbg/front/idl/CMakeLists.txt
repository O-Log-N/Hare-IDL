
cmake_minimum_required(VERSION 3.2)

project("dbg-front-idl")

add_executable(dbgFrontIdl
  main.cpp
)

add_subdirectory(../../../src/front/idl idl)
add_subdirectory(../../../3rdparty/cppformat cppformat)
add_subdirectory(../../../3rdparty/tiny-process-library tiny-process-library)
add_subdirectory(../../front-back dbg-front-back)

include_directories(../../../src)

target_link_libraries(dbgFrontIdl
  front-idl
  cppformat
  tiny-process-library
  dbg-front-back
)

# file(COPY sample.idl DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# install(TARGETS hare RUNTIME DESTINATION bin)
