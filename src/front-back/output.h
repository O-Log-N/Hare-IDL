
#ifndef OUTPUT_H_INCLUDED
#define OUTPUT_H_INCLUDED

#include <simple_lib.h>

// DECLARATIONS

// objects

struct Item;
struct Character;

struct Item {
   std::string 
   name; // 1
};

struct Character {
   uint16_t
   character_id; // 1
   double
   x; // 1
   double
   y; // 1
   double
   z; // 1
   double
   vx; // 1
   double
   vy; // 1
   double
   vz; // 1
   float
   angle; // 1
   anim; // 1
   uint8_t
   animation_frame; // 1
   inventory; // 1
};

  
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

#endif // OUTPUT_H_INCLUDED

