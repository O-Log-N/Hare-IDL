
#ifndef OUTPUT_H_INCLUDED
#define OUTPUT_H_INCLUDED

#include "front-back/idl_tree.h"

class OProtobufStream;
class IProtobufStream;

// DECLARATIONS

// objects

//  INCLUDE TEMPLATE="FORWARD-DECLARING" PARAM-ROOT=PARAM-ROOT

//  INCLUDE TEMPLATE="SMART-DECLARING-ENTRY" PARAM-ROOT=PARAM-ROOT
  
// functions
    
// serialization
void serializeLimit( const Limit& s, OProtobufStream& o );
void serializeLocation( const Location& s, OProtobufStream& o );
void serializeCharacterRange( const CharacterRange& s, OProtobufStream& o );
void serializeCharacterSet( const CharacterSet& s, OProtobufStream& o );
void serializeVariant( const Variant& s, OProtobufStream& o );
void serializeDataType( const DataType& s, OProtobufStream& o );
void serializeEncodingSpecifics( const EncodingSpecifics& s, OProtobufStream& o );
void serializeEncodedOrMember( const EncodedOrMember& s, OProtobufStream& o );
void serializeDataMember( const DataMember& s, OProtobufStream& o );
void serializeEncodedMembers( const EncodedMembers& s, OProtobufStream& o );
void serializeStructure( const Structure& s, OProtobufStream& o );
void serializeTypedef( const Typedef& s, OProtobufStream& o );
void serializeRoot( const Root& s, OProtobufStream& o );
void serialize__unique_ptr_DataType( const unique_ptr<DataType>& s, OProtobufStream& o );
void serialize__unique_ptr_EncodedOrMember( const unique_ptr<EncodedOrMember>& s, OProtobufStream& o );
void serialize__unique_ptr_Structure( const unique_ptr<Structure>& s, OProtobufStream& o );
// deserialization
bool deserializeLimit( Limit& s, IProtobufStream& i );
bool deserializeLocation( Location& s, IProtobufStream& i );
bool deserializeCharacterRange( CharacterRange& s, IProtobufStream& i );
bool deserializeCharacterSet( CharacterSet& s, IProtobufStream& i );
bool deserializeVariant( Variant& s, IProtobufStream& i );
bool deserializeDataType( DataType& s, IProtobufStream& i );
bool deserializeEncodingSpecifics( EncodingSpecifics& s, IProtobufStream& i );
bool deserializeEncodedOrMember( EncodedOrMember& s, IProtobufStream& i );
bool deserializeDataMember( DataMember& s, IProtobufStream& i );
bool deserializeEncodedMembers( EncodedMembers& s, IProtobufStream& i );
bool deserializeStructure( Structure& s, IProtobufStream& i );
bool deserializeTypedef( Typedef& s, IProtobufStream& i );
bool deserializeRoot( Root& s, IProtobufStream& i );
bool deserialize__unique_ptr_DataType( unique_ptr<DataType>& s, IProtobufStream& i );
bool deserialize__unique_ptr_EncodedOrMember( unique_ptr<EncodedOrMember>& s, IProtobufStream& i );
bool deserialize__unique_ptr_Structure( unique_ptr<Structure>& s, IProtobufStream& i );
// printing
//  INCLUDE TEMPLATE="PRINTING-GENERATE-DECLARATIONS" PARAM-ROOT=PARAM-ROOT
// GET-SIZE
size_t protobufGetSizeLimit( const Limit& s );
size_t protobufGetSizeLocation( const Location& s );
size_t protobufGetSizeCharacterRange( const CharacterRange& s );
size_t protobufGetSizeCharacterSet( const CharacterSet& s );
size_t protobufGetSizeVariant( const Variant& s );
size_t protobufGetSizeDataType( const DataType& s );
size_t protobufGetSizeEncodingSpecifics( const EncodingSpecifics& s );
size_t protobufGetSizeEncodedOrMember( const EncodedOrMember& s );
size_t protobufGetSizeDataMember( const DataMember& s );
size_t protobufGetSizeEncodedMembers( const EncodedMembers& s );
size_t protobufGetSizeStructure( const Structure& s );
size_t protobufGetSizeTypedef( const Typedef& s );
size_t protobufGetSizeRoot( const Root& s );
size_t protobufGetSize__unique_ptr_DataType( const unique_ptr<DataType>& s );
size_t protobufGetSize__unique_ptr_EncodedOrMember( const unique_ptr<EncodedOrMember>& s );
size_t protobufGetSize__unique_ptr_Structure( const unique_ptr<Structure>& s );

#endif // OUTPUT_H_INCLUDED

