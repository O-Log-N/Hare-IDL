
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
    size_t sz_1 = protobufGetSizeCharacterRange(item);
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
        default: assert( 0 );
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
        default: assert( 0 );
    }
    o.writeString(2, s.name);
    o.writeString(3, s.mappingName);
    o.writeString(4, s.encodingName);
    size_t sz_5 = protobufGetSize__unique_ptr_DataType(s.keyType);
    o.writeObjectTagAndSize(5, sz_5);
    serialize__unique_ptr_DataType(s.keyType, o);
    size_t sz_6 = protobufGetSize__unique_ptr_DataType(s.paramType);
    o.writeObjectTagAndSize(6, sz_6);
    serialize__unique_ptr_DataType(s.paramType, o);
    size_t sz_7 = protobufGetSizeLimit(s.lowLimit);
    o.writeObjectTagAndSize(7, sz_7);
    serializeLimit(s.lowLimit, o);
    size_t sz_8 = protobufGetSizeLimit(s.highLimit);
    o.writeObjectTagAndSize(8, sz_8);
    serializeLimit(s.highLimit, o);
    o.writeDouble(9, s.fixedPrecision);
    o.writeUInt(10, s.floatingSignificandBits);
    o.writeUInt(11, s.floatingExponentBits);
    size_t sz_12 = protobufGetSizeCharacterSet(s.characterSet);
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
  size_t sz_2 = protobufGetSizeVariant(item.second);
  sz += getUnsignedVarIntSize(sz_2);
  sz += sz_2;
//      sz += getUnsignedVarIntSize(sz);
      o.writeObjectTagAndSize(15, sz);
      }
    o.writeString(1, item.first);
    size_t sz_2 = protobufGetSizeVariant(item.second);
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
  size_t sz_2 = protobufGetSizeVariant(item.second);
  sz += getUnsignedVarIntSize(sz_2);
  sz += sz_2;
//      sz += getUnsignedVarIntSize(sz);
      o.writeObjectTagAndSize(16, sz);
      }
    o.writeString(1, item.first);
    size_t sz_2 = protobufGetSizeVariant(item.second);
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
  size_t sz_2 = protobufGetSizeVariant(item.second);
  sz += getUnsignedVarIntSize(sz_2);
  sz += sz_2;
//      sz += getUnsignedVarIntSize(sz);
      o.writeObjectTagAndSize(2, sz);
      }
    o.writeString(1, item.first);
    size_t sz_2 = protobufGetSizeVariant(item.second);
    o.writeObjectTagAndSize(2, sz_2);
    serializeVariant(item.second, o);
    }

}

void serializeEncodedOrMember( const EncodedOrMember& s, OProtobufStream& o ) {
    size_t sz_1 = protobufGetSizeLocation(s.location);
    o.writeObjectTagAndSize(1, sz_1);
    serializeLocation(s.location, o);
}

void serializeDataMember( const DataMember& s, OProtobufStream& o ) {
    size_t sz_1 = protobufGetSizeDataType(s.type);
    o.writeObjectTagAndSize(1, sz_1);
    serializeDataType(s.type, o);
    o.writeString(2, s.name);
    o.writeUInt(3, s.extendTo);
    size_t sz_4 = protobufGetSizeVariant(s.defaultValue);
    o.writeObjectTagAndSize(4, sz_4);
    serializeVariant(s.defaultValue, o);
    for(const auto& item:s.whenDiscriminant) {
    o.writeString(5, item);
    }
    size_t sz_6 = protobufGetSizeEncodedOrMember(s);
    o.writeObjectTagAndSize(6, sz_6);
    serializeEncodedOrMember(s, o);
}

void serializeEncodedMembers( const EncodedMembers& s, OProtobufStream& o ) {
    size_t sz_1 = protobufGetSizeEncodingSpecifics(s.encodingSpecifics);
    o.writeObjectTagAndSize(1, sz_1);
    serializeEncodingSpecifics(s.encodingSpecifics, o);
    for(const auto& item:s.members) {
    size_t sz_2 = protobufGetSize__unique_ptr_EncodedOrMember(item);
    o.writeObjectTagAndSize(2, sz_2);
    serialize__unique_ptr_EncodedOrMember(item, o);
    }
    size_t sz_3 = protobufGetSizeEncodedOrMember(s);
    o.writeObjectTagAndSize(3, sz_3);
    serializeEncodedOrMember(s, o);
}

void serializeStructure( const Structure& s, OProtobufStream& o ) {
    switch ( s.declType )
    {
        case 2 /*ENCODING*/: o.writeUInt(1, 0 ); break;
        case 0 /*IDL*/: o.writeUInt(1, 1 ); break;
        case 1 /*MAPPING*/: o.writeUInt(1, 2 ); break;
        default: assert( 0 );
    }
    switch ( s.type )
    {
        case 2 /*DISCRIMINATED_UNION*/: o.writeUInt(2, 0 ); break;
        case 1 /*RPC*/: o.writeUInt(2, 1 ); break;
        case 0 /*STRUCT*/: o.writeUInt(2, 2 ); break;
        default: assert( 0 );
    }
    o.writeString(3, s.name);
    o.writeString(4, s.discriminant);
    o.writeString(5, s.inheritedFrom);
    size_t sz_6 = protobufGetSizeEncodedMembers(s);
    o.writeObjectTagAndSize(6, sz_6);
    serializeEncodedMembers(s, o);
}

