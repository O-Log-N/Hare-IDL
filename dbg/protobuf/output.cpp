
#include "output.h"
#include "protobuf/baselib.h"

#include "sample.h"

// IMPLEMENTATIONS


// GET-SIZE

size_t protobufGetSizeBasicTypes( const BasicTypes& s, std::deque<size_t>& stk ) {
  size_t sz = 0;
      
  sz += getTagSize(1);
  sz += getUnsignedVarIntSize(s.max_u32);

      
  sz += getTagSize(2);
  sz += getUnsignedVarIntSize(s.max_u64);

      
  sz += getTagSize(3);
  sz += getSignedVarIntSize(s.max_s32);

      
  sz += getTagSize(4);
  sz += getSignedVarIntSize(s.max_s64);

      
  sz += getTagSize(5);
  sz += getFixedSize(s.aFloat);

      
  sz += getTagSize(6);
  sz += getFixedSize(s.aDouble);

      
  sz += getTagSize(7);
  sz += getUnsignedVarIntSize(s.description.size());
  sz += s.description.size();

      
  sz += getTagSize(8);
  sz += getUnsignedVarIntSize(s.aValue);

      
  sz += getTagSize(9);
  sz += getUnsignedVarIntSize(s.flag);

   
  return sz;
}



// SERIALIZATION

void protobufSerializeBasicTypes( const BasicTypes& s, OProtobufStream& o, std::deque<size_t>& stk ) {

    o.writeUInt(1, s.max_u32);
    o.writeUInt(2, s.max_u64);
    o.writeInt(3, s.max_s32);
    o.writeInt(4, s.max_s64);
    o.writeFloat(5, s.aFloat);
    o.writeDouble(6, s.aDouble);
    o.writeString(7, s.description);
    switch ( s.aValue )
    {
      case /* First */ 1: o.writeUInt( 8, 0 ); break;
      case /* Nothing */ 0: o.writeUInt( 8, 1 ); break;
      case /* Second */ 2: o.writeUInt( 8, 2 ); break;
      default:
        // HAREASSERT( false );
        o.writeUInt( 8, 0 );
        break;
    }
    o.writeUInt(9, s.flag);
}


size_t serializeBasicTypes( const BasicTypes& s, OProtobufStream& o )
{
  std::deque<size_t> stk;
  size_t sz = protobufGetSizeBasicTypes( s, stk );
  protobufSerializeBasicTypes( s, o, stk );
  o.finish();
  return sz;
}
  
// DESERIALIZATION


bool protobufDeserializeBasicTypes( BasicTypes& s, IProtobufStream& i, size_t eos ) {

   const size_t memcnt = 9;
   bool initFlags[memcnt] = { false };
  
  bool readOk = true;

  while( !i.isEndOfStream( eos ) )
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
  if( fieldType != VARINT ) return false;
      uint64_t temp = 0;
      readOk = i.readVariantUInt64( temp );
      s.max_u32 = static_cast<uint32_t>( temp );
    }
    initFlags[1 - 1] = true;
    break;

    case 2:
    {
  if( fieldType != VARINT ) return false;
      uint64_t temp = 0;
      readOk = i.readVariantUInt64( temp );
      s.max_u64 = static_cast<uint64_t>( temp );
    }
    initFlags[2 - 1] = true;
    break;

    case 3:
    {
  if( fieldType != VARINT ) return false;
      int64_t temp = 0;
      readOk = i.readVariantInt64( temp );
      s.max_s32 = static_cast<int32_t>( temp );
    }
    initFlags[3 - 1] = true;
    break;

    case 4:
    {
  if( fieldType != VARINT ) return false;
      int64_t temp = 0;
      readOk = i.readVariantInt64( temp );
      s.max_s64 = static_cast<int64_t>( temp );
    }
    initFlags[4 - 1] = true;
    break;

    case 5:
    {
      if( fieldType != FIXED_32_BIT ) return false;
      readOk = i.readFixed32Bit( s.aFloat );
    }
    initFlags[5 - 1] = true;
    break;

    case 6:
    {
      if( fieldType != FIXED_64_BIT ) return false;
      readOk = i.readFixed64Bit( s.aDouble );
    }
    initFlags[6 - 1] = true;
    break;

    case 7:
    {
      if( fieldType != LENGTH_DELIMITED ) return false;
      readOk = i.readString( s.description );
    }
    initFlags[7 - 1] = true;
    break;

    case 8:
    {
      if( fieldType != VARINT ) return false;
      uint64_t temp = 0;
      readOk = i.readVariantUInt64( temp );
      switch ( temp )
      {
        case 0: s.aValue = s.First; break;
        case 1: s.aValue = s.Nothing; break;
        case 2: s.aValue = s.Second; break;
        default: return false;
      }
    }
    initFlags[8 - 1] = true;
    break;

    case 9:
    {
  if( fieldType != VARINT ) return false;
      uint64_t temp = 0;
      readOk = i.readVariantUInt64( temp );
      s.flag = static_cast<bool>( temp );
    }
    initFlags[9 - 1] = true;
    break;

    default:
      readOk = discardUnexpectedField( fieldType, i );
    }
    if( !readOk )
      return false;
  }

  for ( size_t i = 0; i != memcnt; i++ )
    readOk = readOk && initFlags[i];

  return readOk;
}


  

