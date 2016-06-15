#include "directory.h"

int checkDirectory(const char title[])
{
	struct stat st = {.st_mode = 0};
	if (stat(title, &st) == -1)
	{
		printf("\"%s\" Directory Not Exists\n", title);
		return DIRECTORY_NOT_EXIST;
	}
	else
	{
		printf("\"%s\" Directory Exists\n", title);
		return DIRECTORY_EXIST;
	}
}

int createDirectory(const char title[])
{
	int status = mkdir(title, 0700);
	if (status == -1)
	{
		fputs("mkdir Failed\n", stderr);
		return DIRECTORY_CREATION_FAILURE;
	}
	else
	{
		puts("mkdir Succeeded");
		return DIRECTORY_CREATION_SUCCESS;
	}
}
