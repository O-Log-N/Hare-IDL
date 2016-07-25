
#ifndef OUTPUT_H_INCLUDED
#define OUTPUT_H_INCLUDED

#include "test.h"

class OProtobufStream;
class IProtobufStream;

// DECLARATIONS

// objects

//  INCLUDE TEMPLATE="FORWARD-DECLARING" PARAM-ROOT=PARAM-ROOT

//  INCLUDE TEMPLATE="SMART-DECLARING-ENTRY" PARAM-ROOT=PARAM-ROOT
  
// functions
    
// serialization
void serializeTestClass( const TestClass& s, OProtobufStream& o );
// deserialization
bool deserializeTestClass( TestClass& s, IProtobufStream& i );
// printing
//  INCLUDE TEMPLATE="PRINTING-GENERATE-DECLARATIONS" PARAM-ROOT=PARAM-ROOT
// GET-SIZE
size_t protobufGetSizeTestClass( const TestClass& s );

#endif // OUTPUT_H_INCLUDED

