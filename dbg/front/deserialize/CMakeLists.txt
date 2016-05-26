
cmake_minimum_required(VERSION 3.2)

project("dbg-deserialize")

add_executable(dbgDeserialize
  main.cpp
  ../../../src/front-back/idl_tree_serializer.cpp
)

add_subdirectory(../../../3rdparty/cppformat cppformat)
add_subdirectory(../../front-back dbg-front-back)

include_directories(../../../src)

target_link_libraries(dbgDeserialize
  dbg-front-back
)

set_property(TARGET dbgDeserialize PROPERTY CXX_STANDARD 11)
set_property(TARGET dbgDeserialize PROPERTY CXX_STANDARD_REQUIRED ON)

# file(COPY sample.idl DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# install(TARGETS hare RUNTIME DESTINATION bin)