void serializeTypedef( const Typedef& s, OProtobufStream& o ) {
    size_t sz_1 = protobufGetSizeLocation(s.location);
    o.writeObjectTagAndSize(1, sz_1);
    serializeLocation(s.location, o);
    size_t sz_2 = protobufGetSizeDataType(s.type);
    o.writeObjectTagAndSize(2, sz_2);
    serializeDataType(s.type, o);
    o.writeString(3, s.name);
}

void serializeRoot( const Root& s, OProtobufStream& o ) {
    for(const auto& item:s.typedefs) {
    size_t sz_1 = protobufGetSizeTypedef(item);
    o.writeObjectTagAndSize(1, sz_1);
    serializeTypedef(item, o);
    }
    for(const auto& item:s.structures) {
    size_t sz_2 = protobufGetSize__unique_ptr_Structure(item);
    o.writeObjectTagAndSize(2, sz_2);
    serialize__unique_ptr_Structure(item, o);
    }
}


void serialize__unique_ptr_DataType( const unique_ptr<DataType>& s, OProtobufStream& o ) {
  
  if(s.get() == nullptr) {
    return;
  }
       else if ( typeid( *s ) == typeid( DataType ) ) {
         auto ptr = dynamic_cast<DataType*>(s.get());
    size_t sz_1 = protobufGetSizeDataType(*ptr);
    o.writeObjectTagAndSize(1, sz_1);
    serializeDataType(*ptr, o);

       }
   else {
     ;// TODO assert?
   }
}
void serialize__unique_ptr_EncodedOrMember( const unique_ptr<EncodedOrMember>& s, OProtobufStream& o ) {
  
  if(s.get() == nullptr) {
    return;
  }
       else if ( typeid( *s ) == typeid( DataMember ) ) {
         auto ptr = dynamic_cast<DataMember*>(s.get());
    size_t sz_1 = protobufGetSizeDataMember(*ptr);
    o.writeObjectTagAndSize(1, sz_1);
    serializeDataMember(*ptr, o);

       }
       else if ( typeid( *s ) == typeid( EncodedMembers ) ) {
         auto ptr = dynamic_cast<EncodedMembers*>(s.get());
    size_t sz_2 = protobufGetSizeEncodedMembers(*ptr);
    o.writeObjectTagAndSize(2, sz_2);
    serializeEncodedMembers(*ptr, o);

       }
       else if ( typeid( *s ) == typeid( EncodedOrMember ) ) {
         auto ptr = dynamic_cast<EncodedOrMember*>(s.get());
    size_t sz_3 = protobufGetSizeEncodedOrMember(*ptr);
    o.writeObjectTagAndSize(3, sz_3);
    serializeEncodedOrMember(*ptr, o);

       }
   else {
     ;// TODO assert?
   }
}
void serialize__unique_ptr_Structure( const unique_ptr<Structure>& s, OProtobufStream& o ) {
  
  if(s.get() == nullptr) {
    return;
  }
       else if ( typeid( *s ) == typeid( Structure ) ) {
         auto ptr = dynamic_cast<Structure*>(s.get());
    size_t sz_1 = protobufGetSizeStructure(*ptr);
    o.writeObjectTagAndSize(1, sz_1);
    serializeStructure(*ptr, o);

       }
   else {
     ;// TODO assert?
   }
}

  
// DESERIALIZATION
bool deserializeLimit( Limit& s, IProtobufStream& i ) {
   int type;
   int fieldNumber;
   bool readret;
   const int memcnt = 2;
   uint8_t initFlags[memcnt] = { 0 };
   do
   {
      readret = i.readFieldTypeAndID( type, fieldNumber );
	  if ( !readret )
		  break;
	  switch ( fieldNumber )
	  {
    case 1:
    {
      uint64_t temp = 0;
      initFlags[0] = i.readVariantUInt64( temp );
      s.inclusive = static_cast<bool>( temp );
      break;
    }
    case 2:
    {
      initFlags[1] = i.readFixed64Bit( s.value );
      break;
    }
		default:
		{
			// TODO: what?
			break;
		}
	  }
   }
   while ( 1 ); // TODO: stop criterion (except the end of the message?

   bool OK = true;
   for ( int i=0; i<memcnt; i++ )
     OK = OK && initFlags[i] != 0;

   return OK;
}

bool deserializeLocation( Location& s, IProtobufStream& i ) {
   int type;
   int fieldNumber;
   bool readret;
   const int memcnt = 2;
   uint8_t initFlags[memcnt] = { 0 };
   do
   {
      readret = i.readFieldTypeAndID( type, fieldNumber );
	  if ( !readret )
		  break;
	  switch ( fieldNumber )
	  {
    case 1:
    {
     initFlags[0] = i.readString( s.fileName );
      break;
    }
    case 2:
    {
      int64_t temp = 0;
      initFlags[1] = i.readVariantInt64( temp );
      s.lineNumber = temp;
      break;
    }
		default:
		{
			// TODO: what?
			break;
		}
	  }
   }
   while ( 1 ); // TODO: stop criterion (except the end of the message?

   bool OK = true;
   for ( int i=0; i<memcnt; i++ )
     OK = OK && initFlags[i] != 0;

   return OK;
}

