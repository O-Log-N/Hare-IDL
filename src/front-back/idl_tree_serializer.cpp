#include "idl_tree_serializer.h"

// IMPLEMENTATIONS

// SERIALIZATION

void serializeLimit( Limit& s, OStream& o ) {
   o.write_uint8_t(s.inclusive);
   o.write_double(s.value);
}

void serializeLocation( Location& s, OStream& o ) {
   o.write_string(s.fileName);
   o.write_uint16_t(s.lineNumber);
}

void serializeCharacterRange( CharacterRange& s, OStream& o ) {
   o.write_uint32_t(s.from);
   o.write_uint32_t(s.to);
}

void serializeCharacterSet( CharacterSet& s, OStream& o ) {
   {
   o.write_uint32_t( 
        s.ranges.size() 
     );
   for(
        auto& it_1 = s.ranges.begin() 
         ; !(
        it_1 == s.ranges.end() 
         );
        ++it_1 
         )
   {
        auto& obj_1 = *it_1;
   serializeCharacterRange(obj_1, o);
   }
   }
}

void serializeVariant( Variant& s, OStream& o ) {
      switch ( s.kind )
	  {
        case 0 /*NONE*/: o.write_uint8_t( 0 ); break;
        case 1 /*NUMBER*/: o.write_uint8_t( 1 ); break;
        case 2 /*STRING*/: o.write_uint8_t( 2 ); break;
        default: assert( 0 );
	  }
   o.write_double(s.numberValue);
   o.write_string(s.stringValue);
}

void serializeDataType( DataType& s, OStream& o ) {
      switch ( s.kind )
	  {
        case 10 /*BIT_STRING*/: o.write_uint8_t( 0 ); break;
        case 9 /*CHARACTER_STRING*/: o.write_uint8_t( 1 ); break;
        case 12 /*DISCRIMINATED_UNION*/: o.write_uint8_t( 2 ); break;
        case 3 /*ENCODING_SPECIFIC*/: o.write_uint8_t( 3 ); break;
        case 0 /*ENUM*/: o.write_uint8_t( 4 ); break;
        case 6 /*FIXED_POINT*/: o.write_uint8_t( 5 ); break;
        case 7 /*FLOATING_POINT*/: o.write_uint8_t( 6 ); break;
        case 4 /*MAPPING_SPECIFIC*/: o.write_uint8_t( 7 ); break;
        case 1 /*NAMED_TYPE*/: o.write_uint8_t( 8 ); break;
        case 8 /*CHARACTER*/: o.write_uint8_t( 9 ); break;
        case 11 /*DICTIONARY*/: o.write_uint8_t( 10 ); break;
        case 5 /*INTEGER*/: o.write_uint8_t( 11 ); break;
        case 2 /*SEQUENCE*/: o.write_uint8_t( 12 ); break;
        default: assert( 0 );
	  }
   o.write_string(s.name);
   o.write_string(s.mappingName);
   o.write_string(s.encodingName);
   {
   o.write_uint32_t( 
        (s.keyType != nullptr ? 1 : 0) 
     );
   for(
        auto it_1 = s.keyType != nullptr ? &s.keyType : nullptr
         ; !(
        it_1 == nullptr
         );
        it_1 = nullptr
         )
   {
        auto& obj_1 = **it_1;
   serializeDataType(obj_1, o);
   }
   }
   {
   o.write_uint32_t( 
        (s.paramType != nullptr ? 1 : 0) 
     );
   for(
        auto it_1 = s.paramType != nullptr ? &s.paramType : nullptr
         ; !(
        it_1 == nullptr
         );
        it_1 = nullptr
         )
   {
        auto& obj_1 = **it_1;
   serializeDataType(obj_1, o);
   }
   }
   serializeLimit(s.lowLimit, o);
   serializeLimit(s.highLimit, o);
   o.write_double(s.fixedPrecision);
   o.write_uint8_t(s.floatingSignificandBits);
   o.write_uint8_t(s.floatingExponentBits);
   serializeCharacterSet(s.characterSet, o);
   o.write_uint32_t(s.stringMinSize);
   o.write_uint32_t(s.stringMaxSize);
   o.write_uint32_t(s.encodingAttrs.size());
   for(auto item:s.encodingAttrs) {
   o.write_string(item.first);
   serializeVariant(item.second, o);
   }
   o.write_uint32_t(s.mappingAttrs.size());
   for(auto item:s.mappingAttrs) {
   o.write_string(item.first);
   serializeVariant(item.second, o);
   }
   o.write_uint32_t(s.enumValues.size());
   for(auto item:s.enumValues) {
   o.write_string(item.first);
   o.write_uint32_t(item.second);
   }
}

