#include "output.h"

#include "sample.h"

// IMPLEMENTATIONS

// SERIALIZATION

void serializeItemBase( const ItemBase& s, OStream& o ) {
    o.writeUInt(1, s.id);
}

void serializeItem( const Item& s, OStream& o ) {
    o.writeString(1, s.name);
    o.writeUInt(2, s.valid);
    size_t sz_3 = getSizeItemBase(s);
    o.writeObjectTagAndSize(3, sz_3);
    serializeItemBase(s, o);
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
    switch ( s.anim )
    {
        case 2 /*Running*/: o.writeUInt(13, 0 ); break;
        case 0 /*Standing*/: o.writeUInt(13, 1 ); break;
        case 1 /*Walking*/: o.writeUInt(13, 2 ); break;
        default: assert( 0 );
    }
    o.writeUInt(14, s.flag);
    o.writeString(15, s.desc);
    for(const auto& item:s.more_text) {
    o.writeString(16, item);
    }
    for(const auto& item:s.some_ints) {
    o.writeInt(17, item);
    }
    for(const auto& item:s.inventory) {
    size_t sz_18 = getSizeItem(item);
    o.writeObjectTagAndSize(18, sz_18);
    serializeItem(item, o);
    }
    size_t sz_19 = getSize__unique_ptr_ItemBase(s.poly_ptr);
    o.writeObjectTagAndSize(19, sz_19);
    serialize__unique_ptr_ItemBase(s.poly_ptr, o);
}


