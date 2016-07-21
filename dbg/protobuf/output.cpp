
#include "output.h"

#include "front-back/idl_tree.h"
#include "protobuf/baselib.h"

// IMPLEMENTATIONS

// SERIALIZATION

void serializeLimit( const Limit& s, OProtobufStream& o ) {
    o.writeUInt(1, s.inclusive);
    o.writeDouble(2, s.value);
}
void serializeLocation( const Location& s, OProtobufStream& o ) {
    o.writeString(1, s.fileName);
    o.writeInt(2, s.lineNumber);
}
void serializeCharacterRange( const CharacterRange& s, OProtobufStream& o ) {
    o.writeUInt(1, s.from);
    o.writeUInt(2, s.to);
}
void serializeCharacterSet( const CharacterSet& s, OProtobufStream& o ) {
    for(const auto& item:s.ranges) {
    auto sz_1 = protobufGetSizeCharacterRange(item);
    o.writeObjectTagAndSize(1, sz_1);
    serializeCharacterRange(item, o);
    }
}
void serializeVariant( const Variant& s, OProtobufStream& o ) {
    switch ( s.kind )
    {
      case 0 /*NONE*/: o.writeUInt(1, 0 ); break;
      case 1 /*NUMBER*/: o.writeUInt(1, 1 ); break;
      case 2 /*STRING*/: o.writeUInt(1, 2 ); break;
        default: assert( false );
    }
    o.writeDouble(2, s.numberValue);
    o.writeString(3, s.stringValue);
}
void serializeDataType( const DataType& s, OProtobufStream& o ) {
    switch ( s.kind )
    {
      case 10 /*BIT_STRING*/: o.writeUInt(1, 0 ); break;
      case 8 /*CHARACTER*/: o.writeUInt(1, 1 ); break;
      case 9 /*CHARACTER_STRING*/: o.writeUInt(1, 2 ); break;
      case 11 /*DICTIONARY*/: o.writeUInt(1, 3 ); break;
      case 12 /*DISCRIMINATED_UNION*/: o.writeUInt(1, 4 ); break;
      case 3 /*ENCODING_SPECIFIC*/: o.writeUInt(1, 5 ); break;
      case 0 /*ENUM*/: o.writeUInt(1, 6 ); break;
      case 6 /*FIXED_POINT*/: o.writeUInt(1, 7 ); break;
      case 7 /*FLOATING_POINT*/: o.writeUInt(1, 8 ); break;
      case 5 /*INTEGER*/: o.writeUInt(1, 9 ); break;
      case 4 /*MAPPING_SPECIFIC*/: o.writeUInt(1, 10 ); break;
      case 1 /*NAMED_TYPE*/: o.writeUInt(1, 11 ); break;
      case 2 /*SEQUENCE*/: o.writeUInt(1, 12 ); break;
        default: assert( false );
    }
    o.writeString(2, s.name);
    o.writeString(3, s.mappingName);
    o.writeString(4, s.encodingName);
    auto sz_5 = protobufGetSize__unique_ptr_DataType(s.keyType);
    o.writeObjectTagAndSize(5, sz_5);
    serialize__unique_ptr_DataType(s.keyType, o);
    auto sz_6 = protobufGetSize__unique_ptr_DataType(s.paramType);
    o.writeObjectTagAndSize(6, sz_6);
    serialize__unique_ptr_DataType(s.paramType, o);
    auto sz_7 = protobufGetSizeLimit(s.lowLimit);
    o.writeObjectTagAndSize(7, sz_7);
    serializeLimit(s.lowLimit, o);
    auto sz_8 = protobufGetSizeLimit(s.highLimit);
    o.writeObjectTagAndSize(8, sz_8);
    serializeLimit(s.highLimit, o);
    o.writeDouble(9, s.fixedPrecision);
    o.writeUInt(10, s.floatingSignificandBits);
    o.writeUInt(11, s.floatingExponentBits);
    auto sz_12 = protobufGetSizeCharacterSet(s.characterSet);
    o.writeObjectTagAndSize(12, sz_12);
    serializeCharacterSet(s.characterSet, o);
    o.writeUInt(13, s.stringMinSize);
    o.writeUInt(14, s.stringMaxSize);
    for(const auto& item:s.encodingAttrs) {
      {
      size_t sz = 0;
  sz += getTagSize(1);
  sz += getUnsignedVarIntSize(item.first.size());
  sz += item.first.size();
  sz += getTagSize(2);
  auto sz_2 = protobufGetSizeVariant(item.second);
  sz += getUnsignedVarIntSize(sz_2);
  sz += sz_2;
//      sz += getUnsignedVarIntSize(sz);
      o.writeObjectTagAndSize(15, sz);
      }
    o.writeString(1, item.first);
    auto sz_2 = protobufGetSizeVariant(item.second);
    o.writeObjectTagAndSize(2, sz_2);
    serializeVariant(item.second, o);
    }
    for(const auto& item:s.mappingAttrs) {
      {
      size_t sz = 0;
  sz += getTagSize(1);
  sz += getUnsignedVarIntSize(item.first.size());
  sz += item.first.size();
  sz += getTagSize(2);
  auto sz_2 = protobufGetSizeVariant(item.second);
  sz += getUnsignedVarIntSize(sz_2);
  sz += sz_2;
//      sz += getUnsignedVarIntSize(sz);
      o.writeObjectTagAndSize(16, sz);
      }
    o.writeString(1, item.first);
    auto sz_2 = protobufGetSizeVariant(item.second);
    o.writeObjectTagAndSize(2, sz_2);
    serializeVariant(item.second, o);
    }
    for(const auto& item:s.enumValues) {
      {
      size_t sz = 0;
  sz += getTagSize(1);
  sz += getUnsignedVarIntSize(item.first.size());
  sz += item.first.size();
  sz += getTagSize(2);
  sz += getUnsignedVarIntSize(item.second);
//      sz += getUnsignedVarIntSize(sz);
      o.writeObjectTagAndSize(17, sz);
      }
    o.writeString(1, item.first);
    o.writeUInt(2, item.second);
    }
}
void serializeEncodingSpecifics( const EncodingSpecifics& s, OProtobufStream& o ) {
    o.writeString(1, s.name);
    for(const auto& item:s.attrs) {
      {
      size_t sz = 0;
  sz += getTagSize(1);
  sz += getUnsignedVarIntSize(item.first.size());
  sz += item.first.size();
  sz += getTagSize(2);
  auto sz_2 = protobufGetSizeVariant(item.second);
  sz += getUnsignedVarIntSize(sz_2);
  sz += sz_2;
//      sz += getUnsignedVarIntSize(sz);
      o.writeObjectTagAndSize(2, sz);
      }
    o.writeString(1, item.first);
    auto sz_2 = protobufGetSizeVariant(item.second);
    o.writeObjectTagAndSize(2, sz_2);
    serializeVariant(item.second, o);
    }
}
void serializeEncodedOrMember( const EncodedOrMember& s, OProtobufStream& o ) {
    auto sz_1 = protobufGetSizeLocation(s.location);
    o.writeObjectTagAndSize(1, sz_1);
    serializeLocation(s.location, o);
}
void serializeDataMember( const DataMember& s, OProtobufStream& o ) {
    auto sz_1 = protobufGetSizeDataType(s.type);
    o.writeObjectTagAndSize(1, sz_1);
    serializeDataType(s.type, o);
    o.writeString(2, s.name);
    o.writeUInt(3, s.extendTo);
    auto sz_4 = protobufGetSizeVariant(s.defaultValue);
    o.writeObjectTagAndSize(4, sz_4);
    serializeVariant(s.defaultValue, o);
    for(const auto& item:s.whenDiscriminant) {
    o.writeString(5, item);
    }
    auto sz_6 = protobufGetSizeEncodedOrMember(s);
    o.writeObjectTagAndSize(6, sz_6);
    serializeEncodedOrMember(s, o);
}
void serializeEncodedMembers( const EncodedMembers& s, OProtobufStream& o ) {
    auto sz_1 = protobufGetSizeEncodingSpecifics(s.encodingSpecifics);
    o.writeObjectTagAndSize(1, sz_1);
    serializeEncodingSpecifics(s.encodingSpecifics, o);
    for(const auto& item:s.members) {
    auto sz_2 = protobufGetSize__unique_ptr_EncodedOrMember(item);
    o.writeObjectTagAndSize(2, sz_2);
    serialize__unique_ptr_EncodedOrMember(item, o);
    }
    auto sz_3 = protobufGetSizeEncodedOrMember(s);
    o.writeObjectTagAndSize(3, sz_3);
    serializeEncodedOrMember(s, o);
}
void serializeStructure( const Structure& s, OProtobufStream& o ) {
    switch ( s.declType )
    {
      case 2 /*ENCODING*/: o.writeUInt(1, 0 ); break;
      case 0 /*IDL*/: o.writeUInt(1, 1 ); break;
      case 1 /*MAPPING*/: o.writeUInt(1, 2 ); break;
        default: assert( false );
    }
    switch ( s.type )
    {
      case 2 /*DISCRIMINATED_UNION*/: o.writeUInt(2, 0 ); break;
      case 1 /*RPC*/: o.writeUInt(2, 1 ); break;
      case 0 /*STRUCT*/: o.writeUInt(2, 2 ); break;
        default: assert( false );
    }
    o.writeString(3, s.name);
    o.writeString(4, s.discriminant);
    o.writeString(5, s.inheritedFrom);
    auto sz_6 = protobufGetSizeEncodedMembers(s);
    o.writeObjectTagAndSize(6, sz_6);
    serializeEncodedMembers(s, o);
}
void serializeTypedef( const Typedef& s, OProtobufStream& o ) {
    auto sz_1 = protobufGetSizeLocation(s.location);
    o.writeObjectTagAndSize(1, sz_1);
    serializeLocation(s.location, o);
    auto sz_2 = protobufGetSizeDataType(s.type);
    o.writeObjectTagAndSize(2, sz_2);
    serializeDataType(s.type, o);
    o.writeString(3, s.name);
}
void serializeRoot( const Root& s, OProtobufStream& o ) {
    for(const auto& item:s.typedefs) {
    auto sz_1 = protobufGetSizeTypedef(item);
    o.writeObjectTagAndSize(1, sz_1);
    serializeTypedef(item, o);
    }
    for(const auto& item:s.structures) {
    auto sz_2 = protobufGetSize__unique_ptr_Structure(item);
    o.writeObjectTagAndSize(2, sz_2);
    serialize__unique_ptr_Structure(item, o);
    }
    size_t sz_3 = 0;
    for(const auto& item:s.packedVarInts) {
          sz_3 += getSignedVarIntSize(item);
    }
    o.writeObjectTagAndSize(3, sz_3);
    for(const auto& item:s.packedVarInts) {
    o.writePackedSignedVarInt(item);
    }
    size_t sz_4 = 0;
    for(const auto& item:s.packedDoubles) {
        sz_4 += getFixedSize(item);
    }
    o.writeObjectTagAndSize(4, sz_4);
    for(const auto& item:s.packedDoubles) {
    o.writePackedDouble(item);
    }
    for(const auto& item:s.unpackedStrings) {
    o.writeString(5, item);
    }
}