void serializeEncodingSpecifics( EncodingSpecifics& s, OStream& o ) {
   o.write_string(s.name);
   o.write_uint32_t(s.attrs.size());
   for(auto item:s.attrs) {
   o.write_string(item.first);
   serializeVariant(item.second, o);
   }
}

void serializeEncodedOrMember( EncodedOrMember& s, OStream& o ) {
   serializeLocation(s.location, o);
}

void serializeDataMember( DataMember& s, OStream& o ) {
	serializeEncodedOrMember( *((EncodedOrMember*)(&s)), o ); // MANUALLY ADDED
   serializeDataType(s.type, o);
   o.write_string(s.name);
   o.write_uint8_t(s.extendTo);
   serializeVariant(s.defaultValue, o);
   {
   o.write_uint32_t( 
        s.whenDiscriminant.size() 
     );
   for(
        auto& it_1 = s.whenDiscriminant.begin() 
         ; !(
        it_1 == s.whenDiscriminant.end() 
         );
        ++it_1 
         )
   {
        auto& obj_1 = *it_1;
   o.write_string(obj_1);
   }
   }
}

void serializeEncodedMembers( EncodedMembers& s, OStream& o ) {
	serializeEncodedOrMember( *((EncodedOrMember*)(&s)), o ); // MANUALLY ADDED
   serializeEncodingSpecifics(s.encodingSpecifics, o);
   {
   o.write_uint32_t( 
        s.members.size() 
     );
   for(
        auto& it_1 = s.members.begin() 
         ; !(
        it_1 == s.members.end() 
         );
        ++it_1 
         )
   {
        auto& obj_1 = *it_1;
   {
   o.write_uint32_t( 
        (obj_1 != nullptr ? 1 : 0) 
     );
   for(
        auto it_2 = obj_1 != nullptr ? &obj_1 : nullptr
         ; !(
        it_2 == nullptr
         );
        it_2 = nullptr
         )
   {
	   // MANUALLY ADDED
//        auto& obj_2 = **it_2;
//   serializeEncodedOrMember(obj_2, o);
	   do
	   {
		  // DataMember is behind
		  DataMember* ptr_0 = dynamic_cast<DataMember*>(&(**it_2));
		  if ( ptr_0 )
		  {
			  o.write_uint8_t( 0 );
			  serializeDataMember( *ptr_0, o );
			  break;
		  }
		  // EncodedMembers is behind
		  EncodedMembers* ptr_1 = dynamic_cast<EncodedMembers*>(&(**it_2));
		  if ( ptr_1 )
		  {
			  o.write_uint8_t( 1 );
			  serializeEncodedMembers( *ptr_1, o );
			  break;
		  }
		  // Structure is behind
		  Structure* ptr_2 = dynamic_cast<Structure*>(&(**it_2));
		  if ( ptr_2 )
		  {
			  o.write_uint8_t( 2 );
			  serializeStructure( *ptr_2, o );
			  break;
		  }
		  // base class
		  o.write_uint8_t( 3 );
		  serializeEncodedOrMember( **it_2, o );
	   }
	   while ( 0 );
	   // end of MANUALLY ADDED
   }
   }
   }
   }
}

