#include "output.h"

#include "sample.h"

// IMPLEMENTATIONS

// SERIALIZATION

void serializeItem( const Item& s, OStream& o ) {
    o.writeInt(1, s.id);
    o.writeString(2, s.name);
    o.writeInt(3, s.valid);
}

void serializeCharacter( const Character& s, OStream& o ) {
    o.writeInt(1, s.max_u8);
    o.writeInt(2, s.max_u16);
    o.writeInt(3, s.min_s8);
    o.writeInt(4, s.min_s16);
    o.writeInt(5, s.min_s32);
    o.writeInt(6, s.max_s8);
    o.writeInt(7, s.max_s16);
    o.writeInt(8, s.max_s32);
    o.writeDouble(9, s.x);
    o.writeDouble(10, s.y);
    o.writeDouble(11, s.z);
    o.writeInt(12, s.flag);
    o.writeString(13, s.desc);
    for(const auto& item:s.more_text)
    o.writeString(14, item);
    for(const auto& item:s.some_ints)
    o.writeInt(15, item);
}



  
// DESERIALIZATION
bool deserializeItem( Item& s, IStream& i ) {
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
      int64_t temp = 0;
      initFlags[0] = i.readVariantInt64( temp );
      s.id = temp;
      break;
    }
    case 2:
    {
     initFlags[1] = i.readString( s.name );
      break;
    }
    case 3:
    {
      int64_t temp = 0;
      initFlags[2] = i.readVariantInt64( temp );
      s.valid = static_cast<bool>( temp );
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

bool deserializeCharacter( Character& s, IStream& i ) {
   int type;
   int fieldNumber;
   bool readret;
   const int memcnt = 15;
   uint8_t initFlags[memcnt] = { 0 };
  initFlags[13] = true;
  initFlags[14] = true;
   do
   {
      readret = i.readFieldTypeAndID( type, fieldNumber );
	  if ( !readret )
		  break;
	  switch ( fieldNumber )
	  {
    case 1:
    {
      int64_t temp = 0;
      initFlags[0] = i.readVariantInt64( temp );
      s.max_u8 = temp;
      break;
    }
    case 2:
    {
      int64_t temp = 0;
      initFlags[1] = i.readVariantInt64( temp );
      s.max_u16 = temp;
      break;
    }
    case 3:
    {
      int64_t temp = 0;
      initFlags[2] = i.readVariantInt64( temp );
      s.min_s8 = temp;
      break;
    }
    case 4:
    {
      int64_t temp = 0;
      initFlags[3] = i.readVariantInt64( temp );
      s.min_s16 = temp;
      break;
    }
    case 5:
    {
      int64_t temp = 0;
      initFlags[4] = i.readVariantInt64( temp );
      s.min_s32 = temp;
      break;
    }
    case 6:
    {
      int64_t temp = 0;
      initFlags[5] = i.readVariantInt64( temp );
      s.max_s8 = temp;
      break;
    }
    case 7:
    {
      int64_t temp = 0;
      initFlags[6] = i.readVariantInt64( temp );
      s.max_s16 = temp;
      break;
    }
    case 8:
    {
      int64_t temp = 0;
      initFlags[7] = i.readVariantInt64( temp );
      s.max_s32 = temp;
      break;
    }
    case 9:
    {
      initFlags[8] = i.readFixed64Bit( s.x );
      break;
    }
    case 10:
    {
      initFlags[9] = i.readFixed64Bit( s.y );
      break;
    }
    case 11:
    {
      initFlags[10] = i.readFixed64Bit( s.z );
      break;
    }
    case 12:
    {
      int64_t temp = 0;
      initFlags[11] = i.readVariantInt64( temp );
      s.flag = static_cast<bool>( temp );
      break;
    }
    case 13:
    {
     initFlags[12] = i.readString( s.desc );
      break;
    }
    case 14:
    {
   {
      string temp2;
     initFlags[13] = i.readString( temp2 );
      s.more_text.push_back(temp2);
   }
      break;
    }
    case 15:
    {
   {
      int16_t temp2;
      int64_t temp = 0;
      initFlags[14] = i.readVariantInt64( temp );
      temp2 = temp;
      s.some_ints.push_back(temp2);
   }
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


  
  
// PRINTING
void printItem( const Item& s ) {
    cout << "id: ";
	cout << 
   s.id 
	  ;
    cout << endl;
    cout << "name: ";
	cout << 
   s.name 
	  ;
    cout << endl;
    cout << "valid: ";
	cout << 
   s.valid 
	  ;
    cout << endl;
}

void printCharacter( const Character& s ) {
    cout << "max_u8: ";
	cout << 
   s.max_u8 
	  ;
    cout << endl;
    cout << "max_u16: ";
	cout << 
   s.max_u16 
	  ;
    cout << endl;
    cout << "min_s8: ";
	cout << 
   s.min_s8 
	  ;
    cout << endl;
    cout << "min_s16: ";
	cout << 
   s.min_s16 
	  ;
    cout << endl;
    cout << "min_s32: ";
	cout << 
   s.min_s32 
	  ;
    cout << endl;
    cout << "max_s8: ";
	cout << 
   s.max_s8 
	  ;
    cout << endl;
    cout << "max_s16: ";
	cout << 
   s.max_s16 
	  ;
    cout << endl;
    cout << "max_s32: ";
	cout << 
   s.max_s32 
	  ;
    cout << endl;
    cout << "x: ";
	cout << 
   s.x 
	  ;
    cout << endl;
    cout << "y: ";
	cout << 
   s.y 
	  ;
    cout << endl;
    cout << "z: ";
	cout << 
   s.z 
	  ;
    cout << endl;
    cout << "flag: ";
	cout << 
   s.flag 
	  ;
    cout << endl;
    cout << "desc: ";
	cout << 
   s.desc 
	  ;
    cout << endl;
    cout << "more_text: ";
	cout << 
    "TODO"
	  ;
    cout << endl;
    cout << "some_ints: ";
	cout << 
    "TODO"
	  ;
    cout << endl;
}



// GET-SIZE
size_t getSizeItem( const Item& s ) {
   size_t sz = 0;
      
  sz += getTagSize(1);
  sz += getVarIntSize(s.id);
      
  sz += getTagSize(2);
  sz += getVarIntSize(s.name.size());
  sz += s.name.size();
      
  sz += getTagSize(3);
  sz += getVarIntSize(s.valid);
   
   return sz;
}

size_t getSizeCharacter( const Character& s ) {
   size_t sz = 0;
      
  sz += getTagSize(1);
  sz += getVarIntSize(s.max_u8);
      
  sz += getTagSize(2);
  sz += getVarIntSize(s.max_u16);
      
  sz += getTagSize(3);
  sz += getVarIntSize(s.min_s8);
      
  sz += getTagSize(4);
  sz += getVarIntSize(s.min_s16);
      
  sz += getTagSize(5);
  sz += getVarIntSize(s.min_s32);
      
  sz += getTagSize(6);
  sz += getVarIntSize(s.max_s8);
      
  sz += getTagSize(7);
  sz += getVarIntSize(s.max_s16);
      
  sz += getTagSize(8);
  sz += getVarIntSize(s.max_s32);
      
  sz += getTagSize(9);
  sz += getFixedSize(s.x);
      
  sz += getTagSize(10);
  sz += getFixedSize(s.y);
      
  sz += getTagSize(11);
  sz += getFixedSize(s.z);
      
  sz += getTagSize(12);
  sz += getVarIntSize(s.flag);
      
  sz += getTagSize(13);
  sz += getVarIntSize(s.desc.size());
  sz += s.desc.size();
      
    for(const auto& item:s.more_text) {
  sz += getTagSize(14);
  sz += getVarIntSize(item.size());
  sz += item.size();
    }
      
    for(const auto& item:s.some_ints) {
  sz += getTagSize(15);
  sz += getVarIntSize(item);
    }
   
   return sz;
}