void serialize__unique_ptr_DataType( const unique_ptr<DataType>& s, OProtobufStream& o ) {
  //uint8_t disc; if ( s == nullptr ) disc = 1; else if ( typeid( *(s) ) == typeid( DataType ) ) disc = 0; else assert( false );

  if( s == nullptr )
    return;
      else if ( typeid( *s ) == typeid( DataType ) ) {
        auto ptr = dynamic_cast<DataType*>( s.get() );
        auto sz = protobufGetSizeDataType( *ptr );
        o.writeObjectTagAndSize( 1, sz );
        serializeDataType( *ptr, o );
      }
  else
    assert( false );
}
void serialize__unique_ptr_EncodedOrMember( const unique_ptr<EncodedOrMember>& s, OProtobufStream& o ) {
  //uint8_t disc; if ( s == nullptr ) disc = 3; else if ( typeid( *(s) ) == typeid( DataMember ) ) disc = 0; else if ( typeid( *(s) ) == typeid( EncodedMembers ) ) disc = 1; else if ( typeid( *(s) ) == typeid( EncodedOrMember ) ) disc = 2; else assert( false );

  if( s == nullptr )
    return;
      else if ( typeid( *s ) == typeid( DataMember ) ) {
        auto ptr = dynamic_cast<DataMember*>( s.get() );
        auto sz = protobufGetSizeDataMember( *ptr );
        o.writeObjectTagAndSize( 1, sz );
        serializeDataMember( *ptr, o );
      }
      else if ( typeid( *s ) == typeid( EncodedMembers ) ) {
        auto ptr = dynamic_cast<EncodedMembers*>( s.get() );
        auto sz = protobufGetSizeEncodedMembers( *ptr );
        o.writeObjectTagAndSize( 2, sz );
        serializeEncodedMembers( *ptr, o );
      }
      else if ( typeid( *s ) == typeid( EncodedOrMember ) ) {
        auto ptr = dynamic_cast<EncodedOrMember*>( s.get() );
        auto sz = protobufGetSizeEncodedOrMember( *ptr );
        o.writeObjectTagAndSize( 3, sz );
        serializeEncodedOrMember( *ptr, o );
      }
  else
    assert( false );
}
void serialize__unique_ptr_Structure( const unique_ptr<Structure>& s, OProtobufStream& o ) {
  //uint8_t disc; if ( s == nullptr ) disc = 1; else if ( typeid( *(s) ) == typeid( Structure ) ) disc = 0; else assert( false );

  if( s == nullptr )
    return;
      else if ( typeid( *s ) == typeid( Structure ) ) {
        auto ptr = dynamic_cast<Structure*>( s.get() );
        auto sz = protobufGetSizeStructure( *ptr );
        o.writeObjectTagAndSize( 1, sz );
        serializeStructure( *ptr, o );
      }
  else
    assert( false );
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

bool deserializeLimit( Limit& s, IProtobufStream& i ) {
   const int memcnt = 2;
   bool initFlags[memcnt] = { false };

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
  if( fieldType != VARINT ) return false;
      uint64_t temp = 0;
      readOk = i.readVariantUInt64( temp );
      s.inclusive = static_cast<bool>( temp );
    }
    initFlags[0] = true;
    break;
    case 2:
    {
      if( fieldType != FIXED_64_BIT ) return false;
      readOk = i.readFixed64Bit( s.value );
    }
    initFlags[1] = true;
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

bool deserializeLocation( Location& s, IProtobufStream& i ) {
   const int memcnt = 2;
   bool initFlags[memcnt] = { false };

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
      if( fieldType != LENGTH_DELIMITED ) return false;
      readOk = i.readString( s.fileName );
    }
    initFlags[0] = true;
    break;
    case 2:
    {
  if( fieldType != VARINT ) return false;
      int64_t temp = 0;
      readOk = i.readVariantInt64( temp );
      s.lineNumber = temp;
    }
    initFlags[1] = true;
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

bool deserializeCharacterRange( CharacterRange& s, IProtobufStream& i ) {
   const int memcnt = 2;
   bool initFlags[memcnt] = { false };

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
  if( fieldType != VARINT ) return false;
      uint64_t temp = 0;
      readOk = i.readVariantUInt64( temp );
      s.from = temp;
    }
    initFlags[0] = true;
    break;
    case 2:
    {
  if( fieldType != VARINT ) return false;
      uint64_t temp = 0;
      readOk = i.readVariantUInt64( temp );
      s.to = temp;
    }
    initFlags[1] = true;
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

bool deserializeCharacterSet( CharacterSet& s, IProtobufStream& i ) {
   const int memcnt = 1;
   bool initFlags[memcnt] = { false };
  initFlags[0] = true;

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
      CharacterRange temp2;
      if( fieldType != LENGTH_DELIMITED ) return false;
      uint64_t sz = 0;
      i.readVariantUInt64(sz);
      IProtobufStream is = i.makeSubStream(sz);
      readOk = deserializeCharacterRange(temp2, is);
      s.ranges.push_back(std::move(temp2));
    }
    }
    initFlags[0] = true;
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

