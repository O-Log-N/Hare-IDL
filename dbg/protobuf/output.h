
#ifndef OUTPUT_H_INCLUDED
#define OUTPUT_H_INCLUDED

#include "protobuf/baselib.h"

// DECLARATIONS

// objects

struct ItemBase;
struct Item;
struct Character;
struct __unique_ptr_ItemBase;

//  INCLUDE TEMPLATE="SMART-DECLARING-ENTRY" PARAM-ROOT=PARAM-ROOT
  
// functions
    
// serialization
void serializeItemBase( const ItemBase& s, OStream& o );
void serializeItem( const Item& s, OStream& o );
void serializeCharacter( const Character& s, OStream& o );
void serialize__unique_ptr_ItemBase( const unique_ptr<ItemBase>& s, OStream& o );
// deserialization
bool deserializeItemBase( ItemBase& s, IStream& i );
bool deserializeItem( Item& s, IStream& i );
bool deserializeCharacter( Character& s, IStream& i );
bool deserialize__unique_ptr_ItemBase( unique_ptr<ItemBase>& s, IStream& i );
// printing
void printItemBase( const ItemBase& s );
void printItem( const Item& s );
void printCharacter( const Character& s );
void print__unique_ptr_ItemBase( unique_ptr<ItemBase>& s );
// GET-SIZE
size_t getSizeItemBase( const ItemBase& s );
size_t getSizeItem( const Item& s );
size_t getSizeCharacter( const Character& s );
size_t getSize__unique_ptr_ItemBase( const unique_ptr<ItemBase>& s );

#endif // OUTPUT_H_INCLUDED

