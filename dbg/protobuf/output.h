
#ifndef OUTPUT_H_INCLUDED
#define OUTPUT_H_INCLUDED

#include "sample.h"
#include <string>
#include <vector>
#include <deque>
//TODO remove
//#include "protobuf/baselib.h"

class OProtobufStream;
class IProtobufStream;


// declarations
  // internal use functions
void protobufSerializeBasicTypes( const BasicTypes& s, OProtobufStream& o, std::deque<size_t>& stk );
size_t protobufGetSizeBasicTypes( const BasicTypes& s, std::deque<size_t>& stk );
bool protobufDeserializeBasicTypes( BasicTypes& s, IProtobufStream& i, size_t eos );

  // public API
size_t serializeBasicTypes( const BasicTypes& s, OProtobufStream& o );
inline
bool deserializeBasicTypes( BasicTypes& s, IProtobufStream& i ) {
  return protobufDeserializeBasicTypes( s, i, SIZE_MAX );
}


#endif // OUTPUT_H_INCLUDED

