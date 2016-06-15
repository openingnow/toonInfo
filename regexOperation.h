#ifndef REGEXOPERATION_H
#define REGEXOPERATION_H

/* The following is the size of a buffer to contain any error messages
   encountered when the regular expression is compiled. */
#define MAX_ERROR_MSG 0x1000

#include "fillMemChunk.h"

#include <regex.h>

int compileRegex(const char[]);
char *matchRegex(int, int *, regmatch_t[][*]);
/* "m" contains the matches found. */

#endif /* REGEXOPERATION_H */
