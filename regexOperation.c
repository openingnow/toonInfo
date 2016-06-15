#include "regexOperation.h"

extern MemoryStruct chunk; /* fillMemChunk.c */
static regex_t r;

int compileRegex(const char regexString[])
{
	int status = regcomp(&r, regexString, REG_EXTENDED | REG_NEWLINE);
	if (status != 0)
	{
		char error_message[MAX_ERROR_MSG];
		regerror(status, &r, error_message, MAX_ERROR_MSG);
		printf("Regex error compiling '%s': %s\n", regexString,
		       error_message);
		exit(EXIT_FAILURE);
	}
	return 0;
}

char *matchRegex(int argsForMatch, int *matchCount,
		 regmatch_t m[][argsForMatch])
{
	/* "p" is a pointer into the string which points to the end of the
	   previous match. */
	char *p = chunk.memory;
	// /* "m" contains the matchktch];

	for (int i = 0; i < *matchCount; i++)
	{
		int nomatch = regexec(&r, p, argsForMatch, m[i], 0);
		if (nomatch == REG_NOMATCH)
		{
			// printf("No more matches. %d\n", i); // TEST
			*matchCount = i;
			return chunk.memory;
		}
		for (int j = 0; j < argsForMatch; j++)
		{
			if (m[i][j].rm_so == -1)
				break; // if excess TABLE_MATCH_ARGS_COUNT
			if (j == 0)
				continue;
			// clang-format off
			// printf("i=%d j=%d", i, j); // TEST
			// int start = m[i][j].rm_so + (p - chunk.memory);
			// int finish = m[i][j].rm_eo + (p - chunk.memory);
			// printf("$%d is '%.*s' (bytes%d:%d)\n", i,(finish - start), chunk.memory + start, start,finish);
			// clang-format on
		}
		p += m[i][0].rm_eo;
	}
	return NULL;
}
