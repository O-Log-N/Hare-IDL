
#ifndef DBG_ASSERT_EQUAL_H_INCLUDED
#define DBG_ASSERT_EQUAL_H_INCLUDED

#include <cassert>
#include "output.h"
#include "output.pb.h"

// ASSERT-EQUAL
inline void assertEqualLimit( const Limit& left, const Limit& right );
inline void assertEqualLocation( const Location& left, const Location& right );
inline void assertEqualCharacterRange( const CharacterRange& left, const CharacterRange& right );
inline void assertEqualCharacterSet( const CharacterSet& left, const CharacterSet& right );
inline void assertEqualVariant( const Variant& left, const Variant& right );
inline void assertEqualDataType( const DataType& left, const DataType& right );
inline void assertEqualEncodingSpecifics( const EncodingSpecifics& left, const EncodingSpecifics& right );
inline void assertEqualEncodedOrMember( const EncodedOrMember& left, const EncodedOrMember& right );
inline void assertEqualDataMember( const DataMember& left, const DataMember& right );
inline void assertEqualEncodedMembers( const EncodedMembers& left, const EncodedMembers& right );
inline void assertEqualStructure( const Structure& left, const Structure& right );
inline void assertEqualTypedef( const Typedef& left, const Typedef& right );
inline void assertEqualRoot( const Root& left, const Root& right );
inline void assertEqual__unique_ptr_DataType( const unique_ptr<DataType>& left, const unique_ptr<DataType>& right );
inline void assertEqual__unique_ptr_EncodedOrMember( const unique_ptr<EncodedOrMember>& left, const unique_ptr<EncodedOrMember>& right );
inline void assertEqual__unique_ptr_Structure( const unique_ptr<Structure>& left, const unique_ptr<Structure>& right );


inline void assertEqualLimit( const Limit& left, const Limit& right ) {
    assert(left.inclusive == right.inclusive);
    assert(left.value == right.value);
}

inline void assertEqualLocation( const Location& left, const Location& right ) {
    assert(left.fileName == right.fileName);
    assert(left.lineNumber == right.lineNumber);
}

inline void assertEqualCharacterRange( const CharacterRange& left, const CharacterRange& right ) {
    assert(left.from == right.from);
    assert(left.to == right.to);
}

inline void assertEqualCharacterSet( const CharacterSet& left, const CharacterSet& right ) {
    {
      auto it1 = left.ranges.begin();
      auto it1_end = left.ranges.end();
      auto it2 = right.ranges.begin();
      auto it2_end = right.ranges.end();
      for (; it1 != it1_end && it2 != it2_end; ++it1, ++it2) {
      assertEqualCharacterRange(*it1, *it2);
      }
      assert(it1 == it1_end);
      assert(it2 == it2_end);
    }
}

inline void assertEqualVariant( const Variant& left, const Variant& right ) {
    assert(left.kind == right.kind);
    assert(left.numberValue == right.numberValue);
    assert(left.stringValue == right.stringValue);
}

inline void assertEqualDataType( const DataType& left, const DataType& right ) {
    assert(left.kind == right.kind);
    assert(left.name == right.name);
    assert(left.mappingName == right.mappingName);
    assert(left.encodingName == right.encodingName);
    assertEqual__unique_ptr_DataType(left.keyType , right.keyType);
    assertEqual__unique_ptr_DataType(left.paramType , right.paramType);
    assertEqualLimit(left.lowLimit , right.lowLimit);
    assertEqualLimit(left.highLimit , right.highLimit);
    assert(left.fixedPrecision == right.fixedPrecision);
    assert(left.floatingSignificandBits == right.floatingSignificandBits);
    assert(left.floatingExponentBits == right.floatingExponentBits);
    assertEqualCharacterSet(left.characterSet , right.characterSet);
    assert(left.stringMinSize == right.stringMinSize);
    assert(left.stringMaxSize == right.stringMaxSize);
    {
      auto it1 = left.encodingAttrs.begin();
      auto it1_end = left.encodingAttrs.end();
      auto it2 = right.encodingAttrs.begin();
      auto it2_end = right.encodingAttrs.end();
      for (; it1 != it1_end && it2 != it2_end; ++it1, ++it2) {
      assert(it1->first == it2->first);
      assertEqualVariant(it1->second, it2->second);
      }
      assert(it1 == it1_end);
      assert(it2 == it2_end);
    }
    {
      auto it1 = left.mappingAttrs.begin();
      auto it1_end = left.mappingAttrs.end();
      auto it2 = right.mappingAttrs.begin();
      auto it2_end = right.mappingAttrs.end();
      for (; it1 != it1_end && it2 != it2_end; ++it1, ++it2) {
      assert(it1->first == it2->first);
      assertEqualVariant(it1->second, it2->second);
      }
      assert(it1 == it1_end);
      assert(it2 == it2_end);
    }
    {
      auto it1 = left.enumValues.begin();
      auto it1_end = left.enumValues.end();
      auto it2 = right.enumValues.begin();
      auto it2_end = right.enumValues.end();
      for (; it1 != it1_end && it2 != it2_end; ++it1, ++it2) {
      assert(it1->first == it2->first);
      assert(it1->second == it2->second);
      }
      assert(it1 == it1_end);
      assert(it2 == it2_end);
    }
}