bool deserializeVariant( Variant& s, IProtobufStream& i ) {
   const int memcnt = 3;
   bool initFlags[memcnt] = { false };

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
      if( fieldType != VARINT ) return false;
      uint64_t temp = 0;
      readOk = i.readVariantUInt64( temp );
      switch ( temp )
      {
	      case 0: s.kind = s.NONE; break;
	      case 1: s.kind = s.NUMBER; break;
	      case 2: s.kind = s.STRING; break;
        default: return false;
      }
    }
    initFlags[0] = true;
    break;
    case 2:
    {
      if( fieldType != FIXED_64_BIT ) return false;
      readOk = i.readFixed64Bit( s.numberValue );
    }
    initFlags[1] = true;
    break;
    case 3:
    {
      if( fieldType != LENGTH_DELIMITED ) return false;
      readOk = i.readString( s.stringValue );
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

bool deserializeDataType( DataType& s, IProtobufStream& i ) {
   const int memcnt = 17;
   bool initFlags[memcnt] = { false };
  initFlags[14] = true;
  initFlags[15] = true;
  initFlags[16] = true;

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
      if( fieldType != VARINT ) return false;
      uint64_t temp = 0;
      readOk = i.readVariantUInt64( temp );
      switch ( temp )
      {
	      case 0: s.kind = s.BIT_STRING; break;
	      case 1: s.kind = s.CHARACTER; break;
	      case 2: s.kind = s.CHARACTER_STRING; break;
	      case 3: s.kind = s.DICTIONARY; break;
	      case 4: s.kind = s.DISCRIMINATED_UNION; break;
	      case 5: s.kind = s.ENCODING_SPECIFIC; break;
	      case 6: s.kind = s.ENUM; break;
	      case 7: s.kind = s.FIXED_POINT; break;
	      case 8: s.kind = s.FLOATING_POINT; break;
	      case 9: s.kind = s.INTEGER; break;
	      case 10: s.kind = s.MAPPING_SPECIFIC; break;
	      case 11: s.kind = s.NAMED_TYPE; break;
	      case 12: s.kind = s.SEQUENCE; break;
        default: return false;
      }
    }
    initFlags[0] = true;
    break;
    case 2:
    {
      if( fieldType != LENGTH_DELIMITED ) return false;
      readOk = i.readString( s.name );
    }
    initFlags[1] = true;
    break;
    case 3:
    {
      if( fieldType != LENGTH_DELIMITED ) return false;
      readOk = i.readString( s.mappingName );
    }
    initFlags[2] = true;
    break;
    case 4:
    {
      if( fieldType != LENGTH_DELIMITED ) return false;
      readOk = i.readString( s.encodingName );
    }
    initFlags[3] = true;
    break;
    case 5:
    {
      if( fieldType != LENGTH_DELIMITED ) return false;
      uint64_t sz = 0;
      i.readVariantUInt64(sz);
      IProtobufStream is = i.makeSubStream(sz);
      readOk = deserialize__unique_ptr_DataType(s.keyType, is);
    }
    initFlags[4] = true;
    break;
    case 6:
    {
      if( fieldType != LENGTH_DELIMITED ) return false;
      uint64_t sz = 0;
      i.readVariantUInt64(sz);
      IProtobufStream is = i.makeSubStream(sz);
      readOk = deserialize__unique_ptr_DataType(s.paramType, is);
    }
    initFlags[5] = true;
    break;
    case 7:
    {
      if( fieldType != LENGTH_DELIMITED ) return false;
      uint64_t sz = 0;
      i.readVariantUInt64(sz);
      IProtobufStream is = i.makeSubStream(sz);
      readOk = deserializeLimit(s.lowLimit, is);
    }
    initFlags[6] = true;
    break;
    case 8:
    {
      if( fieldType != LENGTH_DELIMITED ) return false;
      uint64_t sz = 0;
      i.readVariantUInt64(sz);
      IProtobufStream is = i.makeSubStream(sz);
      readOk = deserializeLimit(s.highLimit, is);
    }
    initFlags[7] = true;
    break;
    case 9:
    {
      if( fieldType != FIXED_64_BIT ) return false;
      readOk = i.readFixed64Bit( s.fixedPrecision );
    }
    initFlags[8] = true;
    break;
    case 10:
    {
  if( fieldType != VARINT ) return false;
      uint64_t temp = 0;
      readOk = i.readVariantUInt64( temp );
      s.floatingSignificandBits = temp;
    }
    initFlags[9] = true;
    break;
    case 11:
    {
  if( fieldType != VARINT ) return false;
      uint64_t temp = 0;
      readOk = i.readVariantUInt64( temp );
      s.floatingExponentBits = temp;
    }
    initFlags[10] = true;
    break;
    case 12:
    {
      if( fieldType != LENGTH_DELIMITED ) return false;
      uint64_t sz = 0;
      i.readVariantUInt64(sz);
      IProtobufStream is = i.makeSubStream(sz);
      readOk = deserializeCharacterSet(s.characterSet, is);
    }
    initFlags[11] = true;
    break;
    case 13:
    {
  if( fieldType != VARINT ) return false;
      uint64_t temp = 0;
      readOk = i.readVariantUInt64( temp );
      s.stringMinSize = temp;
    }
    initFlags[12] = true;
    break;
    case 14:
    {
  if( fieldType != VARINT ) return false;
      uint64_t temp = 0;
      readOk = i.readVariantUInt64( temp );
      s.stringMaxSize = temp;
    }
    initFlags[13] = true;
    break;
    case 15:
    {
  if( fieldType != LENGTH_DELIMITED ) return false;
  uint64_t sz = 0;
  i.readVariantUInt64(sz);
  IProtobufStream is = i.makeSubStream(sz);
  IProtobufStream& i = is;
  string key;
  Variant value;
  bool initFlags[2] = { false };

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
      if( fieldType != LENGTH_DELIMITED ) return false;
      readOk = i.readString( key );
    }
     initFlags[0] = true;
     break;

    case 2:
    {
      if( fieldType != LENGTH_DELIMITED ) return false;
      uint64_t sz = 0;
      i.readVariantUInt64(sz);
      IProtobufStream is = i.makeSubStream(sz);
      readOk = deserializeVariant(value, is);
    }
     initFlags[1] = true;
      break;

    default:
      readOk = discardUnexpectedField( fieldType, i );
    }

    if ( !readOk )
      return false;
   }
   
   readOk = initFlags[0] && initFlags[1];
   if(readOk)
     s.encodingAttrs[key] = value;

    }
    initFlags[14] = true;
    break;
    case 16:
    {
  if( fieldType != LENGTH_DELIMITED ) return false;
  uint64_t sz = 0;
  i.readVariantUInt64(sz);
  IProtobufStream is = i.makeSubStream(sz);
  IProtobufStream& i = is;
  string key;
  Variant value;
  bool initFlags[2] = { false };

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
      if( fieldType != LENGTH_DELIMITED ) return false;
      readOk = i.readString( key );
    }
     initFlags[0] = true;
     break;

    case 2:
    {
      if( fieldType != LENGTH_DELIMITED ) return false;
      uint64_t sz = 0;
      i.readVariantUInt64(sz);
      IProtobufStream is = i.makeSubStream(sz);
      readOk = deserializeVariant(value, is);
    }
     initFlags[1] = true;
      break;

    default:
      readOk = discardUnexpectedField( fieldType, i );
    }

    if ( !readOk )
      return false;
   }
   
   readOk = initFlags[0] && initFlags[1];
   if(readOk)
     s.mappingAttrs[key] = value;

    }
    initFlags[15] = true;
    break;
    case 17:
    {
  if( fieldType != LENGTH_DELIMITED ) return false;
  uint64_t sz = 0;
  i.readVariantUInt64(sz);
  IProtobufStream is = i.makeSubStream(sz);
  IProtobufStream& i = is;
  string key;
  uint32_t value;
  bool initFlags[2] = { false };

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
      if( fieldType != LENGTH_DELIMITED ) return false;
      readOk = i.readString( key );
    }
     initFlags[0] = true;
     break;

    case 2:
    {
  if( fieldType != VARINT ) return false;
      uint64_t temp = 0;
      readOk = i.readVariantUInt64( temp );
      value = temp;
    }
     initFlags[1] = true;
      break;

    default:
      readOk = discardUnexpectedField( fieldType, i );
    }

    if ( !readOk )
      return false;
   }
   
   readOk = initFlags[0] && initFlags[1];
   if(readOk)
     s.enumValues[key] = value;

    }
    initFlags[16] = true;
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