void serializeStructure( Structure& s, OStream& o ) {
	serializeEncodedMembers( *((EncodedMembers*)(&s)), o ); // MANUALLY ADDED
      switch ( s.declType )
	  {
        case 0 /*IDL*/: o.write_uint8_t( 0 ); break;
        case 2 /*ENCODING*/: o.write_uint8_t( 1 ); break;
        case 1 /*MAPPING*/: o.write_uint8_t( 2 ); break;
        default: assert( 0 );
	  }
      switch ( s.type )
	  {
        case 2 /*DISCRIMINATED_UNION*/: o.write_uint8_t( 0 ); break;
        case 1 /*RPC*/: o.write_uint8_t( 1 ); break;
        case 0 /*STRUCT*/: o.write_uint8_t( 2 ); break;
        default: assert( 0 );
	  }
   o.write_string(s.name);
   o.write_string(s.discriminant);
}

void serializeTypedef( Typedef& s, OStream& o ) {
   serializeLocation(s.location, o);
   serializeDataType(s.type, o);
   o.write_string(s.name);
}

void serializeRoot( Root& s, OStream& o ) {
   {
   o.write_uint32_t( 
        s.typedefs.size() 
     );
   for(
        auto& it_1 = s.typedefs.begin() 
         ; !(
        it_1 == s.typedefs.end() 
         );
        ++it_1 
         )
   {
        auto& obj_1 = *it_1;
   serializeTypedef(obj_1, o);
   }
   }
   {
   o.write_uint32_t( 
        s.structures.size() 
     );
   for(
        auto& it_1 = s.structures.begin() 
         ; !(
        it_1 == s.structures.end() 
         );
        ++it_1 
         )
   {
        auto& obj_1 = *it_1;
   {
   o.write_uint32_t( 
        (obj_1 != nullptr ? 1 : 0) 
     );
   for(
        auto it_2 = obj_1 != nullptr ? &obj_1 : nullptr
         ; !(
        it_2 == nullptr
         );
        it_2 = nullptr
         )
   {
        auto& obj_2 = **it_2;
   serializeStructure(obj_2, o);
   }
   }
   }
   }
}



  
// DESERIALIZATION
bool deserializeLimit( Limit& s, IStream& i ) {
   i.read_bool(s.inclusive);
   i.read_double(s.value);

   return true;
}

bool deserializeLocation( Location& s, IStream& i ) {
   i.read_string(s.fileName);
   uint16_t tmp; i.read_uint16_t(tmp);s.lineNumber=tmp; // MANUALLY EDITED

   return true;
}

bool deserializeCharacterRange( CharacterRange& s, IStream& i ) {
   i.read_uint32_t(s.from);
   i.read_uint32_t(s.to);

   return true;
}

bool deserializeCharacterSet( CharacterSet& s, IStream& i ) {
   {
     uint32_t size_1;
	 i.read_uint32_t(size_1);
     for(uint32_t k_1=0; k_1<size_1; ++k_1) {
   CharacterRange
        obj_1;
   deserializeCharacterRange(obj_1, i);
        s.ranges.push_back(std::move(obj_1)) 
        ;
     }
   }

   return true;
}

bool deserializeVariant( Variant& s, IStream& i ) {
   {
       uint8_t tmp;
       i.read_uint8_t(tmp);
       switch ( tmp )
       {
	      case 0: s.kind = s.NONE; break;
	      case 1: s.kind = s.NUMBER; break;
	      case 2: s.kind = s.STRING; break;
          default: assert(0);
       }
   }
 
   i.read_double(s.numberValue);
   i.read_string(s.stringValue);

   return true;
}

