#include "toonStruct.h"

struct webToonNode *createWebToonNode(void)
{
	struct webToonNode *newWebToonNode = malloc(sizeof(struct webToonNode));
	if (newWebToonNode == NULL)
	{
		fprintf(stderr, "newWebToonNode Creation Failed\n");
		exit(EXIT_FAILURE);
	}
	*newWebToonNode = (struct webToonNode){{"init", -1, {0}}, NULL};

	return newWebToonNode;
}

void deleteWebToonByParent(struct webToonNode *parent)
{
	struct webToonNode *webToonToBeDeleted = parent->next;

	parent->next = webToonToBeDeleted->next;
	free(webToonToBeDeleted);
}

struct webToonNode *searchWebToonParentByName(struct webToonNode *head,
					      const char name[])
{
	struct webToonNode *prev = head;
	struct webToonNode *curr = prev->next;

	for (; curr != NULL && strcmp(curr->Data.name, name) != 0;
	     prev = curr, curr = curr->next)
		;

	return prev;
}
// head if empty
// parent if found
// last if not found

struct webToonNode *searchWebToonTargetByName(struct webToonNode *head,
					      const char name[])
{
	return searchWebToonParentByName(head, name)->next;
}
// segfault if empty
// target if found
// NULL if not found
