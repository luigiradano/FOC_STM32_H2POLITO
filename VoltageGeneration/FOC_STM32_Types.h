#ifndef FOC_TYPE_INC
#define FOC_TYPE_INC

#include <stdint.h>

typedef struct {
  uint32_t a;
  uint32_t b;
  uint32_t c;
} abcData_uint32;

typedef struct {
  float a;
  float b;
  float c;
} abcData_f;

typedef struct {
  float alpha;
  float beta;
} alphaBetaData_f;

#endif
