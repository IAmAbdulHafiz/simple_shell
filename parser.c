#include "shell.h"

#define MAX_PATH_LENGTH 1024

/**
 * freePointer - Frees a pointer and NULLs the address.
 * @pointer: Address of the pointer to free.
 * Return: 1 if freed, otherwise 0.
 */
int freePointer(void **pointer)
{
	if (pointer && *pointer)
	{
		free(*pointer);
		*pointer = NULL;
		return (1);
	}
	return (0);
}

/**
 * isExc - Checks if a file is an executable command.
 * @infoStruct: The info struct.
 * @filePath: Path to the file.
 * Return: 1 if true, 0 otherwise.
 */

int isExc(info_t *infoStruct, char *filePath)
{
	struct stat fileStats;

	(void)infoStruct;
	if (!filePath || stat(filePath, &fileStats))
		return (0);
	return ((fileStats.st_mode & S_IFREG) ? 1 : 0);
}

/**
 * *dupChar - characters from a string within a specified range.
 * @sourceString: The source string.
 * @startIndex: Starting index.
 * @stopIndex: Stopping index.
 * Return: A newly allocated buffer containing the duplicated characters.
 */

char *dupChar(char *sourceString, int startIndex, int stopIndex)
{
	int i = 0, bufIndex = 0;
	static char buffer[1024];

	for (bufIndex = 0, i = startIndex; i < stopIndex; i++)
		if (sourceString[i] != ':')
			buffer[bufIndex++] = sourceString[i];
	buffer[bufIndex] = 0;
	return (buffer);
}

/**
 * findCommandPath - Finds the full path of a command in the PATH string.
 * @infoStruct: The info struct.
 * @pathString: The PATH string.
 * @cmd_n: The command to find.
 * Return: The full path of the command if found, otherwise NULL.
 */

char *findCommandPath(info_t *infoStruct, char *pathString, char *cmd_n)
{
	int currentIndex = 0;
	int currentPosition = 0;
	char *path;

	if (!pathString)
		return (NULL);
	if ((custom_strlen(cmd_n) > 2) && custom_starts_with(cmd_n, "./"))
	{
		if (isExc(infoStruct, cmd_n))
		{
			return (cmd_n);
		}
	}
	while (1)
	{
		if (!pathString[currentIndex] || pathString[currentIndex] == ':')
		{
			path = dupChar(pathString, currentPosition, currentIndex);
			if (!*path)
			{
				custom_strcat(path, cmd_n);
			}
			else
			{
				custom_strcat(path, "/");
				custom_strcat(path, cmd_n);
			}
			if (isExc(infoStruct, path))
			{
				return (path);
			}
			if (!pathString[currentIndex])
			{
				break;
			}
			currentPosition = currentIndex;
		}
		currentIndex++;
	}
	return (NULL);
}