bool deserializeEncodingSpecifics( EncodingSpecifics& s, IProtobufStream& i ) {
   const int memcnt = 2;
   bool initFlags[memcnt] = { false };
  initFlags[1] = true;

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
      if( fieldType != LENGTH_DELIMITED ) return false;
      readOk = i.readString( s.name );
    }
    initFlags[0] = true;
    break;
    case 2:
    {
  if( fieldType != LENGTH_DELIMITED ) return false;
  uint64_t sz = 0;
  i.readVariantUInt64(sz);
  IProtobufStream is = i.makeSubStream(sz);
  IProtobufStream& i = is;
  string key;
  Variant value;
  bool initFlags[2] = { false };

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
      if( fieldType != LENGTH_DELIMITED ) return false;
      readOk = i.readString( key );
    }
     initFlags[0] = true;
     break;

    case 2:
    {
      if( fieldType != LENGTH_DELIMITED ) return false;
      uint64_t sz = 0;
      i.readVariantUInt64(sz);
      IProtobufStream is = i.makeSubStream(sz);
      readOk = deserializeVariant(value, is);
    }
     initFlags[1] = true;
      break;

    default:
      readOk = discardUnexpectedField( fieldType, i );
    }

    if ( !readOk )
      return false;
   }
   
   readOk = initFlags[0] && initFlags[1];
   if(readOk)
     s.attrs[key] = value;

    }
    initFlags[1] = true;
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