bool deserializeCharacterRange( CharacterRange& s, IProtobufStream& i ) {
   int type;
   int fieldNumber;
   bool readret;
   const int memcnt = 2;
   uint8_t initFlags[memcnt] = { 0 };
   do
   {
      readret = i.readFieldTypeAndID( type, fieldNumber );
	  if ( !readret )
		  break;
	  switch ( fieldNumber )
	  {
    case 1:
    {
      uint64_t temp = 0;
      initFlags[0] = i.readVariantUInt64( temp );
      s.from = temp;
      break;
    }
    case 2:
    {
      uint64_t temp = 0;
      initFlags[1] = i.readVariantUInt64( temp );
      s.to = temp;
      break;
    }
		default:
		{
			// TODO: what?
			break;
		}
	  }
   }
   while ( 1 ); // TODO: stop criterion (except the end of the message?

   bool OK = true;
   for ( int i=0; i<memcnt; i++ )
     OK = OK && initFlags[i] != 0;

   return OK;
}

bool deserializeCharacterSet( CharacterSet& s, IProtobufStream& i ) {
   int type;
   int fieldNumber;
   bool readret;
   const int memcnt = 1;
   uint8_t initFlags[memcnt] = { 0 };
  initFlags[0] = true;
   do
   {
      readret = i.readFieldTypeAndID( type, fieldNumber );
	  if ( !readret )
		  break;
	  switch ( fieldNumber )
	  {
    case 1:
    {
      CharacterRange temp2;
    uint64_t sz_0 = 0;
    i.readVariantUInt64(sz_0);
    IProtobufStream is_0 = i.makeSubStream(sz_0);
    initFlags[0] = deserializeCharacterRange(temp2, is_0);
      s.ranges.push_back(std::move(temp2));

      break;
    }
		default:
		{
			// TODO: what?
			break;
		}
	  }
   }
   while ( 1 ); // TODO: stop criterion (except the end of the message?

   bool OK = true;
   for ( int i=0; i<memcnt; i++ )
     OK = OK && initFlags[i] != 0;

   return OK;
}

bool deserializeVariant( Variant& s, IProtobufStream& i ) {
   int type;
   int fieldNumber;
   bool readret;
   const int memcnt = 3;
   uint8_t initFlags[memcnt] = { 0 };
   do
   {
      readret = i.readFieldTypeAndID( type, fieldNumber );
	  if ( !readret )
		  break;
	  switch ( fieldNumber )
	  {
    case 1:
    {
   {
       uint64_t temp = 0;
       initFlags[0] = i.readVariantUInt64( temp );
       switch ( temp )
       {
	      case 0: s.kind = s.NONE; break;
	      case 1: s.kind = s.NUMBER; break;
	      case 2: s.kind = s.STRING; break;
          default: assert(0);
       }
   }
      break;
    }
    case 2:
    {
      initFlags[1] = i.readFixed64Bit( s.numberValue );
      break;
    }
    case 3:
    {
     initFlags[2] = i.readString( s.stringValue );
      break;
    }
		default:
		{
			// TODO: what?
			break;
		}
	  }
   }
   while ( 1 ); // TODO: stop criterion (except the end of the message?

   bool OK = true;
   for ( int i=0; i<memcnt; i++ )
     OK = OK && initFlags[i] != 0;

   return OK;
}