bool deserializeDataType( DataType& s, IStream& i ) {
   {
       uint8_t tmp;
       i.read_uint8_t(tmp);
       switch ( tmp )
       {
	      case 0: s.kind = s.BIT_STRING; break;
	      case 1: s.kind = s.CHARACTER_STRING; break;
	      case 2: s.kind = s.DISCRIMINATED_UNION; break;
	      case 3: s.kind = s.ENCODING_SPECIFIC; break;
	      case 4: s.kind = s.ENUM; break;
	      case 5: s.kind = s.FIXED_POINT; break;
	      case 6: s.kind = s.FLOATING_POINT; break;
	      case 7: s.kind = s.MAPPING_SPECIFIC; break;
	      case 8: s.kind = s.NAMED_TYPE; break;
	      case 9: s.kind = s.CHARACTER; break;
	      case 10: s.kind = s.DICTIONARY; break;
	      case 11: s.kind = s.INTEGER; break;
	      case 12: s.kind = s.SEQUENCE; break;
          default: assert(0);
       }
   }
 
   i.read_string(s.name);
   i.read_string(s.mappingName);
   i.read_string(s.encodingName);
   {
     uint32_t size_1;
	 i.read_uint32_t(size_1);
     for(uint32_t k_1=0; k_1<size_1; ++k_1) {
   DataType
        &obj_1 = *(new 
   DataType
        );
   deserializeDataType(obj_1, i);
        s.keyType.reset(&obj_1) 
        ;
     }
   }
   {
     uint32_t size_1;
	 i.read_uint32_t(size_1);
     for(uint32_t k_1=0; k_1<size_1; ++k_1) {
   DataType
        &obj_1 = *(new 
   DataType
        );
   deserializeDataType(obj_1, i);
        s.paramType.reset(&obj_1) 
        ;
     }
   }
   deserializeLimit(s.lowLimit, i);
   deserializeLimit(s.highLimit, i);
   i.read_double(s.fixedPrecision);
   i.read_uint8_t(s.floatingSignificandBits);
   i.read_uint8_t(s.floatingExponentBits);
   deserializeCharacterSet(s.characterSet, i);
   i.read_uint32_t(s.stringMinSize);
   i.read_uint32_t(s.stringMaxSize);
   {
     uint32_t size_1;
	 i.read_uint32_t(size_1);
     for(uint32_t k_1=0; k_1<size_1; ++k_1) {
   std::string 
        obj_1_key;
   Variant
        obj_1_value;
   i.read_string(obj_1_key);
   deserializeVariant(obj_1_value, i);
        s.encodingAttrs.insert( make_pair( obj_1_key, obj_1_value ) )
        ;
     }
   }
   {
     uint32_t size_1;
	 i.read_uint32_t(size_1);
     for(uint32_t k_1=0; k_1<size_1; ++k_1) {
   std::string 
        obj_1_key;
   Variant
        obj_1_value;
   i.read_string(obj_1_key);
   deserializeVariant(obj_1_value, i);
        s.mappingAttrs.insert( make_pair( obj_1_key, obj_1_value ) )
        ;
     }
   }
   {
     uint32_t size_1;
	 i.read_uint32_t(size_1);
     for(uint32_t k_1=0; k_1<size_1; ++k_1) {
   std::string 
        obj_1_key;
   uint32_t
        obj_1_value;
   i.read_string(obj_1_key);
   i.read_uint32_t(obj_1_value);
        s.enumValues.insert( make_pair( obj_1_key, obj_1_value ) )
        ;
     }
   }

   return true;
}

bool deserializeEncodingSpecifics( EncodingSpecifics& s, IStream& i ) {
   i.read_string(s.name);
   {
     uint32_t size_1;
	 i.read_uint32_t(size_1);
     for(uint32_t k_1=0; k_1<size_1; ++k_1) {
   std::string 
        obj_1_key;
   Variant
        obj_1_value;
   i.read_string(obj_1_key);
   deserializeVariant(obj_1_value, i);
        s.attrs.insert( make_pair( obj_1_key, obj_1_value ) )
        ;
     }
   }

   return true;
}

bool deserializeEncodedOrMember( EncodedOrMember& s, IStream& i ) {
   deserializeLocation(s.location, i);

   return true;
}

bool deserializeDataMember( DataMember& s, IStream& i ) {
	deserializeEncodedOrMember( *((EncodedOrMember*)(&s)), i ); // MANUALLY ADDED
   deserializeDataType(s.type, i);
   i.read_string(s.name);
   i.read_bool(s.extendTo);
   deserializeVariant(s.defaultValue, i);
   {
     uint32_t size_1;
	 i.read_uint32_t(size_1);
     for(uint32_t k_1=0; k_1<size_1; ++k_1) {
   std::string 
        obj_1;
   i.read_string(obj_1);
        s.whenDiscriminant.push_back(std::move(obj_1)) 
        ;
     }
   }

   return true;
}

