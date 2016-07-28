
#ifndef OUTPUT_H_INCLUDED
#define OUTPUT_H_INCLUDED

#include "sample.h"

class OProtobufStream;
class IProtobufStream;

// DECLARATIONS

// objects

//  INCLUDE TEMPLATE="FORWARD-DECLARING" PARAM-ROOT=PARAM-ROOT

//  INCLUDE TEMPLATE="SMART-DECLARING-ENTRY" PARAM-ROOT=PARAM-ROOT
  
// functions
    
// serialization
void serializeRoot( const Root& s, OProtobufStream& o );
// deserialization
bool deserializeRoot( Root& s, IProtobufStream& i );
// printing
//  INCLUDE TEMPLATE="PRINTING-GENERATE-DECLARATIONS" PARAM-ROOT=PARAM-ROOT
// GET-SIZE
size_t protobufGetSizeRoot( const Root& s );

#endif // OUTPUT_H_INCLUDED