bool deserializeDataType( DataType& s, IProtobufStream& i ) {
   int type;
   int fieldNumber;
   bool readret;
   const int memcnt = 17;
   uint8_t initFlags[memcnt] = { 0 };
  initFlags[14] = true;
  initFlags[15] = true;
  initFlags[16] = true;
   do
   {
      readret = i.readFieldTypeAndID( type, fieldNumber );
	  if ( !readret )
		  break;
	  switch ( fieldNumber )
	  {
    case 1:
    {
   {
       uint64_t temp = 0;
       initFlags[0] = i.readVariantUInt64( temp );
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
          default: assert(0);
       }
   }
      break;
    }
    case 2:
    {
     initFlags[1] = i.readString( s.name );
      break;
    }
    case 3:
    {
     initFlags[2] = i.readString( s.mappingName );
      break;
    }
    case 4:
    {
     initFlags[3] = i.readString( s.encodingName );
      break;
    }
    case 5:
    {
    uint64_t sz_4 = 0;
    i.readVariantUInt64(sz_4);
    IProtobufStream is_4 = i.makeSubStream(sz_4);
    initFlags[4] = deserialize__unique_ptr_DataType(s.keyType, is_4);
      break;
    }
    case 6:
    {
    uint64_t sz_5 = 0;
    i.readVariantUInt64(sz_5);
    IProtobufStream is_5 = i.makeSubStream(sz_5);
    initFlags[5] = deserialize__unique_ptr_DataType(s.paramType, is_5);
      break;
    }
    case 7:
    {
    uint64_t sz_6 = 0;
    i.readVariantUInt64(sz_6);
    IProtobufStream is_6 = i.makeSubStream(sz_6);
    initFlags[6] = deserializeLimit(s.lowLimit, is_6);
      break;
    }
    case 8:
    {
    uint64_t sz_7 = 0;
    i.readVariantUInt64(sz_7);
    IProtobufStream is_7 = i.makeSubStream(sz_7);
    initFlags[7] = deserializeLimit(s.highLimit, is_7);
      break;
    }
    case 9:
    {
      initFlags[8] = i.readFixed64Bit( s.fixedPrecision );
      break;
    }
    case 10:
    {
      uint64_t temp = 0;
      initFlags[9] = i.readVariantUInt64( temp );
      s.floatingSignificandBits = temp;
      break;
    }
    case 11:
    {
      uint64_t temp = 0;
      initFlags[10] = i.readVariantUInt64( temp );
      s.floatingExponentBits = temp;
      break;
    }
    case 12:
    {
    uint64_t sz_11 = 0;
    i.readVariantUInt64(sz_11);
    IProtobufStream is_11 = i.makeSubStream(sz_11);
    initFlags[11] = deserializeCharacterSet(s.characterSet, is_11);
      break;
    }
    case 13:
    {
      uint64_t temp = 0;
      initFlags[12] = i.readVariantUInt64( temp );
      s.stringMinSize = temp;
      break;
    }
    case 14:
    {
      uint64_t temp = 0;
      initFlags[13] = i.readVariantUInt64( temp );
      s.stringMaxSize = temp;
      break;
    }
    case 15:
    {
  bool ok = false;
  {
    uint64_t sz_14 = 0;
    i.readVariantUInt64(sz_14);
    IProtobufStream is_14 = i.makeSubStream(sz_14);
    IProtobufStream& i = is_14;
    string key;
    Variant value;
    bool initFlags[3] = { false };
   do
   {
      readret = i.readFieldTypeAndID( type, fieldNumber );
    if ( !readret )
      break;
    switch ( fieldNumber )
    {
        case 1:
    {
     initFlags[1] = i.readString( key );
     break;
    }

    case 2:
    {
    uint64_t sz_2 = 0;
    i.readVariantUInt64(sz_2);
    IProtobufStream is_2 = i.makeSubStream(sz_2);
    initFlags[2] = deserializeVariant(value, is_2);
      break;
    }

    default:
    {
      // TODO: what?
      break;
    }
    }
   }
   while ( 1 ); // TODO: stop criterion (except the end of the message?
   
   ok = initFlags[1] && initFlags[2];
   if(ok)
     s.encodingAttrs[key] = value;
  }
  initFlags[14] = ok;
      break;
    }
    case 16:
    {
  bool ok = false;
  {
    uint64_t sz_15 = 0;
    i.readVariantUInt64(sz_15);
    IProtobufStream is_15 = i.makeSubStream(sz_15);
    IProtobufStream& i = is_15;
    string key;
    Variant value;
    bool initFlags[3] = { false };
   do
   {
      readret = i.readFieldTypeAndID( type, fieldNumber );
    if ( !readret )
      break;
    switch ( fieldNumber )
    {
        case 1:
    {
     initFlags[1] = i.readString( key );
     break;
    }

    case 2:
    {
    uint64_t sz_2 = 0;
    i.readVariantUInt64(sz_2);
    IProtobufStream is_2 = i.makeSubStream(sz_2);
    initFlags[2] = deserializeVariant(value, is_2);
      break;
    }

    default:
    {
      // TODO: what?
      break;
    }
    }
   }
   while ( 1 ); // TODO: stop criterion (except the end of the message?
   
   ok = initFlags[1] && initFlags[2];
   if(ok)
     s.mappingAttrs[key] = value;
  }
  initFlags[15] = ok;
      break;
    }
    case 17:
    {
  bool ok = false;
  {
    uint64_t sz_16 = 0;
    i.readVariantUInt64(sz_16);
    IProtobufStream is_16 = i.makeSubStream(sz_16);
    IProtobufStream& i = is_16;
    string key;
    uint32_t value;
    bool initFlags[3] = { false };
   do
   {
      readret = i.readFieldTypeAndID( type, fieldNumber );
    if ( !readret )
      break;
    switch ( fieldNumber )
    {
        case 1:
    {
     initFlags[1] = i.readString( key );
     break;
    }

    case 2:
    {
      uint64_t temp = 0;
      initFlags[2] = i.readVariantUInt64( temp );
      value = temp;
      break;
    }

    default:
    {
      // TODO: what?
      break;
    }
    }
   }
   while ( 1 ); // TODO: stop criterion (except the end of the message?
   
   ok = initFlags[1] && initFlags[2];
   if(ok)
     s.enumValues[key] = value;
  }
  initFlags[16] = ok;
      break;
    }
		default:
		{
			// TODO: what?
			break;
		}
	  }
   }
   while ( 1 ); // TODO: stop criterion (except the end of the message?

   bool OK = true;
   for ( int i=0; i<memcnt; i++ )
     OK = OK && initFlags[i] != 0;

   return OK;
}

bool deserializeEncodingSpecifics( EncodingSpecifics& s, IProtobufStream& i ) {
   int type;
   int fieldNumber;
   bool readret;
   const int memcnt = 2;
   uint8_t initFlags[memcnt] = { 0 };
  initFlags[1] = true;
   do
   {
      readret = i.readFieldTypeAndID( type, fieldNumber );
	  if ( !readret )
		  break;
	  switch ( fieldNumber )
	  {
    case 1:
    {
     initFlags[0] = i.readString( s.name );
      break;
    }
    case 2:
    {
  bool ok = false;
  {
    uint64_t sz_1 = 0;
    i.readVariantUInt64(sz_1);
    IProtobufStream is_1 = i.makeSubStream(sz_1);
    IProtobufStream& i = is_1;
    string key;
    Variant value;
    bool initFlags[3] = { false };
   do
   {
      readret = i.readFieldTypeAndID( type, fieldNumber );
    if ( !readret )
      break;
    switch ( fieldNumber )
    {
        case 1:
    {
     initFlags[1] = i.readString( key );
     break;
    }

    case 2:
    {
    uint64_t sz_2 = 0;
    i.readVariantUInt64(sz_2);
    IProtobufStream is_2 = i.makeSubStream(sz_2);
    initFlags[2] = deserializeVariant(value, is_2);
      break;
    }

    default:
    {
      // TODO: what?
      break;
    }
    }
   }
   while ( 1 ); // TODO: stop criterion (except the end of the message?
   
   ok = initFlags[1] && initFlags[2];
   if(ok)
     s.attrs[key] = value;
  }
  initFlags[1] = ok;
      break;
    }
		default:
		{
			// TODO: what?
			break;
		}
	  }
   }
   while ( 1 ); // TODO: stop criterion (except the end of the message?

   bool OK = true;
   for ( int i=0; i<memcnt; i++ )
     OK = OK && initFlags[i] != 0;

   return OK;
}