bool deserializeEncodedMembers( EncodedMembers& s, IStream& i ) {
	deserializeEncodedOrMember( *((EncodedOrMember*)(&s)), i ); // MANUALLY ADDED
   deserializeEncodingSpecifics(s.encodingSpecifics, i);
   {
     uint32_t size_1;
	 i.read_uint32_t(size_1);
     for(uint32_t k_1=0; k_1<size_1; ++k_1) {
   unique_ptr<
   EncodedOrMember
   >
        obj_1;
   {
     uint32_t size_2;
	 i.read_uint32_t(size_2);
     for(uint32_t k_2=0; k_2<size_2; ++k_2) {
		 // MANUALLY ADDED
		 int8_t type;
		 i.read_int8_t( type );
		 switch ( type )
		 {
			case 0:
			{
				DataMember &obj_2 = *(new DataMember );
                deserializeDataMember(obj_2, i);
                obj_1.reset(&obj_2);
				break;
			}
			case 1:
			{
				EncodedMembers &obj_2 = *(new EncodedMembers );
                deserializeEncodedMembers(obj_2, i);
                obj_1.reset(&obj_2);
				break;
			}
			case 2:
			{
				Structure &obj_2 = *(new Structure );
                deserializeStructure(obj_2, i);
                obj_1.reset(&obj_2);
				break;
			}
			case 3:
			{
				EncodedOrMember &obj_2 = *(new EncodedOrMember );
                deserializeEncodedOrMember(obj_2, i);
                obj_1.reset(&obj_2);
				break;
			}
			default:
				assert( 0 );
		 }
/*   EncodedOrMember
        &obj_2 = *(new 
   EncodedOrMember
        );
   deserializeEncodedOrMember(obj_2, i);
        obj_1.reset(&obj_2) 
        ;*/
		 // end of MANUALLY ADDED
     }
   }
        s.members.push_back(std::move(obj_1)) 
        ;
     }
   }

   return true;
}

bool deserializeStructure( Structure& s, IStream& i ) {
	deserializeEncodedMembers( *((EncodedMembers*)(&s)), i ); // MANUALLY ADDED
   {
       uint8_t tmp;
       i.read_uint8_t(tmp);
       switch ( tmp )
       {
	      case 0: s.declType = s.IDL; break;
	      case 1: s.declType = s.ENCODING; break;
	      case 2: s.declType = s.MAPPING; break;
          default: assert(0);
       }
   }
 
   {
       uint8_t tmp;
       i.read_uint8_t(tmp);
       switch ( tmp )
       {
	      case 0: s.type = s.DISCRIMINATED_UNION; break;
	      case 1: s.type = s.RPC; break;
	      case 2: s.type = s.STRUCT; break;
          default: assert(0);
       }
   }
 
   i.read_string(s.name);
   i.read_string(s.discriminant);

   return true;
}

bool deserializeTypedef( Typedef& s, IStream& i ) {
   deserializeLocation(s.location, i);
   deserializeDataType(s.type, i);
   i.read_string(s.name);

   return true;
}

bool deserializeRoot( Root& s, IStream& i ) {
   {
     uint32_t size_1;
	 i.read_uint32_t(size_1);
     for(uint32_t k_1=0; k_1<size_1; ++k_1) {
   Typedef
        obj_1;
   deserializeTypedef(obj_1, i);
        s.typedefs.push_back(std::move(obj_1)) 
        ;
     }
   }
   {
     uint32_t size_1;
	 i.read_uint32_t(size_1);
     for(uint32_t k_1=0; k_1<size_1; ++k_1) {
   unique_ptr<
   Structure
   >
        obj_1;
   {
     uint32_t size_2;
	 i.read_uint32_t(size_2);
     for(uint32_t k_2=0; k_2<size_2; ++k_2) {
   Structure
        &obj_2 = *(new 
   Structure
        );
   deserializeStructure(obj_2, i);
        obj_1.reset(&obj_2) 
        ;
     }
   }
        s.structures.push_back(std::move(obj_1)) 
        ;
     }
   }

   return true;
}


  
  
// PRINTING
void printLimit( Limit& s ) {
    cout << "inclusive: ";
   cout << s.inclusive << endl;
    cout << endl;
    cout << "value: ";
   cout << s.value << endl;
    cout << endl;
}

