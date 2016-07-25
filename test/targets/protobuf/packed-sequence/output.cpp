
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
   const int memcnt = 3;
   bool initFlags[memcnt] = { false };
  initFlags[0] = true;
  initFlags[1] = true;
  initFlags[2] = true;

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
    {
      string temp2;
      if( fieldType != LENGTH_DELIMITED ) return false;
      readOk = i.readString( temp2 );
      s.unpackedStrings.push_back(std::move(temp2));
    }
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

      int16_t temp2;
      int64_t temp = 0;
      readOk = i.readVariantInt64( temp );
      temp2 = temp;
      s.packedVarInts.push_back(std::move(temp2));
      
      if ( !readOk )
        return false;
      }
    } 
    else
    // fall back to non packed
    {
      int16_t temp2;
  if( fieldType != VARINT ) return false;
      int64_t temp = 0;
      readOk = i.readVariantInt64( temp );
      temp2 = temp;
      s.packedVarInts.push_back(std::move(temp2));
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

      double temp2;
      readOk = i.readFixed64Bit( temp2 );
      s.packedDoubles.push_back(std::move(temp2));
      
      if ( !readOk )
        return false;
      }
    } 
    else
    // fall back to non packed
    {
      double temp2;
      if( fieldType != FIXED_64_BIT ) return false;
      readOk = i.readFixed64Bit( temp2 );
      s.packedDoubles.push_back(std::move(temp2));
    }
    }
    initFlags[2] = true;
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

   
  return sz;
}



