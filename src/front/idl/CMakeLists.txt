
add_library(idl-front
    hare-idl.tab.cpp
    hare-idl.tab.h
    lex.h
    lex.yy.cpp
    parser.h
    parser_helper.cpp
    parser_helper.h
)

target_link_libraries(idl-front
  cppformat
  idl-front-back
  tiny-process-library
)

set_property(TARGET idl-front PROPERTY CXX_STANDARD 11)
set_property(TARGET idl-front PROPERTY CXX_STANDARD_REQUIRED ON)
