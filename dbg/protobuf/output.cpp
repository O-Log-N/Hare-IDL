#include "output.h"

#include <bitset>
#include "sample.h"

// IMPLEMENTATIONS

// SERIALIZATION

void serializeItem( Item& s, OStream& o ) {
   o.writeString(1, s.name);
}

void serializeCharacter( Character& s, OStream& o ) {
    o.writeUnsignedVarInt(1, s.idU8);
    o.writeUnsignedVarInt(2, s.idU16);
    o.writeUnsignedVarInt(3, s.idU32);
   o.writeFloatingPoint(4, s.x);
   o.writeFloatingPoint(5, s.y);
   o.writeFloatingPoint(6, s.z);
   o.writeFloatingPoint(7, s.angle);
   o.writeEnum(8, s.anim);
    o.writeUnsignedVarInt(9, s.flag);
   o.writeString(10, s.desc);
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
   std::bitset<10> initFlags;
   do
   {
      readret = i.readFieldTypeAndID( type, fieldNumber );
	  if ( !readret )
		  break;
	  switch ( fieldNumber )
	  {
		case 1:
		{
      initFlags[0] = i.readUnsignedVarInt( s.idU8 );
			break;
		}
		case 2:
		{
      initFlags[1] = i.readUnsignedVarInt( s.idU16 );
			break;
		}
		case 3:
		{
      initFlags[2] = i.readUnsignedVarInt( s.idU32 );
			break;
		}
		case 4:
		{
      initFlags[3] = i.readFloatingPoint( s.x );

			break;
		}
		case 5:
		{
      initFlags[4] = i.readFloatingPoint( s.y );

			break;
		}
		case 6:
		{
      initFlags[5] = i.readFloatingPoint( s.z );

			break;
		}
		case 7:
		{
      initFlags[6] = i.readFloatingPoint( s.angle );

			break;
		}
		case 8:
		{
  		initFlags[7] = i.readEnum( s.anim );
			break;
		}
		case 9:
		{
      initFlags[8] = i.readUnsignedVarInt( s.flag );
			break;
		}
		case 10:
		{
     initFlags[9] = i.readString( s.desc );
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
    cout << "idU8: ";
	cout << 
   s.idU8 
	  ;
    cout << endl;
    cout << "idU16: ";
	cout << 
   s.idU16 
	  ;
    cout << endl;
    cout << "idU32: ";
	cout << 
   s.idU32 
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