inline void assertEqualEncodingSpecifics( const EncodingSpecifics& left, const EncodingSpecifics& right ) {
    assert(left.name == right.name);
    {
      auto it1 = left.attrs.begin();
      auto it1_end = left.attrs.end();
      auto it2 = right.attrs.begin();
      auto it2_end = right.attrs.end();
      for (; it1 != it1_end && it2 != it2_end; ++it1, ++it2) {
      assert(it1->first == it2->first);
      assertEqualVariant(it1->second, it2->second);
      }
      assert(it1 == it1_end);
      assert(it2 == it2_end);
    }
}

inline void assertEqualEncodedOrMember( const EncodedOrMember& left, const EncodedOrMember& right ) {
    assertEqualLocation(left.location , right.location);
}

inline void assertEqualDataMember( const DataMember& left, const DataMember& right ) {
    assertEqualDataType(left.type , right.type);
    assert(left.name == right.name);
    assert(left.extendTo == right.extendTo);
    assertEqualVariant(left.defaultValue , right.defaultValue);
    {
      auto it1 = left.whenDiscriminant.begin();
      auto it1_end = left.whenDiscriminant.end();
      auto it2 = right.whenDiscriminant.begin();
      auto it2_end = right.whenDiscriminant.end();
      for (; it1 != it1_end && it2 != it2_end; ++it1, ++it2) {
      assert(*it1 == *it2);
      }
      assert(it1 == it1_end);
      assert(it2 == it2_end);
    }
    assertEqualEncodedOrMember(left , right);
}

inline void assertEqualEncodedMembers( const EncodedMembers& left, const EncodedMembers& right ) {
    assertEqualEncodingSpecifics(left.encodingSpecifics , right.encodingSpecifics);
    {
      auto it1 = left.members.begin();
      auto it1_end = left.members.end();
      auto it2 = right.members.begin();
      auto it2_end = right.members.end();
      for (; it1 != it1_end && it2 != it2_end; ++it1, ++it2) {
      assertEqual__unique_ptr_EncodedOrMember(*it1, *it2);
      }
      assert(it1 == it1_end);
      assert(it2 == it2_end);
    }
    assertEqualEncodedOrMember(left , right);
}

inline void assertEqualStructure( const Structure& left, const Structure& right ) {
    assert(left.declType == right.declType);
    assert(left.type == right.type);
    assert(left.name == right.name);
    assert(left.discriminant == right.discriminant);
    assert(left.inheritedFrom == right.inheritedFrom);
    assertEqualEncodedMembers(left , right);
}

inline void assertEqualTypedef( const Typedef& left, const Typedef& right ) {
    assertEqualLocation(left.location , right.location);
    assertEqualDataType(left.type , right.type);
    assert(left.name == right.name);
}

