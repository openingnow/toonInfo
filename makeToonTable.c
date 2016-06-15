#include "makeToonTable.h"

static char dayTable[7][4] = {"mon", "tue", "wed", "thu", "fri", "sat", "sun"};

static int getDay(char day[])
{
	for (int i = 0; i < 7; i++)
	{
		if (strcmp(day, dayTable[i]) == 0)
			return i;
	}
	fprintf(stderr, "Day error\n");
	exit(EXIT_FAILURE);
}

static void fillString(char dest[], int j, int nulPos, const char *p,
		       regmatch_t m[])
{
	strncpy(dest, m[j].rm_so + p, (m[j].rm_eo - m[j].rm_so));
	dest[nulPos] = '\0';
}

static void linkNode(struct webToonNode *head, int titleId, int day,
		     char toonName[])
{
	struct webToonNode *parent = searchWebToonParentByName(head, toonName);
	struct webToonNode *targetNode = parent->next;

	if (targetNode == NULL) // new WebToon
	{
		targetNode = createWebToonNode();
		parent->next = targetNode;
		targetNode->Data.day[day] = true;
		targetNode->Data.titleId = titleId;
		strcpy(targetNode->Data.name, toonName);
	}
	else
	{
		if (targetNode->Data.day[day] == true)
		{
			fprintf(stderr, "WebToon Duplication Error\n");
			exit(EXIT_FAILURE);
		}
		targetNode->Data.day[day] = true;
	}
}

void makeToonTable(struct webToonNode *head)
{
	fillmemchunk(tableChunkURL); /* fillMemChunk.c */

	/* RegexOperation.c */
	compileRegex(tableRegexString);

	regmatch_t m[MAX_TOON_COUNT][TABLE_MATCH_ARGS_COUNT];
	int toonCount = MAX_TOON_COUNT;
	const char *p = matchRegex(TABLE_MATCH_ARGS_COUNT, &toonCount, m);
	if (p == NULL)
	{
		fprintf(stderr, "Not Enough WebToonCount\n");
		exit(EXIT_FAILURE);
	}
	printf("Found %d webtoons(include duplicate)\n", toonCount);
	char toonName[MAX_TOON_NAME];
	char toonName2[MAX_TOON_NAME];
	char titleIdChar[toonIdLength + 1];
	char dayChar[4];
	int titleId;
	for (int i = 0; i < toonCount; p += m[i][0].rm_eo, i++)
	{
		// j : 1 titleId 2 day 3 4 name
		// fillString(dest[], int j, nulPos, p, m)
		fillString(titleIdChar, 1, toonIdLength, p, m[i]);
		titleId = atoi(titleIdChar);
		fillString(dayChar, 2, 3, p, m[i]);
		fillString(toonName, 3, m[i][3].rm_eo - m[i][3].rm_so, p, m[i]);
		fillString(toonName2, 4, m[i][4].rm_eo - m[i][4].rm_so, p,
			   m[i]);

		if (strcmp(toonName, toonName2) != 0)
			fprintf(stderr, "Regex Error suspected\n");

		linkNode(head, titleId, getDay(dayChar), toonName);
	}
}
