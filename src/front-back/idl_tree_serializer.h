#ifndef IDL_TREE_SERIALIZER_H
#define IDL_TREE_SERIALIZER_H

#include "idl_tree.h"
#include "../targets/sample/include/simple_lib.h"

// functions
    
// serialization
void serializeCharacterRange( CharacterRange& s, OStream& o );
void serializeCharacterSet( CharacterSet& s, OStream& o );
void serializeVariant( Variant& s, OStream& o );
void serializeLimit( Limit& s, OStream& o );
void serializeLocation( Location& s, OStream& o );
void serializeDataType( DataType& s, OStream& o );
void serializeEncodingSpecifics( EncodingSpecifics& s, OStream& o );
void serializeEncodedOrMember( EncodedOrMember& s, OStream& o );
void serializeDataMember( DataMember& s, OStream& o );
void serializeEncodedMembers( EncodedMembers& s, OStream& o );
void serializeStructure( Structure& s, OStream& o );
void serializeTypedef( Typedef& s, OStream& o );
void serializeRoot( Root& s, OStream& o );
void serialize__unique_ptr_DataType( unique_ptr<DataType>& s, OStream& o );
void serialize__unique_ptr_EncodedOrMember( unique_ptr<EncodedOrMember>& s, OStream& o );
void serialize__unique_ptr_Structure( unique_ptr<Structure>& s, OStream& o );
// deserialization
bool deserializeCharacterRange( CharacterRange& s, IStream& i );
bool deserializeCharacterSet( CharacterSet& s, IStream& i );
bool deserializeVariant( Variant& s, IStream& i );
bool deserializeLimit( Limit& s, IStream& i );
bool deserializeLocation( Location& s, IStream& i );
bool deserializeDataType( DataType& s, IStream& i );
bool deserializeEncodingSpecifics( EncodingSpecifics& s, IStream& i );
bool deserializeEncodedOrMember( EncodedOrMember& s, IStream& i );
bool deserializeDataMember( DataMember& s, IStream& i );
bool deserializeEncodedMembers( EncodedMembers& s, IStream& i );
bool deserializeStructure( Structure& s, IStream& i );
bool deserializeTypedef( Typedef& s, IStream& i );
bool deserializeRoot( Root& s, IStream& i );
bool deserialize__unique_ptr_DataType( unique_ptr<DataType>& s, IStream& i );
bool deserialize__unique_ptr_EncodedOrMember( unique_ptr<EncodedOrMember>& s, IStream& i );
bool deserialize__unique_ptr_Structure( unique_ptr<Structure>& s, IStream& i );
// printing
void printCharacterRange( CharacterRange& s );
void printCharacterSet( CharacterSet& s );
void printVariant( Variant& s );
void printLimit( Limit& s );
void printLocation( Location& s );
void printDataType( DataType& s );
void printEncodingSpecifics( EncodingSpecifics& s );
void printEncodedOrMember( EncodedOrMember& s );
void printDataMember( DataMember& s );
void printEncodedMembers( EncodedMembers& s );
void printStructure( Structure& s );
void printTypedef( Typedef& s );
void printRoot( Root& s );
void print__unique_ptr_DataType( unique_ptr<DataType>& s );
void print__unique_ptr_EncodedOrMember( unique_ptr<EncodedOrMember>& s );
void print__unique_ptr_Structure( unique_ptr<Structure>& s );

#endif // IDL_TREE_SERIALIZER_H