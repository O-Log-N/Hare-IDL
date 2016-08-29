
#ifndef DBG_HELPERS_H_INCLUDED
#define DBG_HELPERS_H_INCLUDED

#include <cassert>
#include <ostream>

#include "output.h"
#include "output.pb.h"

#ifndef EXPECT_TRUE
#define EXPECT_TRUE assert
#endif

#ifndef EXPECT_EQ
#define EXPECT_EQ(left, right) assert(left == right)
#endif

void dbgPrintDiscriminatedUnion( const DiscriminatedUnion& s, std::ostream& o, size_t offset );

inline void assertEqualDiscriminatedUnion( const DiscriminatedUnion& left, const DiscriminatedUnion& right );


inline void assertEqualDiscriminatedUnion( const DiscriminatedUnion& left, const pb::DiscriminatedUnion& right );

// PRINT

void dbgPrintDiscriminatedUnion( const DiscriminatedUnion& s, std::ostream& o, size_t offset ) {

  std::string sp( 2 * offset, ' ' );
  std::string sp1( 2 * offset + 2, ' ');

 o << "DISCRIMINATED-UNION DiscriminatedUnion:\n";

   //uint8_t disc = (s.disc);

  uint8_t disc = s.disc;
  
  o << sp << "disc = " << disc << "\n";

  switch ( disc )
  {
    case 0:
    {
    o << sp << "name = ";
  o << "\"" << s.name << "\"\n";
    o << sp << "value1 = ";
  o << s.value1 << "\n";
    }
    break;
    case 1:
    {
    o << sp << "name = ";
  o << "\"" << s.name << "\"\n";
    o << sp << "value1 = ";
  o << s.value1 << "\n";
    }
    break;
    case 2:
    {
    o << sp << "name = ";
  o << "\"" << s.name << "\"\n";
    o << sp << "value2 = ";
  o << s.value2 << "\n";
    }
    break;
    case 3:
    {
    o << sp << "name = ";
  o << "\"" << s.name << "\"\n";
    o << sp << "value3 = ";
  o << s.value3 << "\n";
    }
    break;
    default:
      assert( false );
  }
}

// ASSERT-EQUAL

// ASSERT-EQUAL-2-GPB
inline void assertEqualDiscriminatedUnion( const DiscriminatedUnion& left, const pb::DiscriminatedUnion& right ) {

  uint8_t disc = (left.disc);
  EXPECT_TRUE(disc == right.discriminator());

  switch(disc)
  {
    case 0:
    {
    EXPECT_EQ(left.name, right.name());
    EXPECT_EQ(left.value1, right.value1());
    }
    break;
    case 1:
    {
    EXPECT_EQ(left.name, right.name());
    EXPECT_EQ(left.value1, right.value1());
    }
    break;
    case 2:
    {
    EXPECT_EQ(left.name, right.name());
    EXPECT_EQ(left.value2, right.value2());
    }
    break;
    case 3:
    {
    EXPECT_EQ(left.name, right.name());
    EXPECT_EQ(left.value3, right.value3());
    }
    break;
    default:
      EXPECT_TRUE(false);
  }
}

#endif // DBG_HELPERS_H_INCLUDED
  