inline void assertEqualRoot( const Root& left, const Root& right ) {
    {
      auto it1 = left.typedefs.begin();
      auto it1_end = left.typedefs.end();
      auto it2 = right.typedefs.begin();
      auto it2_end = right.typedefs.end();
      for (; it1 != it1_end && it2 != it2_end; ++it1, ++it2) {
      assertEqualTypedef(*it1, *it2);
      }
      assert(it1 == it1_end);
      assert(it2 == it2_end);
    }
    {
      auto it1 = left.structures.begin();
      auto it1_end = left.structures.end();
      auto it2 = right.structures.begin();
      auto it2_end = right.structures.end();
      for (; it1 != it1_end && it2 != it2_end; ++it1, ++it2) {
      assertEqual__unique_ptr_Structure(*it1, *it2);
      }
      assert(it1 == it1_end);
      assert(it2 == it2_end);
    }
}

inline void assertEqual__unique_ptr_DataType( const unique_ptr<DataType>& left, const unique_ptr<DataType>& right ) {

  if(left.get() == nullptr) {
    assert(right.get() == nullptr);
  }

       else if ( typeid( *left ) == typeid( DataType ) ) {
         assert (typeid(*right) == typeid( DataType ));
         auto l = dynamic_cast<DataType*>(left.get());
         auto r = dynamic_cast<DataType*>(right.get());

         assertEqualDataType(*l , *r);
       }

   else {
     assert(false);
   }
}
inline void assertEqual__unique_ptr_EncodedOrMember( const unique_ptr<EncodedOrMember>& left, const unique_ptr<EncodedOrMember>& right ) {

  if(left.get() == nullptr) {
    assert(right.get() == nullptr);
  }

       else if ( typeid( *left ) == typeid( DataMember ) ) {
         assert (typeid(*right) == typeid( DataMember ));
         auto l = dynamic_cast<DataMember*>(left.get());
         auto r = dynamic_cast<DataMember*>(right.get());

         assertEqualDataMember(*l , *r);
       }
       else if ( typeid( *left ) == typeid( EncodedMembers ) ) {
         assert (typeid(*right) == typeid( EncodedMembers ));
         auto l = dynamic_cast<EncodedMembers*>(left.get());
         auto r = dynamic_cast<EncodedMembers*>(right.get());

         assertEqualEncodedMembers(*l , *r);
       }
       else if ( typeid( *left ) == typeid( EncodedOrMember ) ) {
         assert (typeid(*right) == typeid( EncodedOrMember ));
         auto l = dynamic_cast<EncodedOrMember*>(left.get());
         auto r = dynamic_cast<EncodedOrMember*>(right.get());

         assertEqualEncodedOrMember(*l , *r);
       }

   else {
     assert(false);
   }
}
inline void assertEqual__unique_ptr_Structure( const unique_ptr<Structure>& left, const unique_ptr<Structure>& right ) {

  if(left.get() == nullptr) {
    assert(right.get() == nullptr);
  }

       else if ( typeid( *left ) == typeid( Structure ) ) {
         assert (typeid(*right) == typeid( Structure ));
         auto l = dynamic_cast<Structure*>(left.get());
         auto r = dynamic_cast<Structure*>(right.get());

         assertEqualStructure(*l , *r);
       }

   else {
     assert(false);
   }
}


// ASSERT-EQUAL-2-GPB
inline void assertEqualLimit( const Limit& left, const pb::Limit& right );
inline void assertEqualLocation( const Location& left, const pb::Location& right );
inline void assertEqualCharacterRange( const CharacterRange& left, const pb::CharacterRange& right );
inline void assertEqualCharacterSet( const CharacterSet& left, const pb::CharacterSet& right );
inline void assertEqualVariant( const Variant& left, const pb::Variant& right );
inline void assertEqualDataType( const DataType& left, const pb::DataType& right );
inline void assertEqualEncodingSpecifics( const EncodingSpecifics& left, const pb::EncodingSpecifics& right );
inline void assertEqualEncodedOrMember( const EncodedOrMember& left, const pb::EncodedOrMember& right );
inline void assertEqualDataMember( const DataMember& left, const pb::DataMember& right );
inline void assertEqualEncodedMembers( const EncodedMembers& left, const pb::EncodedMembers& right );
inline void assertEqualStructure( const Structure& left, const pb::Structure& right );
inline void assertEqualTypedef( const Typedef& left, const pb::Typedef& right );
inline void assertEqualRoot( const Root& left, const pb::Root& right );
inline void assertEqual__unique_ptr_DataType( const unique_ptr<DataType>& left, const pb::__unique_ptr_DataType& right );
inline void assertEqual__unique_ptr_EncodedOrMember( const unique_ptr<EncodedOrMember>& left, const pb::__unique_ptr_EncodedOrMember& right );
inline void assertEqual__unique_ptr_Structure( const unique_ptr<Structure>& left, const pb::__unique_ptr_Structure& right );


