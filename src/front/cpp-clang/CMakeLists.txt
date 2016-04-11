
cmake_minimum_required(VERSION 3.2)

add_library(front-cpp-clang
  cpp-parser.h
  cpp-parser.cpp
)

add_subdirectory(../../../3rdparty/llvm llvm EXCLUDE_FROM_ALL)

include_directories(../../../3rdparty/llvm/include)
include_directories(../../../3rdparty/llvm/tools/clang/include)
include_directories(${CMAKE_CURRENT_BINARY_DIR}/llvm/include)
include_directories(${CMAKE_CURRENT_BINARY_DIR}/llvm/tools/clang/include)

target_link_libraries(front-cpp-clang
  clangAST
  clangBasic
  clangDriver
  clangFrontend
  clangRewriteFrontend
  clangStaticAnalyzerFrontend
  clangTooling
)