bool deserializeEncodedOrMember( EncodedOrMember& s, IProtobufStream& i ) {
   const int memcnt = 1;
   bool initFlags[memcnt] = { false };

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
      if( fieldType != LENGTH_DELIMITED ) return false;
      uint64_t sz = 0;
      i.readVariantUInt64(sz);
      IProtobufStream is = i.makeSubStream(sz);
      readOk = deserializeLocation(s.location, is);
    }
    initFlags[0] = true;
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

bool deserializeDataMember( DataMember& s, IProtobufStream& i ) {
   const int memcnt = 6;
   bool initFlags[memcnt] = { false };
  initFlags[4] = true;

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
      if( fieldType != LENGTH_DELIMITED ) return false;
      uint64_t sz = 0;
      i.readVariantUInt64(sz);
      IProtobufStream is = i.makeSubStream(sz);
      readOk = deserializeDataType(s.type, is);
    }
    initFlags[0] = true;
    break;
    case 2:
    {
      if( fieldType != LENGTH_DELIMITED ) return false;
      readOk = i.readString( s.name );
    }
    initFlags[1] = true;
    break;
    case 3:
    {
  if( fieldType != VARINT ) return false;
      uint64_t temp = 0;
      readOk = i.readVariantUInt64( temp );
      s.extendTo = static_cast<bool>( temp );
    }
    initFlags[2] = true;
    break;
    case 4:
    {
      if( fieldType != LENGTH_DELIMITED ) return false;
      uint64_t sz = 0;
      i.readVariantUInt64(sz);
      IProtobufStream is = i.makeSubStream(sz);
      readOk = deserializeVariant(s.defaultValue, is);
    }
    initFlags[3] = true;
    break;
    case 5:
    {
    {
      string temp2;
      if( fieldType != LENGTH_DELIMITED ) return false;
      readOk = i.readString( temp2 );
      s.whenDiscriminant.push_back(std::move(temp2));
    }
    }
    initFlags[4] = true;
    break;
    case 6:
    {
      if( fieldType != LENGTH_DELIMITED ) return false;
      uint64_t sz = 0;
      i.readVariantUInt64(sz);
      IProtobufStream is = i.makeSubStream(sz);
      readOk = deserializeEncodedOrMember(s, is);
    }
    initFlags[5] = true;
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