bool deserializeEncodedOrMember( EncodedOrMember& s, IProtobufStream& i ) {
   int type;
   int fieldNumber;
   bool readret;
   const int memcnt = 1;
   uint8_t initFlags[memcnt] = { 0 };
   do
   {
      readret = i.readFieldTypeAndID( type, fieldNumber );
	  if ( !readret )
		  break;
	  switch ( fieldNumber )
	  {
    case 1:
    {
    uint64_t sz_0 = 0;
    i.readVariantUInt64(sz_0);
    IProtobufStream is_0 = i.makeSubStream(sz_0);
    initFlags[0] = deserializeLocation(s.location, is_0);
      break;
    }
		default:
		{
			// TODO: what?
			break;
		}
	  }
   }
   while ( 1 ); // TODO: stop criterion (except the end of the message?

   bool OK = true;
   for ( int i=0; i<memcnt; i++ )
     OK = OK && initFlags[i] != 0;

   return OK;
}

bool deserializeDataMember( DataMember& s, IProtobufStream& i ) {
   int type;
   int fieldNumber;
   bool readret;
   const int memcnt = 6;
   uint8_t initFlags[memcnt] = { 0 };
  initFlags[4] = true;
   do
   {
      readret = i.readFieldTypeAndID( type, fieldNumber );
	  if ( !readret )
		  break;
	  switch ( fieldNumber )
	  {
    case 1:
    {
    uint64_t sz_0 = 0;
    i.readVariantUInt64(sz_0);
    IProtobufStream is_0 = i.makeSubStream(sz_0);
    initFlags[0] = deserializeDataType(s.type, is_0);
      break;
    }
    case 2:
    {
     initFlags[1] = i.readString( s.name );
      break;
    }
    case 3:
    {
      uint64_t temp = 0;
      initFlags[2] = i.readVariantUInt64( temp );
      s.extendTo = static_cast<bool>( temp );
      break;
    }
    case 4:
    {
    uint64_t sz_3 = 0;
    i.readVariantUInt64(sz_3);
    IProtobufStream is_3 = i.makeSubStream(sz_3);
    initFlags[3] = deserializeVariant(s.defaultValue, is_3);
      break;
    }
    case 5:
    {
      string temp2;
     initFlags[4] = i.readString( temp2 );
      s.whenDiscriminant.push_back(std::move(temp2));

      break;
    }
    case 6:
    {
    uint64_t sz_5 = 0;
    i.readVariantUInt64(sz_5);
    IProtobufStream is_5 = i.makeSubStream(sz_5);
    initFlags[5] = deserializeEncodedOrMember(s, is_5);
      break;
    }
		default:
		{
			// TODO: what?
			break;
		}
	  }
   }
   while ( 1 ); // TODO: stop criterion (except the end of the message?

   bool OK = true;
   for ( int i=0; i<memcnt; i++ )
     OK = OK && initFlags[i] != 0;

   return OK;
}

bool deserializeEncodedMembers( EncodedMembers& s, IProtobufStream& i ) {
   int type;
   int fieldNumber;
   bool readret;
   const int memcnt = 3;
   uint8_t initFlags[memcnt] = { 0 };
  initFlags[1] = true;
   do
   {
      readret = i.readFieldTypeAndID( type, fieldNumber );
	  if ( !readret )
		  break;
	  switch ( fieldNumber )
	  {
    case 1:
    {
    uint64_t sz_0 = 0;
    i.readVariantUInt64(sz_0);
    IProtobufStream is_0 = i.makeSubStream(sz_0);
    initFlags[0] = deserializeEncodingSpecifics(s.encodingSpecifics, is_0);
      break;
    }
    case 2:
    {
      unique_ptr<EncodedOrMember> temp2;
    uint64_t sz_1 = 0;
    i.readVariantUInt64(sz_1);
    IProtobufStream is_1 = i.makeSubStream(sz_1);
    initFlags[1] = deserialize__unique_ptr_EncodedOrMember(temp2, is_1);
      s.members.push_back(std::move(temp2));

      break;
    }
    case 3:
    {
    uint64_t sz_2 = 0;
    i.readVariantUInt64(sz_2);
    IProtobufStream is_2 = i.makeSubStream(sz_2);
    initFlags[2] = deserializeEncodedOrMember(s, is_2);
      break;
    }
		default:
		{
			// TODO: what?
			break;
		}
	  }
   }
   while ( 1 ); // TODO: stop criterion (except the end of the message?

   bool OK = true;
   for ( int i=0; i<memcnt; i++ )
     OK = OK && initFlags[i] != 0;

   return OK;
}

