#include <ctype.h>
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

/**
 * Compares two strings case-insensitively.
 */
bool insensitiveStrCmp(char* str1, char* str2) {

  bool isEqual = true;
  int i;
  
  if (strlen(str1) != strlen(str2)) {
    isEqual = false;
  } else {
    for (i = 0; i < strlen(str1); i++) {
      if (tolower(str1[i]) != tolower(str2[i])) {
        isEqual = false;
      }
    }
  }

  return isEqual;
}

/**
 * Prints an array.
 */
void printArr(String31 arr[], int numElements, char message[]) {
  printf("%s\n", message);
  for (int i = 0; i < numElements; ++i) {
    printf("%s ", arr[i]);
  }
  printf("\n");
}

/**
 * Swaps the values of two strings.
 */
void swap(String31 str1, String31 str2) {
  String31 temp;
  strcpy(temp, str1);
  strcpy(str1, str2);
  strcpy(str2, temp);
}

/**
 * Sorts an array of strings in increasing or decreasing lexicographical order.
 */
void sortArr(String31 arr[], int numElements, bool sortInIncreasingOrder) {
  
  int i, j;

  printArr(arr, numElements, "Pre-sort:"); // testing

  if (sortInIncreasingOrder) { // increasing lexicographical order
    for (i = 0; i < numElements - 1; ++i) {
      for (j = i + 1; j < numElements; ++j) {
        if (strcmp(arr[j - 1], arr[j]) > 0) {
          swap(arr[j - 1], arr[j]);
        }
      }
    }
  } else { // decreasing lexicographical order
    for (i = numElements - 1; i >= 1; --i) {
      for (j = 0; j < i; ++j) {
        if (strcmp(arr[j], arr[j + 1]) < 0) {
          swap(arr[j], arr[j + 1]);
        }
      }
    }
  }

  printArr(arr, numElements, "Post-sort:"); // testing
}

#if DEBUG 
  /**
  * A developer's version of printf that is togglable - useful for debugging. 
  * @retval None
  */
  #define LOG(X, ...) do{typeof (X) _X = (X); if (_X) fprintf(stdout, __VA_ARGS__);} while(0)
#else
  #define LOG(X, ...)
#endif

#endif