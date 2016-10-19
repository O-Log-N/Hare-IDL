
#ifndef DBG_HELPERS_H_INCLUDED
#define DBG_HELPERS_H_INCLUDED

#include <cassert>
#include <ostream>

#include "output.h"

#ifndef EXPECT_TRUE
#define EXPECT_TRUE assert
#endif

#ifndef EXPECT_EQ
#define EXPECT_EQ(left, right) assert(left == right)
#endif

void dbgPrintBasicTypes( const BasicTypes& s, std::ostream& o, size_t offset );

inline void assertEqualBasicTypes( const BasicTypes& left, const BasicTypes& right );


// PRINT
void dbgPrintBasicTypes( const BasicTypes& s, std::ostream& o, size_t offset ) {

  std::string sp( 2 * offset, ' ' );
  std::string sp1( 2 * offset + 2, ' ');

  o << "PUBLISHABLE-STRUCT BasicTypes:\n";

    o << sp << "max_u32 = ";
  o << s.max_u32 << "\n";
    o << sp << "max_u64 = ";
  o << s.max_u64 << "\n";
    o << sp << "max_s32 = ";
  o << s.max_s32 << "\n";
    o << sp << "max_s64 = ";
  o << s.max_s64 << "\n";
    o << sp << "aFloat = ";
  o << s.aFloat << "\n";
    o << sp << "aDouble = ";
  o << s.aDouble << "\n";
    o << sp << "description = ";
  o << "\"" << s.description << "\"\n";
    o << sp << "aValue = ";
  o << s.aValue << "\n";
    o << sp << "flag = ";
  o << s.flag << "\n";
}


// ASSERT-EQUAL
inline void assertEqualBasicTypes( const BasicTypes& left, const BasicTypes& right ) {
    EXPECT_EQ(left.max_u32, right.max_u32);
    EXPECT_EQ(left.max_u64, right.max_u64);
    EXPECT_EQ(left.max_s32, right.max_s32);
    EXPECT_EQ(left.max_s64, right.max_s64);
    EXPECT_EQ(left.aFloat, right.aFloat);
    EXPECT_EQ(left.aDouble, right.aDouble);
    EXPECT_EQ(left.description, right.description);
    EXPECT_EQ(left.aValue, right.aValue);
    EXPECT_EQ(left.flag, right.flag);
}


#endif // DBG_HELPERS_H_INCLUDED
  
