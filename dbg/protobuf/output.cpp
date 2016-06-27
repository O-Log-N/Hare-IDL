#include "output.h"
#include "sample.h"

// IMPLEMENTATIONS

// SERIALIZATION

void serializeItem( Item& s, OStream& o ) {
   o.writeString(1, s.name);
}

void serializeCharacter( Character& s, OStream& o ) {
   o.writeInt(1, s.character_id);
   o.writeDouble(2, s.x);
   o.writeDouble(3, s.y);
   o.writeDouble(4, s.z);
   o.writeDouble(5, s.vx);
   o.writeDouble(6, s.vy);
   o.writeDouble(7, s.vz);
   o.writeDouble(8, s.angle);
   o.writeInt(9, s.anim);
   o.writeInt(10, s.animation_frame);
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
			if ( type == LENGTH_DELIMITED )
			{
				i.readString( s.name );
				initFlags[0] = 1;
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

bool deserializeCharacter( Character& s, IStream& i ) {
   int type;
   int fieldNumber;
   bool readret;
   const int memcnt = 10;
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
      if ( type == VARINT )
      {
        initFlags[0] = i.readUnsignedVarInt( s.character_id );
      }
			break;
		}
		case 2:
		{
      if ( type == FIXED_64_BIT )
      {
        initFlags[1] = i.readDouble( s.x );
      }

			break;
		}
		case 3:
		{
      if ( type == FIXED_64_BIT )
      {
        initFlags[2] = i.readDouble( s.y );
      }

			break;
		}
		case 4:
		{
      if ( type == FIXED_64_BIT )
      {
        initFlags[3] = i.readDouble( s.z );
      }

			break;
		}
		case 5:
		{
      if ( type == FIXED_64_BIT )
      {
        initFlags[4] = i.readDouble( s.vx );
      }

			break;
		}
		case 6:
		{
      if ( type == FIXED_64_BIT )
      {
        initFlags[5] = i.readDouble( s.vy );
      }

			break;
		}
		case 7:
		{
      if ( type == FIXED_64_BIT )
      {
        initFlags[6] = i.readDouble( s.vz );
      }

			break;
		}
		case 8:
		{
      if ( type == FIXED_64_BIT )
      {
        initFlags[7] = i.readDouble( s.angle );
      }

			break;
		}
		case 9:
		{
			if ( type == VARINT )
			{
				initFlags[8] = i.readEnum( s.anim );
			}
			break;
		}
		case 10:
		{
      if ( type == VARINT )
      {
        initFlags[9] = i.readUnsignedVarInt( s.animation_frame );
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
void printItem( Item& s ) {
    cout << "name: ";
	cout << 
   s.name 
	  ;
    cout << endl;
}

void printCharacter( Character& s ) {
    cout << "character_id: ";
	cout << 
   s.character_id 
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
    cout << "vx: ";
	cout << 
   s.vx 
	  ;
    cout << endl;
    cout << "vy: ";
	cout << 
   s.vy 
	  ;
    cout << endl;
    cout << "vz: ";
	cout << 
   s.vz 
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
    cout << "animation_frame: ";
	cout << 
   s.animation_frame 
	  ;
    cout << endl;
}



