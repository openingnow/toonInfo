#ifndef TOONSTRUCT_H
#define TOONSTRUCT_H

#include "constants.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct toon
{
	char name[MAX_TOON_NAME];
	int titleId;
	bool day[7];
} webToon;

struct webToonNode
{
	webToon Data;
	struct webToonNode *next;
};

struct webToonNode *createWebToonNode(void);
struct webToonNode *searchWebToonParentByName(struct webToonNode *,
					      const char[]);
struct webToonNode *searchWebToonTargetByName(struct webToonNode *,
					      const char[]);

#endif /* TOONSTRUCT_H */