inline void assertEqualLimit( const Limit& left, const pb::Limit& right ) {
    assert(left.inclusive == right.inclusive());
    assert(left.value == right.value());
}

inline void assertEqualLocation( const Location& left, const pb::Location& right ) {
    assert(left.fileName == right.file_name());
    assert(left.lineNumber == right.line_number());
}

inline void assertEqualCharacterRange( const CharacterRange& left, const pb::CharacterRange& right ) {
    assert(left.from == right.from());
    assert(left.to == right.to());
}

inline void assertEqualCharacterSet( const CharacterSet& left, const pb::CharacterSet& right ) {
    {
      auto it1 = left.ranges.begin();
      auto it1_end = left.ranges.end();
      auto it2 = right.ranges().begin();
      auto it2_end = right.ranges().end();
      for (; it1 != it1_end && it2 != it2_end; ++it1, ++it2) {
      assertEqualCharacterRange(*it1, *it2);
      }
      assert(it1 == it1_end);
      assert(it2 == it2_end);
    }
}

inline void assertEqualVariant( const Variant& left, const pb::Variant& right ) {
       // can't compare enum kind
    assert(left.numberValue == right.number_value());
    assert(left.stringValue == right.string_value());
}

inline void assertEqualDataType( const DataType& left, const pb::DataType& right ) {
       // can't compare enum kind
    assert(left.name == right.name());
    assert(left.mappingName == right.mapping_name());
    assert(left.encodingName == right.encoding_name());
    assertEqual__unique_ptr_DataType(left.keyType , right.key_type());
    assertEqual__unique_ptr_DataType(left.paramType , right.param_type());
    assertEqualLimit(left.lowLimit , right.low_limit());
    assertEqualLimit(left.highLimit , right.high_limit());
    assert(left.fixedPrecision == right.fixed_precision());
    assert(left.floatingSignificandBits == right.floating_significand_bits());
    assert(left.floatingExponentBits == right.floating_exponent_bits());
    assertEqualCharacterSet(left.characterSet , right.character_set());
    assert(left.stringMinSize == right.string_min_size());
    assert(left.stringMaxSize == right.string_max_size());
       // can't compare dictionary encodingAttrs
       // can't compare dictionary mappingAttrs
       // can't compare dictionary enumValues
}

inline void assertEqualEncodingSpecifics( const EncodingSpecifics& left, const pb::EncodingSpecifics& right ) {
    assert(left.name == right.name());
       // can't compare dictionary attrs
}

inline void assertEqualEncodedOrMember( const EncodedOrMember& left, const pb::EncodedOrMember& right ) {
    assertEqualLocation(left.location , right.location());
}

inline void assertEqualDataMember( const DataMember& left, const pb::DataMember& right ) {
    assertEqualDataType(left.type , right.type());
    assert(left.name == right.name());
    assert(left.extendTo == right.extend_to());
    assertEqualVariant(left.defaultValue , right.default_value());
    {
      auto it1 = left.whenDiscriminant.begin();
      auto it1_end = left.whenDiscriminant.end();
      auto it2 = right.when_discriminant().begin();
      auto it2_end = right.when_discriminant().end();
      for (; it1 != it1_end && it2 != it2_end; ++it1, ++it2) {
      assert(*it1 == *it2);
      }
      assert(it1 == it1_end);
      assert(it2 == it2_end);
    }
    assertEqualEncodedOrMember(left , right.__parent());
}

