
#ifndef DBG_PRINT_H_INCLUDED
#define DBG_PRINT_H_INCLUDED

#include <ostream>

// PRINT
void dbgPrintLimit( const Limit& s, std::ostream& o, size_t offset );
void dbgPrintLocation( const Location& s, std::ostream& o, size_t offset );
void dbgPrintCharacterRange( const CharacterRange& s, std::ostream& o, size_t offset );
void dbgPrintCharacterSet( const CharacterSet& s, std::ostream& o, size_t offset );
void dbgPrintVariant( const Variant& s, std::ostream& o, size_t offset );
void dbgPrintDataType( const DataType& s, std::ostream& o, size_t offset );
void dbgPrintEncodingSpecifics( const EncodingSpecifics& s, std::ostream& o, size_t offset );
void dbgPrintEncodedOrMember( const EncodedOrMember& s, std::ostream& o, size_t offset );
void dbgPrintDataMember( const DataMember& s, std::ostream& o, size_t offset );
void dbgPrintEncodedMembers( const EncodedMembers& s, std::ostream& o, size_t offset );
void dbgPrintStructure( const Structure& s, std::ostream& o, size_t offset );
void dbgPrintTypedef( const Typedef& s, std::ostream& o, size_t offset );
void dbgPrintRoot( const Root& s, std::ostream& o, size_t offset );
void dbgPrint__unique_ptr_DataType( const unique_ptr<DataType>& s, std::ostream& o, size_t offset );
void dbgPrint__unique_ptr_EncodedOrMember( const unique_ptr<EncodedOrMember>& s, std::ostream& o, size_t offset );
void dbgPrint__unique_ptr_Structure( const unique_ptr<Structure>& s, std::ostream& o, size_t offset );

