
#ifndef DBG_ASSERT_EQUAL_H_INCLUDED
#define DBG_ASSERT_EQUAL_H_INCLUDED

#include <cassert>
#include "output.h"
#include "output.pb.h"

// ASSERT-EQUAL
inline void assertEqualRoot( const Root& left, const Root& right );


inline void assertEqualRoot( const Root& left, const Root& right ) {
    {
      auto it1 = left.packedVarInts.begin();
      auto it1_end = left.packedVarInts.end();
      auto it2 = right.packedVarInts.begin();
      auto it2_end = right.packedVarInts.end();
      for (; it1 != it1_end && it2 != it2_end; ++it1, ++it2) {
      assert(*it1 == *it2);
      }
      assert(it1 == it1_end);
      assert(it2 == it2_end);
    }
    {
      auto it1 = left.packedDoubles.begin();
      auto it1_end = left.packedDoubles.end();
      auto it2 = right.packedDoubles.begin();
      auto it2_end = right.packedDoubles.end();
      for (; it1 != it1_end && it2 != it2_end; ++it1, ++it2) {
      assert(*it1 == *it2);
      }
      assert(it1 == it1_end);
      assert(it2 == it2_end);
    }
    {
      auto it1 = left.unpackedStrings.begin();
      auto it1_end = left.unpackedStrings.end();
      auto it2 = right.unpackedStrings.begin();
      auto it2_end = right.unpackedStrings.end();
      for (; it1 != it1_end && it2 != it2_end; ++it1, ++it2) {
      assert(*it1 == *it2);
      }
      assert(it1 == it1_end);
      assert(it2 == it2_end);
    }
}


// ASSERT-EQUAL-2-GPB
inline void assertEqualRoot( const Root& left, const pb::Root& right );

inline void assertEqualRoot( const Root& left, const pb::Root& right ) {
    {
      auto it1 = left.packedVarInts.begin();
      auto it1_end = left.packedVarInts.end();
      auto it2 = right.packed_var_ints().begin();
      auto it2_end = right.packed_var_ints().end();
      for (; it1 != it1_end && it2 != it2_end; ++it1, ++it2) {
      assert(*it1 == *it2);
      }
      assert(it1 == it1_end);
      assert(it2 == it2_end);
    }
    {
      auto it1 = left.packedDoubles.begin();
      auto it1_end = left.packedDoubles.end();
      auto it2 = right.packed_doubles().begin();
      auto it2_end = right.packed_doubles().end();
      for (; it1 != it1_end && it2 != it2_end; ++it1, ++it2) {
      assert(*it1 == *it2);
      }
      assert(it1 == it1_end);
      assert(it2 == it2_end);
    }
    {
      auto it1 = left.unpackedStrings.begin();
      auto it1_end = left.unpackedStrings.end();
      auto it2 = right.unpacked_strings().begin();
      auto it2_end = right.unpacked_strings().end();
      for (; it1 != it1_end && it2 != it2_end; ++it1, ++it2) {
      assert(*it1 == *it2);
      }
      assert(it1 == it1_end);
      assert(it2 == it2_end);
    }
}

#endif // DBG_ASSERT_EQUAL_H_INCLUDED
  
