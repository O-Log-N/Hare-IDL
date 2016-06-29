#include "output.h"

#include <bitset>
#include "sample.h"

// IMPLEMENTATIONS

// SERIALIZATION

void serializeItem( Item& s, OStream& o ) {
   o.writeString(1, s.name);
}

void serializeCharacter( Character& s, OStream& o ) {
    o.writeUnsignedVarInt(1, s.max_u8);
    o.writeUnsignedVarInt(2, s.max_u16);
    o.writeUnsignedVarInt(3, s.max_u32);
    o.writeSignedVarInt(4, s.min_s8);
    o.writeSignedVarInt(5, s.min_s16);
    o.writeSignedVarInt(6, s.min_s32);
    o.writeSignedVarInt(7, s.max_s8);
    o.writeSignedVarInt(8, s.max_s16);
    o.writeSignedVarInt(9, s.max_s32);
   o.writeFloatingPoint(10, s.x);
   o.writeFloatingPoint(11, s.y);
   o.writeFloatingPoint(12, s.z);
   o.writeFloatingPoint(13, s.angle);
   o.writeEnum(14, s.anim);
    o.writeUnsignedVarInt(15, s.flag);
   o.writeString(16, s.desc);
}



  
// DESERIALIZATION
bool deserializeItem( Item& s, IStream& i ) {
   int type;
   int fieldNumber;
   bool readret;
   std::bitset<1> initFlags;
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

   return initFlags.all();
}

bool deserializeCharacter( Character& s, IStream& i ) {
   int type;
   int fieldNumber;
   bool readret;
   std::bitset<16> initFlags;
   do
   {
      readret = i.readFieldTypeAndID( type, fieldNumber );
	  if ( !readret )
		  break;
	  switch ( fieldNumber )
	  {
		case 1:
		{
      initFlags[0] = i.readUnsignedVarInt( s.max_u8 );
			break;
		}
		case 2:
		{
      initFlags[1] = i.readUnsignedVarInt( s.max_u16 );
			break;
		}
		case 3:
		{
      initFlags[2] = i.readUnsignedVarInt( s.max_u32 );
			break;
		}
		case 4:
		{
      initFlags[3] = i.readSignedVarInt( s.min_s8 );
			break;
		}
		case 5:
		{
      initFlags[4] = i.readSignedVarInt( s.min_s16 );
			break;
		}
		case 6:
		{
      initFlags[5] = i.readSignedVarInt( s.min_s32 );
			break;
		}
		case 7:
		{
      initFlags[6] = i.readSignedVarInt( s.max_s8 );
			break;
		}
		case 8:
		{
      initFlags[7] = i.readSignedVarInt( s.max_s16 );
			break;
		}
		case 9:
		{
      initFlags[8] = i.readSignedVarInt( s.max_s32 );
			break;
		}
		case 10:
		{
      initFlags[9] = i.readFloatingPoint( s.x );

			break;
		}
		case 11:
		{
      initFlags[10] = i.readFloatingPoint( s.y );

			break;
		}
		case 12:
		{
      initFlags[11] = i.readFloatingPoint( s.z );

			break;
		}
		case 13:
		{
      initFlags[12] = i.readFloatingPoint( s.angle );

			break;
		}
		case 14:
		{
  		initFlags[13] = i.readEnum( s.anim );
			break;
		}
		case 15:
		{
      initFlags[14] = i.readUnsignedVarInt( s.flag );
			break;
		}
		case 16:
		{
     initFlags[15] = i.readString( s.desc );
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

   return initFlags.all();
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
    cout << "angle: ";
	cout << 
   s.angle 
	  ;
    cout << endl;
    cout << "anim: ";
	cout << 
   s.anim 
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