bool deserializeStructure( Structure& s, IProtobufStream& i ) {
   int type;
   int fieldNumber;
   bool readret;
   const int memcnt = 6;
   uint8_t initFlags[memcnt] = { 0 };
   do
   {
      readret = i.readFieldTypeAndID( type, fieldNumber );
	  if ( !readret )
		  break;
	  switch ( fieldNumber )
	  {
    case 1:
    {
   {
       uint64_t temp = 0;
       initFlags[0] = i.readVariantUInt64( temp );
       switch ( temp )
       {
	      case 0: s.declType = s.ENCODING; break;
	      case 1: s.declType = s.IDL; break;
	      case 2: s.declType = s.MAPPING; break;
          default: assert(0);
       }
   }
      break;
    }
    case 2:
    {
   {
       uint64_t temp = 0;
       initFlags[1] = i.readVariantUInt64( temp );
       switch ( temp )
       {
	      case 0: s.type = s.DISCRIMINATED_UNION; break;
	      case 1: s.type = s.RPC; break;
	      case 2: s.type = s.STRUCT; break;
          default: assert(0);
       }
   }
      break;
    }
    case 3:
    {
     initFlags[2] = i.readString( s.name );
      break;
    }
    case 4:
    {
     initFlags[3] = i.readString( s.discriminant );
      break;
    }
    case 5:
    {
     initFlags[4] = i.readString( s.inheritedFrom );
      break;
    }
    case 6:
    {
    uint64_t sz_5 = 0;
    i.readVariantUInt64(sz_5);
    IProtobufStream is_5 = i.makeSubStream(sz_5);
    initFlags[5] = deserializeEncodedMembers(s, is_5);
      break;
    }
		default:
		{
			// TODO: what?
			break;
		}
	  }
   }
   while ( 1 ); // TODO: stop criterion (except the end of the message?

   bool OK = true;
   for ( int i=0; i<memcnt; i++ )
     OK = OK && initFlags[i] != 0;

   return OK;
}

bool deserializeTypedef( Typedef& s, IProtobufStream& i ) {
   int type;
   int fieldNumber;
   bool readret;
   const int memcnt = 3;
   uint8_t initFlags[memcnt] = { 0 };
   do
   {
      readret = i.readFieldTypeAndID( type, fieldNumber );
	  if ( !readret )
		  break;
	  switch ( fieldNumber )
	  {
    case 1:
    {
    uint64_t sz_0 = 0;
    i.readVariantUInt64(sz_0);
    IProtobufStream is_0 = i.makeSubStream(sz_0);
    initFlags[0] = deserializeLocation(s.location, is_0);
      break;
    }
    case 2:
    {
    uint64_t sz_1 = 0;
    i.readVariantUInt64(sz_1);
    IProtobufStream is_1 = i.makeSubStream(sz_1);
    initFlags[1] = deserializeDataType(s.type, is_1);
      break;
    }
    case 3:
    {
     initFlags[2] = i.readString( s.name );
      break;
    }
		default:
		{
			// TODO: what?
			break;
		}
	  }
   }
   while ( 1 ); // TODO: stop criterion (except the end of the message?

   bool OK = true;
   for ( int i=0; i<memcnt; i++ )
     OK = OK && initFlags[i] != 0;

   return OK;
}

bool deserializeRoot( Root& s, IProtobufStream& i ) {
   int type;
   int fieldNumber;
   bool readret;
   const int memcnt = 2;
   uint8_t initFlags[memcnt] = { 0 };
  initFlags[0] = true;
  initFlags[1] = true;
   do
   {
      readret = i.readFieldTypeAndID( type, fieldNumber );
	  if ( !readret )
		  break;
	  switch ( fieldNumber )
	  {
    case 1:
    {
      Typedef temp2;
    uint64_t sz_0 = 0;
    i.readVariantUInt64(sz_0);
    IProtobufStream is_0 = i.makeSubStream(sz_0);
    initFlags[0] = deserializeTypedef(temp2, is_0);
      s.typedefs.push_back(std::move(temp2));

      break;
    }
    case 2:
    {
      unique_ptr<Structure> temp2;
    uint64_t sz_1 = 0;
    i.readVariantUInt64(sz_1);
    IProtobufStream is_1 = i.makeSubStream(sz_1);
    initFlags[1] = deserialize__unique_ptr_Structure(temp2, is_1);
      s.structures.push_back(std::move(temp2));

      break;
    }
		default:
		{
			// TODO: what?
			break;
		}
	  }
   }
   while ( 1 ); // TODO: stop criterion (except the end of the message?

   bool OK = true;
   for ( int i=0; i<memcnt; i++ )
     OK = OK && initFlags[i] != 0;

   return OK;
}