void printLocation( Location& s ) {
    cout << "fileName: ";
   cout << s.fileName << endl;
    cout << endl;
    cout << "lineNumber: ";
   cout << s.lineNumber << endl;
    cout << endl;
}

void printCharacterRange( CharacterRange& s ) {
    cout << "from: ";
   cout << s.from << endl;
    cout << endl;
    cout << "to: ";
   cout << s.to << endl;
    cout << endl;
}

void printCharacterSet( CharacterSet& s ) {
    cout << "ranges: ";
   for(
        auto& it_1 = s.ranges.begin() 
         ; !(
        it_1 == s.ranges.end() 
         );
        ++it_1 
         )
   {
        auto& obj_1 = *it_1;
   printCharacterRange( obj_1 );
   }
    cout << endl;
}

void printVariant( Variant& s ) {
    cout << "kind: ";
   cout << s.kind;
    cout << endl;
    cout << "numberValue: ";
   cout << s.numberValue << endl;
    cout << endl;
    cout << "stringValue: ";
   cout << s.stringValue << endl;
    cout << endl;
}

void printDataType( DataType& s ) {
    cout << "kind: ";
   cout << s.kind;
    cout << endl;
    cout << "name: ";
   cout << s.name << endl;
    cout << endl;
    cout << "mappingName: ";
   cout << s.mappingName << endl;
    cout << endl;
    cout << "encodingName: ";
   cout << s.encodingName << endl;
    cout << endl;
    cout << "keyType: ";
   for(
        auto it_1 = s.keyType != nullptr ? &s.keyType : nullptr
         ; !(
        it_1 == nullptr
         );
        it_1 = nullptr
         )
   {
        auto& obj_1 = **it_1;
   printDataType( obj_1 );
   }
    cout << endl;
    cout << "paramType: ";
   for(
        auto it_1 = s.paramType != nullptr ? &s.paramType : nullptr
         ; !(
        it_1 == nullptr
         );
        it_1 = nullptr
         )
   {
        auto& obj_1 = **it_1;
   printDataType( obj_1 );
   }
    cout << endl;
    cout << "lowLimit: ";
   printLimit( s.lowLimit );
    cout << endl;
    cout << "highLimit: ";
   printLimit( s.highLimit );
    cout << endl;
    cout << "fixedPrecision: ";
   cout << s.fixedPrecision << endl;
    cout << endl;
    cout << "floatingSignificandBits: ";
   cout << s.floatingSignificandBits << endl;
    cout << endl;
    cout << "floatingExponentBits: ";
   cout << s.floatingExponentBits << endl;
    cout << endl;
    cout << "characterSet: ";
   printCharacterSet( s.characterSet );
    cout << endl;
    cout << "stringMinSize: ";
   cout << s.stringMinSize << endl;
    cout << endl;
    cout << "stringMaxSize: ";
   cout << s.stringMaxSize << endl;
    cout << endl;
    cout << "encodingAttrs: ";
   cout << "size = " << s.encodingAttrs.size() << endl;
   for(auto item:s.encodingAttrs) {
   cout << item.first << endl;
   printVariant( item.second );
   }
    cout << endl;
    cout << "mappingAttrs: ";
   cout << "size = " << s.mappingAttrs.size() << endl;
   for(auto item:s.mappingAttrs) {
   cout << item.first << endl;
   printVariant( item.second );
   }
    cout << endl;
    cout << "enumValues: ";
   cout << "size = " << s.enumValues.size() << endl;
   for(auto item:s.enumValues) {
   cout << item.first << endl;
   cout << item.second << endl;
   }
    cout << endl;
}

void printEncodingSpecifics( EncodingSpecifics& s ) {
    cout << "name: ";
   cout << s.name << endl;
    cout << endl;
    cout << "attrs: ";
   cout << "size = " << s.attrs.size() << endl;
   for(auto item:s.attrs) {
   cout << item.first << endl;
   printVariant( item.second );
   }
    cout << endl;
}

void printEncodedOrMember( EncodedOrMember& s ) {
    cout << "location: ";
   printLocation( s.location );
    cout << endl;
}

