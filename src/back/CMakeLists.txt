
add_library(idl-back
    back_idl_tree.cpp
    back_idl_tree.h
    idl_tree_finalizer.cpp
    idl_tree_finalizer.h
    idlc_back.cpp
    idlc_back.h
    template_instantiator.cpp
    template_instantiator.h
    template_instantiator_derived.cpp
    template_instantiator_derived.h
    template_line_tokenizer.cpp
    template_line_tokenizer.h
    template_line_tokens.cpp
    template_line_tokens.h
    template_tree_builder.cpp
    template_tree_builder.h
)

target_link_libraries(idl-back
  idl-front
  idl-front-back
  cppformat
)

set_property(TARGET idl-back PROPERTY CXX_STANDARD 11)
set_property(TARGET idl-back PROPERTY CXX_STANDARD_REQUIRED ON)
