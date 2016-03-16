
cmake_minimum_required(VERSION 3.5)

project("cpp-clang")

add_executable(hare
  main.cpp
)

add_subdirectory(../../../3rdparty/llvm llvm EXCLUDE_FROM_ALL)

include_directories(../../../3rdparty/llvm/include)
include_directories(../../../3rdparty/llvm/tools/clang/include)
include_directories(${CMAKE_BINARY_DIR}/llvm/include)
include_directories(${CMAKE_BINARY_DIR}/llvm/tools/clang/include)

target_link_libraries(hare
  clangAST
  clangBasic
  clangDriver
  clangFrontend
  clangRewriteFrontend
  clangStaticAnalyzerFrontend
  clangTooling
)

install(TARGETS hare RUNTIME DESTINATION bin)