void dbgPrintLimit( const Limit& s, std::ostream& o, size_t offset ) {

  std::string sp( 2 * offset, ' ' );
  std::string sp1( 2 * offset + 2, ' ');

  o << "PUBLISHABLE-STRUCT Limit:\n";

    o << sp << "inclusive = ";
  o << s.inclusive << "\n";
    o << sp << "value = ";
  o << s.value << "\n";
}
void dbgPrintLocation( const Location& s, std::ostream& o, size_t offset ) {

  std::string sp( 2 * offset, ' ' );
  std::string sp1( 2 * offset + 2, ' ');

  o << "PUBLISHABLE-STRUCT Location:\n";

    o << sp << "fileName = ";
  o << "\"" << s.fileName << "\"\n";
    o << sp << "lineNumber = ";
  o << s.lineNumber << "\n";
}
void dbgPrintCharacterRange( const CharacterRange& s, std::ostream& o, size_t offset ) {

  std::string sp( 2 * offset, ' ' );
  std::string sp1( 2 * offset + 2, ' ');

  o << "PUBLISHABLE-STRUCT CharacterRange:\n";

    o << sp << "from = ";
  o << s.from << "\n";
    o << sp << "to = ";
  o << s.to << "\n";
}
void dbgPrintCharacterSet( const CharacterSet& s, std::ostream& o, size_t offset ) {

  std::string sp( 2 * offset, ' ' );
  std::string sp1( 2 * offset + 2, ' ');

  o << "PUBLISHABLE-STRUCT CharacterSet:\n";

    o << sp << "ranges = ";
  o << "SEQUENCE\n";
    for(const auto& item:s.ranges) {
      o << sp1;
    dbgPrintCharacterRange(item, o, offset + 1);
    }
}
void dbgPrintVariant( const Variant& s, std::ostream& o, size_t offset ) {

  std::string sp( 2 * offset, ' ' );
  std::string sp1( 2 * offset + 2, ' ');

  o << "PUBLISHABLE-STRUCT Variant:\n";

    o << sp << "kind = ";
  o << s.kind << "\n";
    o << sp << "numberValue = ";
  o << s.numberValue << "\n";
    o << sp << "stringValue = ";
  o << "\"" << s.stringValue << "\"\n";
}
void dbgPrintDataType( const DataType& s, std::ostream& o, size_t offset ) {

  std::string sp( 2 * offset, ' ' );
  std::string sp1( 2 * offset + 2, ' ');

  o << "PUBLISHABLE-STRUCT DataType:\n";

    o << sp << "kind = ";
  o << s.kind << "\n";
    o << sp << "name = ";
  o << "\"" << s.name << "\"\n";
    o << sp << "mappingName = ";
  o << "\"" << s.mappingName << "\"\n";
    o << sp << "encodingName = ";
  o << "\"" << s.encodingName << "\"\n";
    o << sp << "keyType = ";
    dbgPrint__unique_ptr_DataType(s.keyType, o, offset + 1);
    o << sp << "paramType = ";
    dbgPrint__unique_ptr_DataType(s.paramType, o, offset + 1);
    o << sp << "lowLimit = ";
    dbgPrintLimit(s.lowLimit, o, offset + 1);
    o << sp << "highLimit = ";
    dbgPrintLimit(s.highLimit, o, offset + 1);
    o << sp << "fixedPrecision = ";
  o << s.fixedPrecision << "\n";
    o << sp << "floatingSignificandBits = ";
  o << s.floatingSignificandBits << "\n";
    o << sp << "floatingExponentBits = ";
  o << s.floatingExponentBits << "\n";
    o << sp << "characterSet = ";
    dbgPrintCharacterSet(s.characterSet, o, offset + 1);
    o << sp << "stringMinSize = ";
  o << s.stringMinSize << "\n";
    o << sp << "stringMaxSize = ";
  o << s.stringMaxSize << "\n";
    o << sp << "encodingAttrs = ";
  o << "DICTIONARY\n";
    for(const auto& item:s.encodingAttrs) {
      o << sp << "{\n"; 
      o << sp1;
  o << "\"" << item.first << "\"\n";
      o << sp1;
    dbgPrintVariant(item.second, o, offset + 1);
      o << sp << "}\n";
    }
    o << sp << "mappingAttrs = ";
  o << "DICTIONARY\n";
    for(const auto& item:s.mappingAttrs) {
      o << sp << "{\n"; 
      o << sp1;
  o << "\"" << item.first << "\"\n";
      o << sp1;
    dbgPrintVariant(item.second, o, offset + 1);
      o << sp << "}\n";
    }
    o << sp << "enumValues = ";
  o << "DICTIONARY\n";
    for(const auto& item:s.enumValues) {
      o << sp << "{\n"; 
      o << sp1;
  o << "\"" << item.first << "\"\n";
      o << sp1;
  o << item.second << "\n";
      o << sp << "}\n";
    }
}
void dbgPrintEncodingSpecifics( const EncodingSpecifics& s, std::ostream& o, size_t offset ) {

  std::string sp( 2 * offset, ' ' );
  std::string sp1( 2 * offset + 2, ' ');

  o << "PUBLISHABLE-STRUCT EncodingSpecifics:\n";

    o << sp << "name = ";
  o << "\"" << s.name << "\"\n";
    o << sp << "attrs = ";
  o << "DICTIONARY\n";
    for(const auto& item:s.attrs) {
      o << sp << "{\n"; 
      o << sp1;
  o << "\"" << item.first << "\"\n";
      o << sp1;
    dbgPrintVariant(item.second, o, offset + 1);
      o << sp << "}\n";
    }
}
void dbgPrintEncodedOrMember( const EncodedOrMember& s, std::ostream& o, size_t offset ) {

  std::string sp( 2 * offset, ' ' );
  std::string sp1( 2 * offset + 2, ' ');

  o << "PUBLISHABLE-STRUCT EncodedOrMember:\n";

    o << sp << "location = ";
    dbgPrintLocation(s.location, o, offset + 1);
}
void dbgPrintDataMember( const DataMember& s, std::ostream& o, size_t offset ) {

  std::string sp( 2 * offset, ' ' );
  std::string sp1( 2 * offset + 2, ' ');

  o << "PUBLISHABLE-STRUCT DataMember:\n";

    o << sp << "type = ";
    dbgPrintDataType(s.type, o, offset + 1);
    o << sp << "name = ";
  o << "\"" << s.name << "\"\n";
    o << sp << "extendTo = ";
  o << s.extendTo << "\n";
    o << sp << "defaultValue = ";
    dbgPrintVariant(s.defaultValue, o, offset + 1);
    o << sp << "whenDiscriminant = ";
  o << "SEQUENCE\n";
    for(const auto& item:s.whenDiscriminant) {
      o << sp1;
  o << "\"" << item << "\"\n";
    }
    o << sp << "__parent = ";
    dbgPrintEncodedOrMember(s, o, offset + 1);
}
void dbgPrintEncodedMembers( const EncodedMembers& s, std::ostream& o, size_t offset ) {

  std::string sp( 2 * offset, ' ' );
  std::string sp1( 2 * offset + 2, ' ');

  o << "PUBLISHABLE-STRUCT EncodedMembers:\n";

    o << sp << "encodingSpecifics = ";
    dbgPrintEncodingSpecifics(s.encodingSpecifics, o, offset + 1);
    o << sp << "members = ";
  o << "SEQUENCE\n";
    for(const auto& item:s.members) {
      o << sp1;
    dbgPrint__unique_ptr_EncodedOrMember(item, o, offset + 1);
    }
    o << sp << "__parent = ";
    dbgPrintEncodedOrMember(s, o, offset + 1);
}
void dbgPrintStructure( const Structure& s, std::ostream& o, size_t offset ) {

  std::string sp( 2 * offset, ' ' );
  std::string sp1( 2 * offset + 2, ' ');

  o << "PUBLISHABLE-STRUCT Structure:\n";

    o << sp << "declType = ";
  o << s.declType << "\n";
    o << sp << "type = ";
  o << s.type << "\n";
    o << sp << "name = ";
  o << "\"" << s.name << "\"\n";
    o << sp << "discriminant = ";
  o << "\"" << s.discriminant << "\"\n";
    o << sp << "inheritedFrom = ";
  o << "\"" << s.inheritedFrom << "\"\n";
    o << sp << "__parent = ";
    dbgPrintEncodedMembers(s, o, offset + 1);
}
void dbgPrintTypedef( const Typedef& s, std::ostream& o, size_t offset ) {

  std::string sp( 2 * offset, ' ' );
  std::string sp1( 2 * offset + 2, ' ');

  o << "PUBLISHABLE-STRUCT Typedef:\n";

    o << sp << "location = ";
    dbgPrintLocation(s.location, o, offset + 1);
    o << sp << "type = ";
    dbgPrintDataType(s.type, o, offset + 1);
    o << sp << "name = ";
  o << "\"" << s.name << "\"\n";
}
void dbgPrintRoot( const Root& s, std::ostream& o, size_t offset ) {

  std::string sp( 2 * offset, ' ' );
  std::string sp1( 2 * offset + 2, ' ');

  o << "PUBLISHABLE-STRUCT Root:\n";

    o << sp << "typedefs = ";
  o << "SEQUENCE\n";
    for(const auto& item:s.typedefs) {
      o << sp1;
    dbgPrintTypedef(item, o, offset + 1);
    }
    o << sp << "structures = ";
  o << "SEQUENCE\n";
    for(const auto& item:s.structures) {
      o << sp1;
    dbgPrint__unique_ptr_Structure(item, o, offset + 1);
    }
}