bool deserialize__unique_ptr_DataType( unique_ptr<DataType>& s, IProtobufStream& i ) {
   int type;
   int fieldNumber;
   bool readret;
   const int memcnt = 2;
   uint8_t initFlags[memcnt] = { 0 };
   do
   {
      readret = i.readFieldTypeAndID( type, fieldNumber );
    if ( !readret )
      break;
    switch ( fieldNumber )
    {
       case 1:
       {
       //else if ( typeid( *s ) == typeid( DataType ) ) 
         unique_ptr<DataType> ptr(new DataType);
    uint64_t sz_1 = 0;
    i.readVariantUInt64(sz_1);
    IProtobufStream is_1 = i.makeSubStream(sz_1);
    initFlags[1] = deserializeDataType(*ptr, is_1);
         s = move(ptr);
       }
       break;

    default:
    {
      // TODO: what?
      break;
    }
    }
   }
   while ( 1 ); // TODO: stop criterion (except the end of the message?

   bool OK = false;
   for ( int i=0; i<memcnt; i++ )
     OK = OK || initFlags[i] != 0;

   return true; //TODO
}
bool deserialize__unique_ptr_EncodedOrMember( unique_ptr<EncodedOrMember>& s, IProtobufStream& i ) {
   int type;
   int fieldNumber;
   bool readret;
   const int memcnt = 4;
   uint8_t initFlags[memcnt] = { 0 };
   do
   {
      readret = i.readFieldTypeAndID( type, fieldNumber );
    if ( !readret )
      break;
    switch ( fieldNumber )
    {
       case 1:
       {
       //else if ( typeid( *s ) == typeid( DataMember ) ) 
         unique_ptr<DataMember> ptr(new DataMember);
    uint64_t sz_1 = 0;
    i.readVariantUInt64(sz_1);
    IProtobufStream is_1 = i.makeSubStream(sz_1);
    initFlags[1] = deserializeDataMember(*ptr, is_1);
         s = move(ptr);
       }
       break;
       case 2:
       {
       //else if ( typeid( *s ) == typeid( EncodedMembers ) ) 
         unique_ptr<EncodedMembers> ptr(new EncodedMembers);
    uint64_t sz_2 = 0;
    i.readVariantUInt64(sz_2);
    IProtobufStream is_2 = i.makeSubStream(sz_2);
    initFlags[2] = deserializeEncodedMembers(*ptr, is_2);
         s = move(ptr);
       }
       break;
       case 3:
       {
       //else if ( typeid( *s ) == typeid( EncodedOrMember ) ) 
         unique_ptr<EncodedOrMember> ptr(new EncodedOrMember);
    uint64_t sz_3 = 0;
    i.readVariantUInt64(sz_3);
    IProtobufStream is_3 = i.makeSubStream(sz_3);
    initFlags[3] = deserializeEncodedOrMember(*ptr, is_3);
         s = move(ptr);
       }
       break;

    default:
    {
      // TODO: what?
      break;
    }
    }
   }
   while ( 1 ); // TODO: stop criterion (except the end of the message?

   bool OK = false;
   for ( int i=0; i<memcnt; i++ )
     OK = OK || initFlags[i] != 0;

   return true; //TODO
}
bool deserialize__unique_ptr_Structure( unique_ptr<Structure>& s, IProtobufStream& i ) {
   int type;
   int fieldNumber;
   bool readret;
   const int memcnt = 2;
   uint8_t initFlags[memcnt] = { 0 };
   do
   {
      readret = i.readFieldTypeAndID( type, fieldNumber );
    if ( !readret )
      break;
    switch ( fieldNumber )
    {
       case 1:
       {
       //else if ( typeid( *s ) == typeid( Structure ) ) 
         unique_ptr<Structure> ptr(new Structure);
    uint64_t sz_1 = 0;
    i.readVariantUInt64(sz_1);
    IProtobufStream is_1 = i.makeSubStream(sz_1);
    initFlags[1] = deserializeStructure(*ptr, is_1);
         s = move(ptr);
       }
       break;

    default:
    {
      // TODO: what?
      break;
    }
    }
   }
   while ( 1 ); // TODO: stop criterion (except the end of the message?

   bool OK = false;
   for ( int i=0; i<memcnt; i++ )
     OK = OK || initFlags[i] != 0;

   return true; //TODO
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
  size_t sz_1 = protobufGetSizeCharacterRange(item);
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
  size_t sz_5 = protobufGetSize__unique_ptr_DataType(s.keyType);
  sz += getUnsignedVarIntSize(sz_5);
  sz += sz_5;
      
  sz += getTagSize(6);
  size_t sz_6 = protobufGetSize__unique_ptr_DataType(s.paramType);
  sz += getUnsignedVarIntSize(sz_6);
  sz += sz_6;
      
  sz += getTagSize(7);
  size_t sz_7 = protobufGetSizeLimit(s.lowLimit);
  sz += getUnsignedVarIntSize(sz_7);
  sz += sz_7;
      
  sz += getTagSize(8);
  size_t sz_8 = protobufGetSizeLimit(s.highLimit);
  sz += getUnsignedVarIntSize(sz_8);
  sz += sz_8;
      
  sz += getTagSize(9);
  sz += getFixedSize(s.fixedPrecision);
      
  sz += getTagSize(10);
  sz += getUnsignedVarIntSize(s.floatingSignificandBits);
      
  sz += getTagSize(11);
  sz += getUnsignedVarIntSize(s.floatingExponentBits);
      
  sz += getTagSize(12);
  size_t sz_12 = protobufGetSizeCharacterSet(s.characterSet);
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
  size_t sz_2 = protobufGetSizeVariant(item.second);
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
  size_t sz_2 = protobufGetSizeVariant(item.second);
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
  size_t sz_2 = protobufGetSizeVariant(item.second);
  sz += getUnsignedVarIntSize(sz_2);
  sz += sz_2;
      sz += getUnsignedVarIntSize(sz - sz_begin_2);
    }
   
   return sz;
}

size_t protobufGetSizeEncodedOrMember( const EncodedOrMember& s ) {
   size_t sz = 0;
      
  sz += getTagSize(1);
  size_t sz_1 = protobufGetSizeLocation(s.location);
  sz += getUnsignedVarIntSize(sz_1);
  sz += sz_1;
   
   return sz;
}

