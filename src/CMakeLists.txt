
cmake_minimum_required(VERSION 3.2)

project("hare-idl")

add_executable(hare-idl
  main.cpp
)

add_subdirectory(front/idl)
add_subdirectory(front-back)
add_subdirectory(back)
add_subdirectory(../3rdparty/tiny-process-library tiny-process-library)
add_subdirectory(../3rdparty/cppformat cppformat)

target_link_libraries(hare-idl
    idl-front
    idl-front-back
    idl-back
)

set_property(TARGET hare-idl PROPERTY CXX_STANDARD 11)
set_property(TARGET hare-idl PROPERTY CXX_STANDARD_REQUIRED ON)
