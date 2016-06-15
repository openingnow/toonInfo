#ifndef FILLMEMCHUNK_H
#define FILLMEMCHUNK_H

#include "constants.h"

#include <curl/curl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void fillmemchunk(const char[]);

typedef struct MemoryStruct
{
	char *memory;
	size_t size;
} MemoryStruct;

#endif /* FILLMEMCHUNK_H */