size_t protobufGetSizeDataMember( const DataMember& s ) {
   size_t sz = 0;
      
  sz += getTagSize(1);
  size_t sz_1 = protobufGetSizeDataType(s.type);
  sz += getUnsignedVarIntSize(sz_1);
  sz += sz_1;
      
  sz += getTagSize(2);
  sz += getUnsignedVarIntSize(s.name.size());
  sz += s.name.size();
      
  sz += getTagSize(3);
  sz += getUnsignedVarIntSize(s.extendTo);
      
  sz += getTagSize(4);
  size_t sz_4 = protobufGetSizeVariant(s.defaultValue);
  sz += getUnsignedVarIntSize(sz_4);
  sz += sz_4;
      
    for(const auto& item:s.whenDiscriminant) {
  sz += getTagSize(5);
  sz += getUnsignedVarIntSize(item.size());
  sz += item.size();
    }
      
  sz += getTagSize(6);
  size_t sz_6 = protobufGetSizeEncodedOrMember(s);
  sz += getUnsignedVarIntSize(sz_6);
  sz += sz_6;
   
   return sz;
}

size_t protobufGetSizeEncodedMembers( const EncodedMembers& s ) {
   size_t sz = 0;
      
  sz += getTagSize(1);
  size_t sz_1 = protobufGetSizeEncodingSpecifics(s.encodingSpecifics);
  sz += getUnsignedVarIntSize(sz_1);
  sz += sz_1;
      
    for(const auto& item:s.members) {
  sz += getTagSize(2);
  size_t sz_2 = protobufGetSize__unique_ptr_EncodedOrMember(item);
  sz += getUnsignedVarIntSize(sz_2);
  sz += sz_2;
    }
      
  sz += getTagSize(3);
  size_t sz_3 = protobufGetSizeEncodedOrMember(s);
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
  size_t sz_6 = protobufGetSizeEncodedMembers(s);
  sz += getUnsignedVarIntSize(sz_6);
  sz += sz_6;
   
   return sz;
}

size_t protobufGetSizeTypedef( const Typedef& s ) {
   size_t sz = 0;
      
  sz += getTagSize(1);
  size_t sz_1 = protobufGetSizeLocation(s.location);
  sz += getUnsignedVarIntSize(sz_1);
  sz += sz_1;
      
  sz += getTagSize(2);
  size_t sz_2 = protobufGetSizeDataType(s.type);
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
  size_t sz_1 = protobufGetSizeTypedef(item);
  sz += getUnsignedVarIntSize(sz_1);
  sz += sz_1;
    }
      
    for(const auto& item:s.structures) {
  sz += getTagSize(2);
  size_t sz_2 = protobufGetSize__unique_ptr_Structure(item);
  sz += getUnsignedVarIntSize(sz_2);
  sz += sz_2;
    }
   
   return sz;
}


size_t protobufGetSize__unique_ptr_DataType( const unique_ptr<DataType>& s ) {
  

     size_t sz = 0;
  if(s.get() == nullptr) {
    return sz;
  }
       else if ( typeid( *s ) == typeid( DataType ) ) {
         auto ptr = dynamic_cast<DataType*>(s.get());
  sz += getTagSize(1);
  size_t sz_1 = protobufGetSizeDataType(*ptr);
  sz += getUnsignedVarIntSize(sz_1);
  sz += sz_1;

       }
   else {
     ;// TODO assert?
   }
   return sz;
}
size_t protobufGetSize__unique_ptr_EncodedOrMember( const unique_ptr<EncodedOrMember>& s ) {
  

     size_t sz = 0;
  if(s.get() == nullptr) {
    return sz;
  }
       else if ( typeid( *s ) == typeid( DataMember ) ) {
         auto ptr = dynamic_cast<DataMember*>(s.get());
  sz += getTagSize(1);
  size_t sz_1 = protobufGetSizeDataMember(*ptr);
  sz += getUnsignedVarIntSize(sz_1);
  sz += sz_1;

       }
       else if ( typeid( *s ) == typeid( EncodedMembers ) ) {
         auto ptr = dynamic_cast<EncodedMembers*>(s.get());
  sz += getTagSize(2);
  size_t sz_2 = protobufGetSizeEncodedMembers(*ptr);
  sz += getUnsignedVarIntSize(sz_2);
  sz += sz_2;

       }
       else if ( typeid( *s ) == typeid( EncodedOrMember ) ) {
         auto ptr = dynamic_cast<EncodedOrMember*>(s.get());
  sz += getTagSize(3);
  size_t sz_3 = protobufGetSizeEncodedOrMember(*ptr);
  sz += getUnsignedVarIntSize(sz_3);
  sz += sz_3;

       }
   else {
     ;// TODO assert?
   }
   return sz;
}
size_t protobufGetSize__unique_ptr_Structure( const unique_ptr<Structure>& s ) {
  

     size_t sz = 0;
  if(s.get() == nullptr) {
    return sz;
  }
       else if ( typeid( *s ) == typeid( Structure ) ) {
         auto ptr = dynamic_cast<Structure*>(s.get());
  sz += getTagSize(1);
  size_t sz_1 = protobufGetSizeStructure(*ptr);
  sz += getUnsignedVarIntSize(sz_1);
  sz += sz_1;

       }
   else {
     ;// TODO assert?
   }
   return sz;
}