bool deserializeEncodedMembers( EncodedMembers& s, IProtobufStream& i ) {
   const int memcnt = 3;
   bool initFlags[memcnt] = { false };
  initFlags[1] = true;

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
      if( fieldType != LENGTH_DELIMITED ) return false;
      uint64_t sz = 0;
      i.readVariantUInt64(sz);
      IProtobufStream is = i.makeSubStream(sz);
      readOk = deserializeEncodingSpecifics(s.encodingSpecifics, is);
    }
    initFlags[0] = true;
    break;
    case 2:
    {
    {
      unique_ptr<EncodedOrMember> temp2;
      if( fieldType != LENGTH_DELIMITED ) return false;
      uint64_t sz = 0;
      i.readVariantUInt64(sz);
      IProtobufStream is = i.makeSubStream(sz);
      readOk = deserialize__unique_ptr_EncodedOrMember(temp2, is);
      s.members.push_back(std::move(temp2));
    }
    }
    initFlags[1] = true;
    break;
    case 3:
    {
      if( fieldType != LENGTH_DELIMITED ) return false;
      uint64_t sz = 0;
      i.readVariantUInt64(sz);
      IProtobufStream is = i.makeSubStream(sz);
      readOk = deserializeEncodedOrMember(s, is);
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

bool deserializeStructure( Structure& s, IProtobufStream& i ) {
   const int memcnt = 6;
   bool initFlags[memcnt] = { false };

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
      if( fieldType != VARINT ) return false;
      uint64_t temp = 0;
      readOk = i.readVariantUInt64( temp );
      switch ( temp )
      {
	      case 0: s.declType = s.ENCODING; break;
	      case 1: s.declType = s.IDL; break;
	      case 2: s.declType = s.MAPPING; break;
        default: return false;
      }
    }
    initFlags[0] = true;
    break;
    case 2:
    {
      if( fieldType != VARINT ) return false;
      uint64_t temp = 0;
      readOk = i.readVariantUInt64( temp );
      switch ( temp )
      {
	      case 0: s.type = s.DISCRIMINATED_UNION; break;
	      case 1: s.type = s.RPC; break;
	      case 2: s.type = s.STRUCT; break;
        default: return false;
      }
    }
    initFlags[1] = true;
    break;
    case 3:
    {
      if( fieldType != LENGTH_DELIMITED ) return false;
      readOk = i.readString( s.name );
    }
    initFlags[2] = true;
    break;
    case 4:
    {
      if( fieldType != LENGTH_DELIMITED ) return false;
      readOk = i.readString( s.discriminant );
    }
    initFlags[3] = true;
    break;
    case 5:
    {
      if( fieldType != LENGTH_DELIMITED ) return false;
      readOk = i.readString( s.inheritedFrom );
    }
    initFlags[4] = true;
    break;
    case 6:
    {
      if( fieldType != LENGTH_DELIMITED ) return false;
      uint64_t sz = 0;
      i.readVariantUInt64(sz);
      IProtobufStream is = i.makeSubStream(sz);
      readOk = deserializeEncodedMembers(s, is);
    }
    initFlags[5] = true;
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

bool deserializeTypedef( Typedef& s, IProtobufStream& i ) {
   const int memcnt = 3;
   bool initFlags[memcnt] = { false };

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
      if( fieldType != LENGTH_DELIMITED ) return false;
      uint64_t sz = 0;
      i.readVariantUInt64(sz);
      IProtobufStream is = i.makeSubStream(sz);
      readOk = deserializeLocation(s.location, is);
    }
    initFlags[0] = true;
    break;
    case 2:
    {
      if( fieldType != LENGTH_DELIMITED ) return false;
      uint64_t sz = 0;
      i.readVariantUInt64(sz);
      IProtobufStream is = i.makeSubStream(sz);
      readOk = deserializeDataType(s.type, is);
    }
    initFlags[1] = true;
    break;
    case 3:
    {
      if( fieldType != LENGTH_DELIMITED ) return false;
      readOk = i.readString( s.name );
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

bool deserializeRoot( Root& s, IProtobufStream& i ) {
   const int memcnt = 5;
   bool initFlags[memcnt] = { false };
  initFlags[0] = true;
  initFlags[1] = true;
  initFlags[2] = true;
  initFlags[3] = true;
  initFlags[4] = true;

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
      Typedef temp2;
      if( fieldType != LENGTH_DELIMITED ) return false;
      uint64_t sz = 0;
      i.readVariantUInt64(sz);
      IProtobufStream is = i.makeSubStream(sz);
      readOk = deserializeTypedef(temp2, is);
      s.typedefs.push_back(std::move(temp2));
    }
    }
    initFlags[0] = true;
    break;
    case 2:
    {
    {
      unique_ptr<Structure> temp2;
      if( fieldType != LENGTH_DELIMITED ) return false;
      uint64_t sz = 0;
      i.readVariantUInt64(sz);
      IProtobufStream is = i.makeSubStream(sz);
      readOk = deserialize__unique_ptr_Structure(temp2, is);
      s.structures.push_back(std::move(temp2));
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
    initFlags[3] = true;
    break;
    case 5:
    {
    {
      string temp2;
      if( fieldType != LENGTH_DELIMITED ) return false;
      readOk = i.readString( temp2 );
      s.unpackedStrings.push_back(std::move(temp2));
    }
    }
    initFlags[4] = true;
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


bool deserialize__unique_ptr_DataType( unique_ptr<DataType>& s, IProtobufStream& i ) {

    int fieldType;
    int fieldNumber;
    bool readOk = true;

    if( i.isEndOfStream() )
      return true;

    readOk = i.readFieldTypeAndID( fieldType, fieldNumber );
    
    if ( !readOk )
      return false;

    if( fieldType != LENGTH_DELIMITED )
      return false;

    uint64_t sz = 0;
    i.readVariantUInt64(sz);
    IProtobufStream is = i.makeSubStream(sz);

    switch ( fieldNumber )
    {
      case 1:
      {
        std::unique_ptr<DataType> ptr( new DataType );
        readOk = deserializeDataType( *ptr, is );
        s = std::move( ptr );
      }
      break;
      default:
      {
        string temp;
        readOk = is.readString( temp );
      }
    }

    return readOk && i.isEndOfStream();
}
bool deserialize__unique_ptr_EncodedOrMember( unique_ptr<EncodedOrMember>& s, IProtobufStream& i ) {

    int fieldType;
    int fieldNumber;
    bool readOk = true;

    if( i.isEndOfStream() )
      return true;

    readOk = i.readFieldTypeAndID( fieldType, fieldNumber );
    
    if ( !readOk )
      return false;

    if( fieldType != LENGTH_DELIMITED )
      return false;

    uint64_t sz = 0;
    i.readVariantUInt64(sz);
    IProtobufStream is = i.makeSubStream(sz);

    switch ( fieldNumber )
    {
      case 1:
      {
        std::unique_ptr<DataMember> ptr( new DataMember );
        readOk = deserializeDataMember( *ptr, is );
        s = std::move( ptr );
      }
      break;
      case 2:
      {
        std::unique_ptr<EncodedMembers> ptr( new EncodedMembers );
        readOk = deserializeEncodedMembers( *ptr, is );
        s = std::move( ptr );
      }
      break;
      case 3:
      {
        std::unique_ptr<EncodedOrMember> ptr( new EncodedOrMember );
        readOk = deserializeEncodedOrMember( *ptr, is );
        s = std::move( ptr );
      }
      break;
      default:
      {
        string temp;
        readOk = is.readString( temp );
      }
    }

    return readOk && i.isEndOfStream();
}
bool deserialize__unique_ptr_Structure( unique_ptr<Structure>& s, IProtobufStream& i ) {

    int fieldType;
    int fieldNumber;
    bool readOk = true;

    if( i.isEndOfStream() )
      return true;

    readOk = i.readFieldTypeAndID( fieldType, fieldNumber );
    
    if ( !readOk )
      return false;

    if( fieldType != LENGTH_DELIMITED )
      return false;

    uint64_t sz = 0;
    i.readVariantUInt64(sz);
    IProtobufStream is = i.makeSubStream(sz);

    switch ( fieldNumber )
    {
      case 1:
      {
        std::unique_ptr<Structure> ptr( new Structure );
        readOk = deserializeStructure( *ptr, is );
        s = std::move( ptr );
      }
      break;
      default:
      {
        string temp;
        readOk = is.readString( temp );
      }
    }

    return readOk && i.isEndOfStream();
}
  
  
// PRINTING
//  INCLUDE TEMPLATE="PRINTING-GENERATE-IMPLEMENTATIONS" PARAM-ROOT=PARAM-ROOT

// GET-SIZE
size_t protobufGetSizeLimit( const Limit& s ) {
  size_t sz = 0;
      
  sz += getTagSize(1);
  sz += getUnsignedVarIntSize(s.inclusive);

      
  sz += getTagSize(2);
  sz += getFixedSize(s.value);

   
  return sz;
}

size_t protobufGetSizeLocation( const Location& s ) {
  size_t sz = 0;
      
  sz += getTagSize(1);
  sz += getUnsignedVarIntSize(s.fileName.size());
  sz += s.fileName.size();

      
  sz += getTagSize(2);
  sz += getSignedVarIntSize(s.lineNumber);

   
  return sz;
}

size_t protobufGetSizeCharacterRange( const CharacterRange& s ) {
  size_t sz = 0;
      
  sz += getTagSize(1);
  sz += getUnsignedVarIntSize(s.from);

      
  sz += getTagSize(2);
  sz += getUnsignedVarIntSize(s.to);

   
  return sz;
}

size_t protobufGetSizeCharacterSet( const CharacterSet& s ) {
  size_t sz = 0;
      
    for(const auto& item:s.ranges) {
  sz += getTagSize(1);
  auto sz_1 = protobufGetSizeCharacterRange(item);
  sz += getUnsignedVarIntSize(sz_1);
  sz += sz_1;
      }

   
  return sz;
}

size_t protobufGetSizeVariant( const Variant& s ) {
  size_t sz = 0;
      
  sz += getTagSize(1);
  sz += getUnsignedVarIntSize(s.kind);

      
  sz += getTagSize(2);
  sz += getFixedSize(s.numberValue);

      
  sz += getTagSize(3);
  sz += getUnsignedVarIntSize(s.stringValue.size());
  sz += s.stringValue.size();

   
  return sz;
}

size_t protobufGetSizeDataType( const DataType& s ) {
  size_t sz = 0;
      
  sz += getTagSize(1);
  sz += getUnsignedVarIntSize(s.kind);

      
  sz += getTagSize(2);
  sz += getUnsignedVarIntSize(s.name.size());
  sz += s.name.size();

      
  sz += getTagSize(3);
  sz += getUnsignedVarIntSize(s.mappingName.size());
  sz += s.mappingName.size();

      
  sz += getTagSize(4);
  sz += getUnsignedVarIntSize(s.encodingName.size());
  sz += s.encodingName.size();

      
  sz += getTagSize(5);
  auto sz_5 = protobufGetSize__unique_ptr_DataType(s.keyType);
  sz += getUnsignedVarIntSize(sz_5);
  sz += sz_5;

      
  sz += getTagSize(6);
  auto sz_6 = protobufGetSize__unique_ptr_DataType(s.paramType);
  sz += getUnsignedVarIntSize(sz_6);
  sz += sz_6;

      
  sz += getTagSize(7);
  auto sz_7 = protobufGetSizeLimit(s.lowLimit);
  sz += getUnsignedVarIntSize(sz_7);
  sz += sz_7;

      
  sz += getTagSize(8);
  auto sz_8 = protobufGetSizeLimit(s.highLimit);
  sz += getUnsignedVarIntSize(sz_8);
  sz += sz_8;

      
  sz += getTagSize(9);
  sz += getFixedSize(s.fixedPrecision);

      
  sz += getTagSize(10);
  sz += getUnsignedVarIntSize(s.floatingSignificandBits);

      
  sz += getTagSize(11);
  sz += getUnsignedVarIntSize(s.floatingExponentBits);

      
  sz += getTagSize(12);
  auto sz_12 = protobufGetSizeCharacterSet(s.characterSet);
  sz += getUnsignedVarIntSize(sz_12);
  sz += sz_12;

      
  sz += getTagSize(13);
  sz += getUnsignedVarIntSize(s.stringMinSize);

      
  sz += getTagSize(14);
  sz += getUnsignedVarIntSize(s.stringMaxSize);

      
    for(const auto& item:s.encodingAttrs) {
      sz += getTagSize(15);
      size_t sz_begin_15 = sz;
  sz += getTagSize(1);
  sz += getUnsignedVarIntSize(item.first.size());
  sz += item.first.size();
  sz += getTagSize(2);
  auto sz_2 = protobufGetSizeVariant(item.second);
  sz += getUnsignedVarIntSize(sz_2);
  sz += sz_2;
      sz += getUnsignedVarIntSize(sz - sz_begin_15);
    }

      
    for(const auto& item:s.mappingAttrs) {
      sz += getTagSize(16);
      size_t sz_begin_16 = sz;
  sz += getTagSize(1);
  sz += getUnsignedVarIntSize(item.first.size());
  sz += item.first.size();
  sz += getTagSize(2);
  auto sz_2 = protobufGetSizeVariant(item.second);
  sz += getUnsignedVarIntSize(sz_2);
  sz += sz_2;
      sz += getUnsignedVarIntSize(sz - sz_begin_16);
    }

      
    for(const auto& item:s.enumValues) {
      sz += getTagSize(17);
      size_t sz_begin_17 = sz;
  sz += getTagSize(1);
  sz += getUnsignedVarIntSize(item.first.size());
  sz += item.first.size();
  sz += getTagSize(2);
  sz += getUnsignedVarIntSize(item.second);
      sz += getUnsignedVarIntSize(sz - sz_begin_17);
    }

   
  return sz;
}

size_t protobufGetSizeEncodingSpecifics( const EncodingSpecifics& s ) {
  size_t sz = 0;
      
  sz += getTagSize(1);
  sz += getUnsignedVarIntSize(s.name.size());
  sz += s.name.size();

      
    for(const auto& item:s.attrs) {
      sz += getTagSize(2);
      size_t sz_begin_2 = sz;
  sz += getTagSize(1);
  sz += getUnsignedVarIntSize(item.first.size());
  sz += item.first.size();
  sz += getTagSize(2);
  auto sz_2 = protobufGetSizeVariant(item.second);
  sz += getUnsignedVarIntSize(sz_2);
  sz += sz_2;
      sz += getUnsignedVarIntSize(sz - sz_begin_2);
    }

   
  return sz;
}

size_t protobufGetSizeEncodedOrMember( const EncodedOrMember& s ) {
  size_t sz = 0;
      
  sz += getTagSize(1);
  auto sz_1 = protobufGetSizeLocation(s.location);
  sz += getUnsignedVarIntSize(sz_1);
  sz += sz_1;

   
  return sz;
}

size_t protobufGetSizeDataMember( const DataMember& s ) {
  size_t sz = 0;
      
  sz += getTagSize(1);
  auto sz_1 = protobufGetSizeDataType(s.type);
  sz += getUnsignedVarIntSize(sz_1);
  sz += sz_1;

      
  sz += getTagSize(2);
  sz += getUnsignedVarIntSize(s.name.size());
  sz += s.name.size();

      
  sz += getTagSize(3);
  sz += getUnsignedVarIntSize(s.extendTo);

      
  sz += getTagSize(4);
  auto sz_4 = protobufGetSizeVariant(s.defaultValue);
  sz += getUnsignedVarIntSize(sz_4);
  sz += sz_4;

      
    for(const auto& item:s.whenDiscriminant) {
  sz += getTagSize(5);
  sz += getUnsignedVarIntSize(item.size());
  sz += item.size();
      }

      
  sz += getTagSize(6);
  auto sz_6 = protobufGetSizeEncodedOrMember(s);
  sz += getUnsignedVarIntSize(sz_6);
  sz += sz_6;

   
  return sz;
}

size_t protobufGetSizeEncodedMembers( const EncodedMembers& s ) {
  size_t sz = 0;
      
  sz += getTagSize(1);
  auto sz_1 = protobufGetSizeEncodingSpecifics(s.encodingSpecifics);
  sz += getUnsignedVarIntSize(sz_1);
  sz += sz_1;

      
    for(const auto& item:s.members) {
  sz += getTagSize(2);
  auto sz_2 = protobufGetSize__unique_ptr_EncodedOrMember(item);
  sz += getUnsignedVarIntSize(sz_2);
  sz += sz_2;
      }

      
  sz += getTagSize(3);
  auto sz_3 = protobufGetSizeEncodedOrMember(s);
  sz += getUnsignedVarIntSize(sz_3);
  sz += sz_3;

   
  return sz;
}

size_t protobufGetSizeStructure( const Structure& s ) {
  size_t sz = 0;
      
  sz += getTagSize(1);
  sz += getUnsignedVarIntSize(s.declType);

      
  sz += getTagSize(2);
  sz += getUnsignedVarIntSize(s.type);

      
  sz += getTagSize(3);
  sz += getUnsignedVarIntSize(s.name.size());
  sz += s.name.size();

      
  sz += getTagSize(4);
  sz += getUnsignedVarIntSize(s.discriminant.size());
  sz += s.discriminant.size();

      
  sz += getTagSize(5);
  sz += getUnsignedVarIntSize(s.inheritedFrom.size());
  sz += s.inheritedFrom.size();

      
  sz += getTagSize(6);
  auto sz_6 = protobufGetSizeEncodedMembers(s);
  sz += getUnsignedVarIntSize(sz_6);
  sz += sz_6;

   
  return sz;
}

size_t protobufGetSizeTypedef( const Typedef& s ) {
  size_t sz = 0;
      
  sz += getTagSize(1);
  auto sz_1 = protobufGetSizeLocation(s.location);
  sz += getUnsignedVarIntSize(sz_1);
  sz += sz_1;

      
  sz += getTagSize(2);
  auto sz_2 = protobufGetSizeDataType(s.type);
  sz += getUnsignedVarIntSize(sz_2);
  sz += sz_2;

      
  sz += getTagSize(3);
  sz += getUnsignedVarIntSize(s.name.size());
  sz += s.name.size();

   
  return sz;
}

size_t protobufGetSizeRoot( const Root& s ) {
  size_t sz = 0;
      
    for(const auto& item:s.typedefs) {
  sz += getTagSize(1);
  auto sz_1 = protobufGetSizeTypedef(item);
  sz += getUnsignedVarIntSize(sz_1);
  sz += sz_1;
      }

      
    for(const auto& item:s.structures) {
  sz += getTagSize(2);
  auto sz_2 = protobufGetSize__unique_ptr_Structure(item);
  sz += getUnsignedVarIntSize(sz_2);
  sz += sz_2;
      }

      
    sz += getTagSize(3);
    size_t sz_3 = 0;
    for(const auto& item:s.packedVarInts) {
          sz_3 += getSignedVarIntSize(item);
    }
    sz += getUnsignedVarIntSize(sz_3);
    sz += sz_3;

      
    sz += getTagSize(4);
    size_t sz_4 = 0;
    for(const auto& item:s.packedDoubles) {
        sz_4 += getFixedSize(item);
    }
    sz += getUnsignedVarIntSize(sz_4);
    sz += sz_4;

      
    for(const auto& item:s.unpackedStrings) {
  sz += getTagSize(5);
  sz += getUnsignedVarIntSize(item.size());
  sz += item.size();
      }

   
  return sz;
}


size_t protobufGetSize__unique_ptr_DataType( const unique_ptr<DataType>& s ) {

//  uint8_t disc; if ( s == nullptr ) disc = 1; else if ( typeid( *(s) ) == typeid( DataType ) ) disc = 0; else assert( false );
  if( s == nullptr )
    return 0;
      else if ( typeid( *s ) == typeid( DataType ) ) {
        auto ptr = dynamic_cast<DataType*>( s.get() );
        auto sz = protobufGetSizeDataType( *ptr );
        sz += getUnsignedVarIntSize( sz );
        sz += getTagSize( 1 );
        return sz;
      }
  else {
    assert( false );
    return 0; // silence
  }
}
size_t protobufGetSize__unique_ptr_EncodedOrMember( const unique_ptr<EncodedOrMember>& s ) {

//  uint8_t disc; if ( s == nullptr ) disc = 3; else if ( typeid( *(s) ) == typeid( DataMember ) ) disc = 0; else if ( typeid( *(s) ) == typeid( EncodedMembers ) ) disc = 1; else if ( typeid( *(s) ) == typeid( EncodedOrMember ) ) disc = 2; else assert( false );
  if( s == nullptr )
    return 0;
      else if ( typeid( *s ) == typeid( DataMember ) ) {
        auto ptr = dynamic_cast<DataMember*>( s.get() );
        auto sz = protobufGetSizeDataMember( *ptr );
        sz += getUnsignedVarIntSize( sz );
        sz += getTagSize( 1 );
        return sz;
      }
      else if ( typeid( *s ) == typeid( EncodedMembers ) ) {
        auto ptr = dynamic_cast<EncodedMembers*>( s.get() );
        auto sz = protobufGetSizeEncodedMembers( *ptr );
        sz += getUnsignedVarIntSize( sz );
        sz += getTagSize( 2 );
        return sz;
      }
      else if ( typeid( *s ) == typeid( EncodedOrMember ) ) {
        auto ptr = dynamic_cast<EncodedOrMember*>( s.get() );
        auto sz = protobufGetSizeEncodedOrMember( *ptr );
        sz += getUnsignedVarIntSize( sz );
        sz += getTagSize( 3 );
        return sz;
      }
  else {
    assert( false );
    return 0; // silence
  }
}
size_t protobufGetSize__unique_ptr_Structure( const unique_ptr<Structure>& s ) {

//  uint8_t disc; if ( s == nullptr ) disc = 1; else if ( typeid( *(s) ) == typeid( Structure ) ) disc = 0; else assert( false );
  if( s == nullptr )
    return 0;
      else if ( typeid( *s ) == typeid( Structure ) ) {
        auto ptr = dynamic_cast<Structure*>( s.get() );
        auto sz = protobufGetSizeStructure( *ptr );
        sz += getUnsignedVarIntSize( sz );
        sz += getTagSize( 1 );
        return sz;
      }
  else {
    assert( false );
    return 0; // silence
  }
}