void serialize__unique_ptr_ItemBase( const unique_ptr<ItemBase>& s, OStream& o ) {
  
  if(s.get() == nullptr) {
    return;
  }
       else if ( typeid( *s ) == typeid( Item ) ) {
         auto ptr = dynamic_cast<Item*>(s.get());
    size_t sz_1 = getSizeItem(*ptr);
    o.writeObjectTagAndSize(1, sz_1);
    serializeItem(*ptr, o);

       }
       else if ( typeid( *s ) == typeid( ItemBase ) ) {
         auto ptr = dynamic_cast<ItemBase*>(s.get());
    size_t sz_2 = getSizeItemBase(*ptr);
    o.writeObjectTagAndSize(2, sz_2);
    serializeItemBase(*ptr, o);

       }
   else {
     ;// TODO assert?
   }
}

  
// DESERIALIZATION
bool deserializeItemBase( ItemBase& s, IStream& i ) {
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
      uint64_t temp = 0;
      initFlags[0] = i.readVariantUInt64( temp );
      s.id = temp;
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
     initFlags[0] = i.readString( s.name );
      break;
    }
    case 2:
    {
      uint64_t temp = 0;
      initFlags[1] = i.readVariantUInt64( temp );
      s.valid = static_cast<bool>( temp );
      break;
    }
    case 3:
    {
    uint64_t sz_2 = 0;
    i.readVariantUInt64(sz_2);
    IStream is_2 = i.makeSubStream(sz_2);
    initFlags[2] = deserializeItemBase(s, is_2);
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
   const int memcnt = 19;
   uint8_t initFlags[memcnt] = { 0 };
  initFlags[15] = true;
  initFlags[16] = true;
  initFlags[17] = true;
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
   {
       uint64_t temp = 0;
       initFlags[12] = i.readVariantUInt64( temp );
       switch ( temp )
       {
	      case 0: s.anim = s.Running; break;
	      case 1: s.anim = s.Standing; break;
	      case 2: s.anim = s.Walking; break;
          default: assert(0);
       }
   }
      break;
    }
    case 14:
    {
      uint64_t temp = 0;
      initFlags[13] = i.readVariantUInt64( temp );
      s.flag = static_cast<bool>( temp );
      break;
    }
    case 15:
    {
     initFlags[14] = i.readString( s.desc );
      break;
    }
    case 16:
    {
      string temp2;
     initFlags[15] = i.readString( temp2 );
      s.more_text.push_back(temp2);
      break;
    }
    case 17:
    {
      int16_t temp2;
      int64_t temp = 0;
      initFlags[16] = i.readVariantInt64( temp );
      temp2 = temp;
      s.some_ints.push_back(temp2);
      break;
    }
    case 18:
    {
      Item temp2;
    uint64_t sz_17 = 0;
    i.readVariantUInt64(sz_17);
    IStream is_17 = i.makeSubStream(sz_17);
    initFlags[17] = deserializeItem(temp2, is_17);
      s.inventory.push_back(temp2);
      break;
    }
    case 19:
    {
    uint64_t sz_18 = 0;
    i.readVariantUInt64(sz_18);
    IStream is_18 = i.makeSubStream(sz_18);
    initFlags[18] = deserialize__unique_ptr_ItemBase(s.poly_ptr, is_18);
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


bool deserialize__unique_ptr_ItemBase( unique_ptr<ItemBase>& s, IStream& i ) {
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
       //else if ( typeid( *s ) == typeid( Item ) ) 
         unique_ptr<Item> ptr(new Item);
    uint64_t sz_1 = 0;
    i.readVariantUInt64(sz_1);
    IStream is_1 = i.makeSubStream(sz_1);
    initFlags[1] = deserializeItem(*ptr, is_1);
         s = move(ptr);
       }
       break;
       case 2:
       {
       //else if ( typeid( *s ) == typeid( ItemBase ) ) 
         unique_ptr<ItemBase> ptr(new ItemBase);
    uint64_t sz_2 = 0;
    i.readVariantUInt64(sz_2);
    IStream is_2 = i.makeSubStream(sz_2);
    initFlags[2] = deserializeItemBase(*ptr, is_2);
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

   bool OK = true;
   for ( int i=0; i<memcnt; i++ )
     OK = OK || initFlags[i] != 0;

   return OK;
}
  
  
// PRINTING
void printItemBase( const ItemBase& s ) {
/*    cout << "id: ";
	cout << 
   s.id 
	  ;
    cout << endl;*/
}

void printItem( const Item& s ) {
/*    cout << "name: ";
	cout << 
   s.name 
	  ;
    cout << endl;*/
/*    cout << "valid: ";
	cout << 
   s.valid 
	  ;
    cout << endl;*/
/*    cout << "__parent: ";
	cout << 
  "TODO"
	  ;
    cout << endl;*/
}

void printCharacter( const Character& s ) {
/*    cout << "max_u8: ";
	cout << 
   s.max_u8 
	  ;
    cout << endl;*/
/*    cout << "max_u16: ";
	cout << 
   s.max_u16 
	  ;
    cout << endl;*/
/*    cout << "max_u32: ";
	cout << 
   s.max_u32 
	  ;
    cout << endl;*/
/*    cout << "min_s8: ";
	cout << 
   s.min_s8 
	  ;
    cout << endl;*/
/*    cout << "min_s16: ";
	cout << 
   s.min_s16 
	  ;
    cout << endl;*/
/*    cout << "min_s32: ";
	cout << 
   s.min_s32 
	  ;
    cout << endl;*/
/*    cout << "max_s8: ";
	cout << 
   s.max_s8 
	  ;
    cout << endl;*/
/*    cout << "max_s16: ";
	cout << 
   s.max_s16 
	  ;
    cout << endl;*/
/*    cout << "max_s32: ";
	cout << 
   s.max_s32 
	  ;
    cout << endl;*/
/*    cout << "x: ";
	cout << 
   s.x 
	  ;
    cout << endl;*/
/*    cout << "y: ";
	cout << 
   s.y 
	  ;
    cout << endl;*/
/*    cout << "z: ";
	cout << 
   s.z 
	  ;
    cout << endl;*/
/*    cout << "anim: ";
	cout << 
   s.anim 
	  ;
    cout << endl;*/
/*    cout << "flag: ";
	cout << 
   s.flag 
	  ;
    cout << endl;*/
/*    cout << "desc: ";
	cout << 
   s.desc 
	  ;
    cout << endl;*/
/*    cout << "more_text: ";
	cout << 
    "TODO"
	  ;
    cout << endl;*/
/*    cout << "some_ints: ";
	cout << 
    "TODO"
	  ;
    cout << endl;*/
/*    cout << "inventory: ";
	cout << 
    "TODO"
	  ;
    cout << endl;*/
/*    cout << "poly_ptr: ";
	cout << 
  "TODO"
	  ;
    cout << endl;*/
}


void print__unique_ptr_ItemBase( unique_ptr<ItemBase>& s ) {
uint8_t TMP; if ( s == nullptr ) TMP = 2; else if ( typeid( *(s) ) == typeid( Item ) ) TMP = 0; else if ( typeid( *(s) ) == typeid( ItemBase ) ) TMP = 1; 
/*   switch ( TMP )
   {
      case 2:
	  {
  "TODO"
         break;
      }
      case 1:
	  {
  "TODO"
         break;
      }
   }*/
}


// GET-SIZE
size_t getSizeItemBase( const ItemBase& s ) {
   size_t sz = 0;
      
  sz += getTagSize(1);
  sz += getUnsignedVarIntSize(s.id);
   
   return sz;
}

size_t getSizeItem( const Item& s ) {
   size_t sz = 0;
      
  sz += getTagSize(1);
  sz += getUnsignedVarIntSize(s.name.size());
  sz += s.name.size();
      
  sz += getTagSize(2);
  sz += getUnsignedVarIntSize(s.valid);
      
  sz += getTagSize(3);
  size_t sz_3 = getSizeItemBase(s);
  sz += getUnsignedVarIntSize(sz_3);
  sz += sz_3;
   
   return sz;
}

size_t getSizeCharacter( const Character& s ) {
   size_t sz = 0;
      
  sz += getTagSize(1);
  sz += getUnsignedVarIntSize(s.max_u8);
      
  sz += getTagSize(2);
  sz += getUnsignedVarIntSize(s.max_u16);
      
  sz += getTagSize(3);
  sz += getUnsignedVarIntSize(s.max_u32);
      
  sz += getTagSize(4);
  sz += getSignedVarIntSize(s.min_s8);
      
  sz += getTagSize(5);
  sz += getSignedVarIntSize(s.min_s16);
      
  sz += getTagSize(6);
  sz += getSignedVarIntSize(s.min_s32);
      
  sz += getTagSize(7);
  sz += getSignedVarIntSize(s.max_s8);
      
  sz += getTagSize(8);
  sz += getSignedVarIntSize(s.max_s16);
      
  sz += getTagSize(9);
  sz += getSignedVarIntSize(s.max_s32);
      
  sz += getTagSize(10);
  sz += getFixedSize(s.x);
      
  sz += getTagSize(11);
  sz += getFixedSize(s.y);
      
  sz += getTagSize(12);
  sz += getFixedSize(s.z);
      
  sz += getTagSize(13);
  sz += getUnsignedVarIntSize(s.anim);
      
  sz += getTagSize(14);
  sz += getUnsignedVarIntSize(s.flag);
      
  sz += getTagSize(15);
  sz += getUnsignedVarIntSize(s.desc.size());
  sz += s.desc.size();
      
    for(const auto& item:s.more_text) {
  sz += getTagSize(16);
  sz += getUnsignedVarIntSize(item.size());
  sz += item.size();
    }
      
    for(const auto& item:s.some_ints) {
  sz += getTagSize(17);
  sz += getSignedVarIntSize(item);
    }
      
    for(const auto& item:s.inventory) {
  sz += getTagSize(18);
  size_t sz_18 = getSizeItem(item);
  sz += getUnsignedVarIntSize(sz_18);
  sz += sz_18;
    }
      
  sz += getTagSize(19);
  size_t sz_19 = getSize__unique_ptr_ItemBase(s.poly_ptr);
  sz += getUnsignedVarIntSize(sz_19);
  sz += sz_19;
   
   return sz;
}


size_t getSize__unique_ptr_ItemBase( const unique_ptr<ItemBase>& s ) {
  

     size_t sz = 0;
  if(s.get() == nullptr) {
    return sz;
  }
       else if ( typeid( *s ) == typeid( Item ) ) {
         auto ptr = dynamic_cast<Item*>(s.get());
  sz += getTagSize(1);
  size_t sz_1 = getSizeItem(*ptr);
  sz += getUnsignedVarIntSize(sz_1);
  sz += sz_1;

       }
       else if ( typeid( *s ) == typeid( ItemBase ) ) {
         auto ptr = dynamic_cast<ItemBase*>(s.get());
  sz += getTagSize(2);
  size_t sz_2 = getSizeItemBase(*ptr);
  sz += getUnsignedVarIntSize(sz_2);
  sz += sz_2;

       }
   else {
     ;// TODO assert?
   }
   return sz;
}


