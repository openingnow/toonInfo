#ifndef DIRECTORY_H
#define DIRECTORY_H

#include <stdio.h>
#include <sys/stat.h>

#define DIRECTORY_NOT_EXIST 0
#define DIRECTORY_EXIST 1
#define DIRECTORY_CREATION_FAILURE 0
#define DIRECTORY_CREATION_SUCCESS 1

int checkDirectory(const char[]);
int createDirectory(const char[]);

#endif /* DIRECTORY_H */
