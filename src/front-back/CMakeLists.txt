
add_library(idl-front-back
    idl_tree.h
    idl_tree_serializer.cpp
    idl_tree_serializer.h
    raiistdiofile.h
)

target_link_libraries(idl-front-back
  cppformat
)

set_property(TARGET idl-front-back PROPERTY CXX_STANDARD 11)
set_property(TARGET idl-front-back PROPERTY CXX_STANDARD_REQUIRED ON)
