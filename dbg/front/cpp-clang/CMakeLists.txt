
cmake_minimum_required(VERSION 3.2)

project("dbg-front-cpp-clang")

add_executable(dbgFrontCppClang
  main.cpp
)

add_subdirectory(../../front-back dbg-front-back)
add_subdirectory(../../../src/front/cpp-clang cpp-clang)
add_subdirectory(../../../3rdparty/cppformat cppformat)

include_directories(../../../src)

target_link_libraries(dbgFrontCppClang
  front-cpp-clang
  cppformat
  dbg-front-back
)



# file(COPY sample.idl DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# install(TARGETS hare RUNTIME DESTINATION bin)
