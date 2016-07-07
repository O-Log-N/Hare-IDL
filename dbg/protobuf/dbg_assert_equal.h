
#ifndef DBG_ASSERT_EQUAL_H_INCLUDED
#define DBG_ASSERT_EQUAL_H_INCLUDED

#include <cassert>
#include "output.h"
#include "output.pb.h"

// ASSERT-EQUAL
inline void assertEqualItemBase( const ItemBase& left, const ItemBase& right );
inline void assertEqualItem( const Item& left, const Item& right );
inline void assertEqualCharacter( const Character& left, const Character& right );
inline void assertEqual__unique_ptr_ItemBase( const unique_ptr<ItemBase>& left, const unique_ptr<ItemBase>& right );


inline void assertEqualItemBase( const ItemBase& left, const ItemBase& right ) {
    assert(left.id == right.id);
}

inline void assertEqualItem( const Item& left, const Item& right ) {
    assert(left.name == right.name);
    assert(left.valid == right.valid);
    assertEqualItemBase(left , right);
}

inline void assertEqualCharacter( const Character& left, const Character& right ) {
    assert(left.max_u8 == right.max_u8);
    assert(left.max_u16 == right.max_u16);
    assert(left.max_u32 == right.max_u32);
    assert(left.min_s8 == right.min_s8);
    assert(left.min_s16 == right.min_s16);
    assert(left.min_s32 == right.min_s32);
    assert(left.max_s8 == right.max_s8);
    assert(left.max_s16 == right.max_s16);
    assert(left.max_s32 == right.max_s32);
    assert(left.x == right.x);
    assert(left.y == right.y);
    assert(left.z == right.z);
    assert(left.flag == right.flag);
    assert(left.desc == right.desc);
    {
      auto it1 = left.more_text.begin();
      auto it1_end = left.more_text.end();
      auto it2 = right.more_text.begin();
      auto it2_end = right.more_text.end();
      for (; it1 != it1_end && it2 != it2_end; ++it1, ++it2)
      assert(*it1 == *it2);
      assert(it1 == it1_end);
      assert(it2 == it2_end);
    }
    {
      auto it1 = left.some_ints.begin();
      auto it1_end = left.some_ints.end();
      auto it2 = right.some_ints.begin();
      auto it2_end = right.some_ints.end();
      for (; it1 != it1_end && it2 != it2_end; ++it1, ++it2)
      assert(*it1 == *it2);
      assert(it1 == it1_end);
      assert(it2 == it2_end);
    }
    {
      auto it1 = left.inventory.begin();
      auto it1_end = left.inventory.end();
      auto it2 = right.inventory.begin();
      auto it2_end = right.inventory.end();
      for (; it1 != it1_end && it2 != it2_end; ++it1, ++it2)
      assertEqualItem(*it1, *it2);
      assert(it1 == it1_end);
      assert(it2 == it2_end);
    }
    assertEqual__unique_ptr_ItemBase(left.poly_ptr , right.poly_ptr);
}

inline void assertEqual__unique_ptr_ItemBase( const unique_ptr<ItemBase>& left, const unique_ptr<ItemBase>& right ) {

  if(left.get() == nullptr) {
    assert(right.get() == nullptr);
  }

       else if ( typeid( *left ) == typeid( Item ) ) {
         assert (typeid(*right) == typeid( Item ));
         auto l = dynamic_cast<Item*>(left.get());
         auto r = dynamic_cast<Item*>(right.get());

         assertEqualItem(*l , *r);
       }
       else if ( typeid( *left ) == typeid( ItemBase ) ) {
         assert (typeid(*right) == typeid( ItemBase ));
         auto l = dynamic_cast<ItemBase*>(left.get());
         auto r = dynamic_cast<ItemBase*>(right.get());

         assertEqualItemBase(*l , *r);
       }

   else {
     assert(false);
   }
}


// ASSERT-EQUAL2
inline void assertEqualItemBase( const ItemBase& left, const pb::ItemBase& right );
inline void assertEqualItem( const Item& left, const pb::Item& right );
inline void assertEqualCharacter( const Character& left, const pb::Character& right );
inline void assertEqual__unique_ptr_ItemBase( const unique_ptr<ItemBase>& left, const pb::__unique_ptr_ItemBase& right );


inline void assertEqualItemBase( const ItemBase& left, const pb::ItemBase& right ) {
    assert(left.id == right.id());
}

inline void assertEqualItem( const Item& left, const pb::Item& right ) {
    assert(left.name == right.name());
    assert(left.valid == right.valid());
    assertEqualItemBase(left , right.__parent());
}

inline void assertEqualCharacter( const Character& left, const pb::Character& right ) {
    assert(left.max_u8 == right.max_u8());
    assert(left.max_u16 == right.max_u16());
    assert(left.max_u32 == right.max_u32());
    assert(left.min_s8 == right.min_s8());
    assert(left.min_s16 == right.min_s16());
    assert(left.min_s32 == right.min_s32());
    assert(left.max_s8 == right.max_s8());
    assert(left.max_s16 == right.max_s16());
    assert(left.max_s32 == right.max_s32());
    assert(left.x == right.x());
    assert(left.y == right.y());
    assert(left.z == right.z());
    assert(left.flag == right.flag());
    assert(left.desc == right.desc());
    {
      auto it1 = left.more_text.begin();
      auto it1_end = left.more_text.end();
      auto it2 = right.more_text().begin();
      auto it2_end = right.more_text().end();
      for (; it1 != it1_end && it2 != it2_end; ++it1, ++it2)
      assert(*it1 == *it2);
      assert(it1 == it1_end);
      assert(it2 == it2_end);
    }
    {
      auto it1 = left.some_ints.begin();
      auto it1_end = left.some_ints.end();
      auto it2 = right.some_ints().begin();
      auto it2_end = right.some_ints().end();
      for (; it1 != it1_end && it2 != it2_end; ++it1, ++it2)
      assert(*it1 == *it2);
      assert(it1 == it1_end);
      assert(it2 == it2_end);
    }
    {
      auto it1 = left.inventory.begin();
      auto it1_end = left.inventory.end();
      auto it2 = right.inventory().begin();
      auto it2_end = right.inventory().end();
      for (; it1 != it1_end && it2 != it2_end; ++it1, ++it2)
      assertEqualItem(*it1, *it2);
      assert(it1 == it1_end);
      assert(it2 == it2_end);
    }
    assertEqual__unique_ptr_ItemBase(left.poly_ptr , right.poly_ptr());
}

inline void assertEqual__unique_ptr_ItemBase( const unique_ptr<ItemBase>& left, const pb::__unique_ptr_ItemBase& right ) {


  size_t du = 0;
  if(left.get() == nullptr) {
    ; // nothing
  }

       else if ( typeid( *left ) == typeid( Item ) ) {
         auto l = dynamic_cast<Item*>(left.get());

         assertEqualItem(*l , right.du_1());
         du = 1;
       }
       else if ( typeid( *left ) == typeid( ItemBase ) ) {
         auto l = dynamic_cast<ItemBase*>(left.get());

         assertEqualItemBase(*l , right.du_2());
         du = 2;
       }

   else {
     assert(false);
   }

       if(du != 1) assert(!right.has_du_1());
       if(du != 2) assert(!right.has_du_2());

}


#endif // DBG_ASSERT_EQUAL_H_INCLUDED
  
