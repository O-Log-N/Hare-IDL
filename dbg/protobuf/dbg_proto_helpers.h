
#ifndef DBG_PROTO_HELPERS_H_INCLUDED
#define DBG_PROTO_HELPERS_H_INCLUDED

#include <cassert>

#include "output.h"
#include "output.pb.h"

#ifndef EXPECT_TRUE
#define EXPECT_TRUE assert
#endif

#ifndef EXPECT_EQ
#define EXPECT_EQ(left, right) assert(left == right)
#endif

inline void assertEqualBasicTypes( const BasicTypes& left, const pb::BasicTypes& right );

// ASSERT-EQUAL-2-GPB
inline void assertEqualBasicTypes( const BasicTypes& left, const pb::BasicTypes& right ) {
    EXPECT_EQ(left.max_u32, right.max_u32());
    EXPECT_EQ(left.max_u64, right.max_u64());
    EXPECT_EQ(left.max_s32, right.max_s32());
    EXPECT_EQ(left.max_s64, right.max_s64());
    EXPECT_EQ(left.aFloat, right.a_float());
    EXPECT_EQ(left.aDouble, right.a_double());
    EXPECT_EQ(left.description, right.description());
        switch(left.aValue)
        {
          case /* First */ 1: EXPECT_TRUE(right.a_value() == 0); break;
          case /* Nothing */ 0: EXPECT_TRUE(right.a_value() == 1); break;
          case /* Second */ 2: EXPECT_TRUE(right.a_value() == 2); break;
          default: EXPECT_TRUE(false);
        }
    EXPECT_EQ(left.flag, right.flag());
}

#endif // DBG_PROTO_HELPERS_H_INCLUDED
  
