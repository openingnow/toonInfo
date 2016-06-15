#include "toonInfo.h"

extern MemoryStruct chunk; /* regexOperation.c */

static char dayTable[7][4] = {"월", "화", "수", "목", "금", "토", "일"};

static void printDay(struct webToonNode *targetNode)
{
	for (int i = 0; i < 7; i++)
	{
		if (targetNode->Data.day[i] == true)
			printf(" %s", dayTable[i]);
	}
	printf("\n");
}

int main(int argc, const char *argv[])
{
	if (argc != 2)
	{
		fprintf(stderr, "Usage : %s toonname\n", argv[0]);
		return -1;
	}

	struct webToonNode head = {{"Dummy", -1, {0}}, NULL};

	makeToonTable(&head); /* makeToonTable.c */
	puts("Toon Table Creation Finished");

	struct webToonNode *targetNode =
		searchWebToonTargetByName(&head, argv[1]);
	if (targetNode == NULL)
	{
		fprintf(stderr, "WebToon '%s' Not Found\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	printf("WebToon '%s' Found\nUpdated at", argv[1]);
	printDay(targetNode);

	/* directory.c */
	// if (checkDirectory(argv[1]) == DIRECTORY_NOT_EXIST)
	// {
	// 	if (createDirectory(argv[1]) == DIRECTORY_CREATION_FAILURE)
	// 		exit(EXIT_FAILURE);
	// }
	return 0;
}
