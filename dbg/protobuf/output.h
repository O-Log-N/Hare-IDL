
#ifndef OUTPUT_H_INCLUDED
#define OUTPUT_H_INCLUDED

#include "protobuf/baselib.h"

// DECLARATIONS

// objects

struct Item;
struct Character;

//  INCLUDE TEMPLATE="SMART-DECLARING-ENTRY" PARAM-ROOT=PARAM-ROOT
  
// functions
    
// serialization
void serializeItem( Item& s, OStream& o );
void serializeCharacter( Character& s, OStream& o );
// deserialization
bool deserializeItem( Item& s, IStream& i );
bool deserializeCharacter( Character& s, IStream& i );
// printing
void printItem( Item& s );
void printCharacter( Character& s );
// GET-SIZE
size_t getSizeItem( const Item& s );
size_t getSizeCharacter( const Character& s );

#endif // OUTPUT_H_INCLUDED

