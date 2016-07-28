
#include "output.h"
#include "protobuf/baselib.h"

#include "sample.h"

// IMPLEMENTATIONS

// SERIALIZATION

void serializeRoot( const Root& s, OProtobufStream& o ) {
    if(!s.packedVarInts.empty()) {
      size_t sz_1 = 0;
    for(const auto& item:s.packedVarInts) {
          sz_1 += getSignedVarIntSize(item);
    }
      o.writeObjectTagAndSize(1, sz_1);
      for(const auto& item:s.packedVarInts) {
    o.writePackedSignedVarInt(item);
      }
    }
    if(!s.packedDoubles.empty()) {
      size_t sz_2 = 0;
    for(const auto& item:s.packedDoubles) {
        sz_2 += getFixedSize(item);
    }
      o.writeObjectTagAndSize(2, sz_2);
      for(const auto& item:s.packedDoubles) {
    o.writePackedDouble(item);
      }
    }
    for(const auto& item:s.unpackedStrings) {
    o.writeString(3, item);
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

bool deserializeRoot( Root& s, IProtobufStream& i ) {
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
    initFlags[1] = true;
    break;
    case 3:
    {
    string temp2;
      if( fieldType != LENGTH_DELIMITED ) return false;
      readOk = i.readString( temp2 );
    s.unpackedStrings.push_back( std::move( temp2 ) );
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
size_t protobufGetSizeRoot( const Root& s ) {
  size_t sz = 0;
      
    sz += getTagSize(1);
    size_t sz_1 = 0;
    for(const auto& item:s.packedVarInts) {
          sz_1 += getSignedVarIntSize(item);
    }
    sz += getUnsignedVarIntSize(sz_1);
    sz += sz_1;

      
    sz += getTagSize(2);
    size_t sz_2 = 0;
    for(const auto& item:s.packedDoubles) {
        sz_2 += getFixedSize(item);
    }
    sz += getUnsignedVarIntSize(sz_2);
    sz += sz_2;

      
    for(const auto& item:s.unpackedStrings) {
  sz += getTagSize(3);
  sz += getUnsignedVarIntSize(item.size());
  sz += item.size();
      }

   
  return sz;
}