void printDataMember( DataMember& s ) {
	printEncodedOrMember( *((EncodedOrMember*)(&s)) ); // MANUALLY ADDED
    cout << "type: ";
   printDataType( s.type );
    cout << endl;
    cout << "name: ";
   cout << s.name << endl;
    cout << endl;
    cout << "extendTo: ";
   cout << s.extendTo << endl;
    cout << endl;
    cout << "defaultValue: ";
   printVariant( s.defaultValue );
    cout << endl;
    cout << "whenDiscriminant: ";
   for(
        auto& it_1 = s.whenDiscriminant.begin() 
         ; !(
        it_1 == s.whenDiscriminant.end() 
         );
        ++it_1 
         )
   {
        auto& obj_1 = *it_1;
   cout << obj_1 << endl;
   }
    cout << endl;
}

void printEncodedMembers( EncodedMembers& s ) {
	printEncodedOrMember( *((EncodedOrMember*)(&s)) ); // MANUALLY ADDED
    cout << "encodingSpecifics: ";
   printEncodingSpecifics( s.encodingSpecifics );
    cout << endl;
    cout << "members: ";
   for(
        auto& it_1 = s.members.begin() 
         ; !(
        it_1 == s.members.end() 
         );
        ++it_1 
         )
   {
        auto& obj_1 = *it_1;
   for(
        auto it_2 = obj_1 != nullptr ? &obj_1 : nullptr
         ; !(
        it_2 == nullptr
         );
        it_2 = nullptr
         )
   {
   	   // MANUALLY ADDED
//        auto& obj_2 = **it_2;
//   printEncodedOrMember( obj_2 );
	   do
	   {
		  // DataMember is behind
		  DataMember* ptr_0 = dynamic_cast<DataMember*>(&(**it_2));
		  if ( ptr_0 )
		  {
			  printDataMember( *ptr_0 );
			  break;
		  }
		  // EncodedMembers is behind
		  EncodedMembers* ptr_1 = dynamic_cast<EncodedMembers*>(&(**it_2));
		  if ( ptr_1 )
		  {
			  printEncodedMembers( *ptr_1 );
			  break;
		  }
		  // Structure is behind
		  Structure* ptr_2 = dynamic_cast<Structure*>(&(**it_2));
		  if ( ptr_2 )
		  {
			  printStructure( *ptr_2 );
			  break;
		  }
		  // base class
		  printEncodedOrMember( **it_2 );
	   }
	   while ( 0 );
	   // end of MANUALLY ADDED

   }
   }
    cout << endl;
}

void printStructure( Structure& s ) {
	printEncodedMembers( *((EncodedMembers*)(&s)) ); // MANUALLY ADDED
    cout << "declType: ";
   cout << s.declType;
    cout << endl;
    cout << "type: ";
   cout << s.type;
    cout << endl;
    cout << "name: ";
   cout << s.name << endl;
    cout << endl;
    cout << "discriminant: ";
   cout << s.discriminant << endl;
    cout << endl;
}

void printTypedef( Typedef& s ) {
    cout << "location: ";
   printLocation( s.location );
    cout << endl;
    cout << "type: ";
   printDataType( s.type );
    cout << endl;
    cout << "name: ";
   cout << s.name << endl;
    cout << endl;
}

void printRoot( Root& s ) {
    cout << "typedefs: ";
   for(
        auto& it_1 = s.typedefs.begin() 
         ; !(
        it_1 == s.typedefs.end() 
         );
        ++it_1 
         )
   {
        auto& obj_1 = *it_1;
   printTypedef( obj_1 );
   }
    cout << endl;
    cout << "structures: ";
   for(
        auto& it_1 = s.structures.begin() 
         ; !(
        it_1 == s.structures.end() 
         );
        ++it_1 
         )
   {
        auto& obj_1 = *it_1;
   for(
        auto it_2 = obj_1 != nullptr ? &obj_1 : nullptr
         ; !(
        it_2 == nullptr
         );
        it_2 = nullptr
         )
   {
        auto& obj_2 = **it_2;
   printStructure( obj_2 );
   }
   }
    cout << endl;
}





