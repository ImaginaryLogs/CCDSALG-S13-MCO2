#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h> // for pow()
#include "config.h"


// Include Guards to help prevent double inclusion collisions when the compiler's preprocessor links the files.
// Reference: [3]
#ifndef _UTILS_H_
#define _UTILS_H_


// Region to denote types defined at utils.h
// UTIL_DEFINED_TYPES


typedef char String639[640];
typedef char String511[512];
typedef char String255[256];
typedef char String127[128];
typedef char String63[64];
typedef char String31[32];
typedef char String7[8];
typedef char String2[3];

enum ParserState {
  TOKEN_NUMBER,
  TOKEN_OPERATION,
  END_OF_STRING
};

typedef struct DimensionTag {
    int width;
    int height;
} dimension;

typedef struct PositionTag {
    int x;
    int y;
} position;


#if DEBUG 
  /**
  * A developer's version of printf that is togglable - useful for debugging. 
  * @retval None
  */
  #define LOG(X, ...) \
    do {\
      typeof (X) _X = (X); \
      if (_X) \
        fprintf(stdout, __VA_ARGS__); } \
    while(0)
#else
  #define LOG(X, ...)
#endif

#endif