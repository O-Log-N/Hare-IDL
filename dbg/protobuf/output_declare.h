
#ifndef OUTPUT_DECLARE_H_INCLUDED
#define OUTPUT_DECLARE_H_INCLUDED

//include-here
#include <string>
#include <vector>

// DECLARATIONS
struct BasicTypes;

struct BasicTypes {
  uint32_t max_u32;
  uint64_t max_u64;
  int32_t max_s32;
  int64_t max_s64;
  float aFloat;
  double aDouble;
  string description;
  enum Values {
      First=1,
      Nothing=0,
      Second=2,
  } aValue;
  bool flag;
};

  
#endif // OUTPUT_DECLARE_H_INCLUDED