inline void assertEqualEncodedMembers( const EncodedMembers& left, const pb::EncodedMembers& right ) {
    assertEqualEncodingSpecifics(left.encodingSpecifics , right.encoding_specifics());
    {
      auto it1 = left.members.begin();
      auto it1_end = left.members.end();
      auto it2 = right.members().begin();
      auto it2_end = right.members().end();
      for (; it1 != it1_end && it2 != it2_end; ++it1, ++it2) {
      assertEqual__unique_ptr_EncodedOrMember(*it1, *it2);
      }
      assert(it1 == it1_end);
      assert(it2 == it2_end);
    }
    assertEqualEncodedOrMember(left , right.__parent());
}

inline void assertEqualStructure( const Structure& left, const pb::Structure& right ) {
       // can't compare enum declType
       // can't compare enum type
    assert(left.name == right.name());
    assert(left.discriminant == right.discriminant());
    assert(left.inheritedFrom == right.inherited_from());
    assertEqualEncodedMembers(left , right.__parent());
}

inline void assertEqualTypedef( const Typedef& left, const pb::Typedef& right ) {
    assertEqualLocation(left.location , right.location());
    assertEqualDataType(left.type , right.type());
    assert(left.name == right.name());
}

inline void assertEqualRoot( const Root& left, const pb::Root& right ) {
    {
      auto it1 = left.typedefs.begin();
      auto it1_end = left.typedefs.end();
      auto it2 = right.typedefs().begin();
      auto it2_end = right.typedefs().end();
      for (; it1 != it1_end && it2 != it2_end; ++it1, ++it2) {
      assertEqualTypedef(*it1, *it2);
      }
      assert(it1 == it1_end);
      assert(it2 == it2_end);
    }
    {
      auto it1 = left.structures.begin();
      auto it1_end = left.structures.end();
      auto it2 = right.structures().begin();
      auto it2_end = right.structures().end();
      for (; it1 != it1_end && it2 != it2_end; ++it1, ++it2) {
      assertEqual__unique_ptr_Structure(*it1, *it2);
      }
      assert(it1 == it1_end);
      assert(it2 == it2_end);
    }
}

inline void assertEqual__unique_ptr_DataType( const unique_ptr<DataType>& left, const pb::__unique_ptr_DataType& right ) {


  size_t du = 0;
  if(left.get() == nullptr) {
    ; // nothing
  }

       else if ( typeid( *left ) == typeid( DataType ) ) {
         auto l = dynamic_cast<DataType*>(left.get());

         assertEqualDataType(*l , right.du_1());
         du = 1;
       }

   else {
     assert(false);
   }

       if(du != 1) assert(!right.has_du_1());

}
inline void assertEqual__unique_ptr_EncodedOrMember( const unique_ptr<EncodedOrMember>& left, const pb::__unique_ptr_EncodedOrMember& right ) {


  size_t du = 0;
  if(left.get() == nullptr) {
    ; // nothing
  }

       else if ( typeid( *left ) == typeid( DataMember ) ) {
         auto l = dynamic_cast<DataMember*>(left.get());

         assertEqualDataMember(*l , right.du_1());
         du = 1;
       }
       else if ( typeid( *left ) == typeid( EncodedMembers ) ) {
         auto l = dynamic_cast<EncodedMembers*>(left.get());

         assertEqualEncodedMembers(*l , right.du_2());
         du = 2;
       }
       else if ( typeid( *left ) == typeid( EncodedOrMember ) ) {
         auto l = dynamic_cast<EncodedOrMember*>(left.get());

         assertEqualEncodedOrMember(*l , right.du_3());
         du = 3;
       }

   else {
     assert(false);
   }

       if(du != 1) assert(!right.has_du_1());
       if(du != 2) assert(!right.has_du_2());
       if(du != 3) assert(!right.has_du_3());

}
inline void assertEqual__unique_ptr_Structure( const unique_ptr<Structure>& left, const pb::__unique_ptr_Structure& right ) {


  size_t du = 0;
  if(left.get() == nullptr) {
    ; // nothing
  }

       else if ( typeid( *left ) == typeid( Structure ) ) {
         auto l = dynamic_cast<Structure*>(left.get());

         assertEqualStructure(*l , right.du_1());
         du = 1;
       }

   else {
     assert(false);
   }

       if(du != 1) assert(!right.has_du_1());

}


#endif // DBG_ASSERT_EQUAL_H_INCLUDED
  