void dbgPrint__unique_ptr_DataType( const unique_ptr<DataType>& s, std::ostream& o, size_t offset ) {

  std::string sp( 2 * offset, ' ' );
  std::string sp1( 2 * offset + 2, ' ');

//  o << "DISCRIMINATED-UNION __unique_ptr_DataType:\n";

  if( s == nullptr )
    o << sp << "<nullptr>\n";
      else if ( typeid( *s ) == typeid( DataType ) ) {
        auto ptr = dynamic_cast<DataType*>( s.get() );
        dbgPrintDataType( *ptr, o, offset + 1 );
      }
  else
    assert( false );
}
void dbgPrint__unique_ptr_EncodedOrMember( const unique_ptr<EncodedOrMember>& s, std::ostream& o, size_t offset ) {

  std::string sp( 2 * offset, ' ' );
  std::string sp1( 2 * offset + 2, ' ');

//  o << "DISCRIMINATED-UNION __unique_ptr_EncodedOrMember:\n";

  if( s == nullptr )
    o << sp << "<nullptr>\n";
      else if ( typeid( *s ) == typeid( DataMember ) ) {
        auto ptr = dynamic_cast<DataMember*>( s.get() );
        dbgPrintDataMember( *ptr, o, offset + 1 );
      }
      else if ( typeid( *s ) == typeid( EncodedMembers ) ) {
        auto ptr = dynamic_cast<EncodedMembers*>( s.get() );
        dbgPrintEncodedMembers( *ptr, o, offset + 1 );
      }
      else if ( typeid( *s ) == typeid( EncodedOrMember ) ) {
        auto ptr = dynamic_cast<EncodedOrMember*>( s.get() );
        dbgPrintEncodedOrMember( *ptr, o, offset + 1 );
      }
  else
    assert( false );
}
void dbgPrint__unique_ptr_Structure( const unique_ptr<Structure>& s, std::ostream& o, size_t offset ) {

  std::string sp( 2 * offset, ' ' );
  std::string sp1( 2 * offset + 2, ' ');

//  o << "DISCRIMINATED-UNION __unique_ptr_Structure:\n";

  if( s == nullptr )
    o << sp << "<nullptr>\n";
      else if ( typeid( *s ) == typeid( Structure ) ) {
        auto ptr = dynamic_cast<Structure*>( s.get() );
        dbgPrintStructure( *ptr, o, offset + 1 );
      }
  else
    assert( false );
}

#endif // DBG_PRINT_H_INCLUDED
  
