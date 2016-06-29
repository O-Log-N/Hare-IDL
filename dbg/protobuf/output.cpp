#include "output.h"

#include <bitset>
#include "sample.h"

// IMPLEMENTATIONS

// SERIALIZATION

void serializeItem( Item& s, OStream& o ) {
   o.writeString(1, s.name);
}

void serializeCharacter( Character& s, OStream& o ) {
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
}



  
// DESERIALIZATION
bool deserializeItem( Item& s, IStream& i ) {
   int type;
   int fieldNumber;
   bool readret;
   const int memcnt = 1;
   uint8_t initFlags[memcnt];
   memset( initFlags, 0, memcnt );
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
   const int memcnt = 13;
   uint8_t initFlags[memcnt];
   memset( initFlags, 0, memcnt );
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
void printItem( Item& s ) {
    cout << "name: ";
	cout << 
   s.name 
	  ;
    cout << endl;
}

void printCharacter( Character& s ) {
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
}



