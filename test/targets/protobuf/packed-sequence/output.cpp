
#include "output.h"
#include "protobuf/baselib.h"

#include "test.h"

// IMPLEMENTATIONS

// SERIALIZATION

void serializeTestClass( const TestClass& s, OProtobufStream& o ) {
    for(const auto& item:s.unpackedStrings) {
    o.writeString(1, item);
    }
    if(!s.packedVarInts.empty()) {
      size_t sz_2 = 0;
    for(const auto& item:s.packedVarInts) {
          sz_2 += getSignedVarIntSize(item);
    }
      o.writeObjectTagAndSize(2, sz_2);
      for(const auto& item:s.packedVarInts) {
    o.writePackedSignedVarInt(item);
      }
    }
    if(!s.packedDoubles.empty()) {
      size_t sz_3 = 0;
    for(const auto& item:s.packedDoubles) {
        sz_3 += getFixedSize(item);
    }
      o.writeObjectTagAndSize(3, sz_3);
      for(const auto& item:s.packedDoubles) {
    o.writePackedDouble(item);
      }
    }
    if(!s.packedEnum.empty()) {
      size_t sz_4 = 0;
    for(const auto& item:s.packedEnum) {
        sz_4 += getUnsignedVarIntSize(item);
    }
      o.writeObjectTagAndSize(4, sz_4);
      for(const auto& item:s.packedEnum) {
        switch ( item )
        {
          case /* First */ 1: o.writePackedUnsignedVarInt(0 ); break;
          case /* Nothing */ 0: o.writePackedUnsignedVarInt(1 ); break;
          case /* Second */ 2: o.writePackedUnsignedVarInt(2 ); break;
            default: assert( false );
        }
      }
    }
}

  
// DESERIALIZATION

inline
bool discardUnexpectedField( int fieldType, IProtobufStream& i ) {

  // Unexpected field, just read and discard
  switch(fieldType)
  {
  case VARINT:
    {
      uint64_t temp;
      return i.readVariantUInt64( temp );
    }
    break;
  case FIXED_64_BIT:
    {
      double temp;
      return i.readFixed64Bit( temp );
    }
    break;
  case LENGTH_DELIMITED:
    {
      uint64_t sz;
      i.readVariantUInt64( sz );
      IProtobufStream is = i.makeSubStream( sz );
      string temp;
      return is.readString( temp );
    }
    break;
  case FIXED_32_BIT:
    {
      float temp;
//          readOk = i.readFixed32Bit( temp );
      return false;
    }
    break;
  default:
    return false;
  }
}

bool deserializeTestClass( TestClass& s, IProtobufStream& i ) {
   const int memcnt = 4;
   bool initFlags[memcnt] = { false };
  initFlags[0] = true;
  initFlags[1] = true;
  initFlags[2] = true;
  initFlags[3] = true;

  while(!i.isEndOfStream())
  {
    int fieldType;
    int fieldNumber;

    bool readOk = i.readFieldTypeAndID( fieldType, fieldNumber );
	  if ( !readOk )
		  return false;
	  switch ( fieldNumber )
	  {
    case 1:
    {
    string temp2;
      if( fieldType != LENGTH_DELIMITED ) return false;
      readOk = i.readString( temp2 );
    s.unpackedStrings.push_back( std::move( temp2 ) );
    }
    initFlags[0] = true;
    break;
    case 2:
    {
    if( fieldType == LENGTH_DELIMITED ) {
      uint64_t sz = 0;
      i.readVariantUInt64(sz);
      IProtobufStream is = i.makeSubStream(sz);
      IProtobufStream& i = is;

      while(!i.isEndOfStream()) {

      int64_t temp = 0;
      readOk = i.readVariantInt64( temp );
      s.packedVarInts.push_back( temp );
      
      if ( !readOk )
        return false;
      }
    } 
    else
    // fall back to non packed
    {
      if( fieldType != VARINT ) return false;
      int64_t temp = 0;
      readOk = i.readVariantInt64( temp );
      s.packedVarInts.push_back( temp );
    }
    }
    initFlags[1] = true;
    break;
    case 3:
    {
    if( fieldType == LENGTH_DELIMITED ) {
      uint64_t sz = 0;
      i.readVariantUInt64(sz);
      IProtobufStream is = i.makeSubStream(sz);
      IProtobufStream& i = is;

      while(!i.isEndOfStream()) {

      double temp = 0;
      readOk = i.readFixed64Bit( temp );
      s.packedDoubles.push_back( temp );
      
      if ( !readOk )
        return false;
      }
    } 
    else
    // fall back to non packed
    {
      if( fieldType != FIXED_64_BIT ) return false;
      double temp = 0;
      readOk = i.readFixed64Bit( temp );
      s.packedDoubles.push_back( temp );
    }
    }
    initFlags[2] = true;
    break;
    case 4:
    {
    if( fieldType == LENGTH_DELIMITED ) {
      uint64_t sz = 0;
      i.readVariantUInt64(sz);
      IProtobufStream is = i.makeSubStream(sz);
      IProtobufStream& i = is;

      while(!i.isEndOfStream()) {

      uint64_t temp = 0;
      readOk = i.readVariantUInt64( temp );
      switch ( temp )
      {
        case 0: s.packedEnum.push_back( s.First ); break;
        case 1: s.packedEnum.push_back( s.Nothing ); break;
        case 2: s.packedEnum.push_back( s.Second ); break;
        default: return false;
      }
      
      if ( !readOk )
        return false;
      }
    } 
    else
    // fall back to non packed
    {
      if( fieldType != VARINT ) return false;
      uint64_t temp = 0;
      readOk = i.readVariantUInt64( temp );
      switch ( temp )
      {
        case 0: s.packedEnum.push_back( s.First ); break;
        case 1: s.packedEnum.push_back( s.Nothing ); break;
        case 2: s.packedEnum.push_back( s.Second ); break;
        default: return false;
      }
    }
    }
    initFlags[3] = true;
    break;
		default:
      readOk = discardUnexpectedField( fieldType, i );
	  }
    if( !readOk )
      return false;
  }

  bool OK = true;
  for ( int i=0; i<memcnt; i++ )
    OK = OK && initFlags[i] != 0;

  return OK;
}


  
  
// PRINTING
//  INCLUDE TEMPLATE="PRINTING-GENERATE-IMPLEMENTATIONS" PARAM-ROOT=PARAM-ROOT

// GET-SIZE
size_t protobufGetSizeTestClass( const TestClass& s ) {
  size_t sz = 0;
      
    for(const auto& item:s.unpackedStrings) {
  sz += getTagSize(1);
  sz += getUnsignedVarIntSize(item.size());
  sz += item.size();
      }

      
    sz += getTagSize(2);
    size_t sz_2 = 0;
    for(const auto& item:s.packedVarInts) {
          sz_2 += getSignedVarIntSize(item);
    }
    sz += getUnsignedVarIntSize(sz_2);
    sz += sz_2;

      
    sz += getTagSize(3);
    size_t sz_3 = 0;
    for(const auto& item:s.packedDoubles) {
        sz_3 += getFixedSize(item);
    }
    sz += getUnsignedVarIntSize(sz_3);
    sz += sz_3;

      
    sz += getTagSize(4);
    size_t sz_4 = 0;
    for(const auto& item:s.packedEnum) {
        sz_4 += getUnsignedVarIntSize(item);
    }
    sz += getUnsignedVarIntSize(sz_4);
    sz += sz_4;

   
  return sz;
}



