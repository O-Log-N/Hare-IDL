#include "output.h"

#include "sample.h"

// IMPLEMENTATIONS

// SERIALIZATION

void serializeItem( const Item& s, OStream& o ) {
    o.writeUInt(1, s.id);
    o.writeString(2, s.name);
    o.writeUInt(3, s.valid);
}

void serializeCharacter( const Character& s, OStream& o ) {
    o.writeUInt(1, s.max_u8);
    o.writeUInt(2, s.max_u16);
    o.writeUInt(3, s.max_u32);
    o.writeInt(4, s.min_s8);
    o.writeInt(5, s.min_s16);
    o.writeInt(6, s.min_s32);
    o.writeInt(7, s.max_s8);
    o.writeInt(8, s.max_s16);
    o.writeInt(9, s.max_s32);
    o.writeDouble(10, s.x);
    o.writeDouble(11, s.y);
    o.writeDouble(12, s.z);
    o.writeUInt(13, s.flag);
    o.writeString(14, s.desc);
    for(const auto& item:s.more_text) {
    o.writeString(15, item);
    }
    for(const auto& item:s.some_ints) {
    o.writeInt(16, item);
    }
    for(const auto& item:s.inventory) {
    size_t sz_17 = getSizeItem(item);
    o.writeObjectTagAndSize(17, sz_17);
    serializeItem(item, o);
    }
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
      uint64_t temp = 0;
      initFlags[0] = i.readVariantUInt64( temp );
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
      uint64_t temp = 0;
      initFlags[2] = i.readVariantUInt64( temp );
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
      uint64_t temp = 0;
      initFlags[0] = i.readVariantUInt64( temp );
      s.max_u8 = temp;
      break;
    }
    case 2:
    {
      uint64_t temp = 0;
      initFlags[1] = i.readVariantUInt64( temp );
      s.max_u16 = temp;
      break;
    }
    case 3:
    {
      uint64_t temp = 0;
      initFlags[2] = i.readVariantUInt64( temp );
      s.max_u32 = temp;
      break;
    }
    case 4:
    {
      int64_t temp = 0;
      initFlags[3] = i.readVariantInt64( temp );
      s.min_s8 = temp;
      break;
    }
    case 5:
    {
      int64_t temp = 0;
      initFlags[4] = i.readVariantInt64( temp );
      s.min_s16 = temp;
      break;
    }
    case 6:
    {
      int64_t temp = 0;
      initFlags[5] = i.readVariantInt64( temp );
      s.min_s32 = temp;
      break;
    }
    case 7:
    {
      int64_t temp = 0;
      initFlags[6] = i.readVariantInt64( temp );
      s.max_s8 = temp;
      break;
    }
    case 8:
    {
      int64_t temp = 0;
      initFlags[7] = i.readVariantInt64( temp );
      s.max_s16 = temp;
      break;
    }
    case 9:
    {
      int64_t temp = 0;
      initFlags[8] = i.readVariantInt64( temp );
      s.max_s32 = temp;
      break;
    }
    case 10:
    {
      initFlags[9] = i.readFixed64Bit( s.x );
      break;
    }
    case 11:
    {
      initFlags[10] = i.readFixed64Bit( s.y );
      break;
    }
    case 12:
    {
      initFlags[11] = i.readFixed64Bit( s.z );
      break;
    }
    case 13:
    {
      uint64_t temp = 0;
      initFlags[12] = i.readVariantUInt64( temp );
      s.flag = static_cast<bool>( temp );
      break;
    }
    case 14:
    {
     initFlags[13] = i.readString( s.desc );
      break;
    }
    case 15:
    {
      string temp2;
     initFlags[14] = i.readString( temp2 );
      s.more_text.push_back(temp2);
      break;
    }
    case 16:
    {
      int16_t temp2;
      int64_t temp = 0;
      initFlags[15] = i.readVariantInt64( temp );
      temp2 = temp;
      s.some_ints.push_back(temp2);
      break;
    }
    case 17:
    {
      Item temp2;
    uint64_t sz_16 = 0;
    i.readVariantUInt64(sz_16);
    IStream is_16 = i.makeSubStream(sz_16);
    initFlags[16] = deserializeItem(temp2, is_16);
      s.inventory.push_back(temp2);
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
    cout << "max_u32: ";
	cout << 
   s.max_u32 
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
    cout << "inventory: ";
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
  sz += getVarIntSize(s.max_u32);
      
  sz += getTagSize(4);
  sz += getVarIntSize(s.min_s8);
      
  sz += getTagSize(5);
  sz += getVarIntSize(s.min_s16);
      
  sz += getTagSize(6);
  sz += getVarIntSize(s.min_s32);
      
  sz += getTagSize(7);
  sz += getVarIntSize(s.max_s8);
      
  sz += getTagSize(8);
  sz += getVarIntSize(s.max_s16);
      
  sz += getTagSize(9);
  sz += getVarIntSize(s.max_s32);
      
  sz += getTagSize(10);
  sz += getFixedSize(s.x);
      
  sz += getTagSize(11);
  sz += getFixedSize(s.y);
      
  sz += getTagSize(12);
  sz += getFixedSize(s.z);
      
  sz += getTagSize(13);
  sz += getVarIntSize(s.flag);
      
  sz += getTagSize(14);
  sz += getVarIntSize(s.desc.size());
  sz += s.desc.size();
      
    for(const auto& item:s.more_text) {
  sz += getTagSize(15);
  sz += getVarIntSize(item.size());
  sz += item.size();
    }
      
    for(const auto& item:s.some_ints) {
  sz += getTagSize(16);
  sz += getVarIntSize(item);
    }
      
    for(const auto& item:s.inventory) {
  sz += getTagSize(17);
  size_t sz_17 = getSizeItem(item);
  sz += getVarIntSize(sz_17);
  sz += sz_17;
    }
   
   return sz;
}




