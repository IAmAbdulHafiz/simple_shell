#include "shell.h"

#define MAX_PATH_LENGTH 1024

/**
 * Frees a pointer and NULLs the address.
 * @param pointer: Address of the pointer to free.
 * @return: 1 if freed, otherwise 0.
 */
int freePointer(void **pointer) {
    if (pointer && *pointer) {
        free(*pointer);
        *pointer = NULL;
        return 1;
    }
    return 0;
}

/**
 * Checks if a file is an executable command.
 * @param infoStruct: The info struct.
 * @param filePath: Path to the file.
 * @return: 1 if true, 0 otherwise.
 */
int isExecutable(info_t *infoStruct, char *filePath) {
    struct stat fileStats;
    (void)infoStruct;
    if (!filePath || stat(filePath, &fileStats))
        return 0;

    return (fileStats.st_mode & S_IFREG) ? 1 : 0;
}

/**
 * Duplicates characters from a string within a specified range.
 * @param sourceString: The source string.
 * @param startIndex: Starting index.
 * @param stopIndex: Stopping index.
 * @return: A newly allocated buffer containing the duplicated characters.
 */
char *duplicateCharacters(char *sourceString, int startIndex, int stopIndex) {
	int bufferIndex;
    char *buffer = malloc(MAX_PATH_LENGTH);

    if (!buffer) {
        return NULL;
    }

    bufferIndex = 0;
    for (int i = startIndex; i < stopIndex; i++) {
        if (sourceString[i] != ':') {
            buffer[bufferIndex++] = sourceString[i];
        }
    }

    buffer[bufferIndex] = '\0';
    return buffer;
}

/**
 * Finds the full path of a command in the PATH string.
 * @param infoStruct: The info struct.
 * @param pathString: The PATH string.
 * @param commandName: The command to find.
 * @return: The full path of the command if found, otherwise NULL.
 */
char *findCommandPath(info_t *infoStruct, char *pathString, char *commandName) {
    int currentIndex = 0;
    int currentPosition = 0;
    char *path;

    if (!pathString)
        return NULL;

    if ((_strlen(commandName) > 2) && starts_with(commandName, "./")) {
        if (isExecutable(infoStruct, commandName)) {
            return commandName;
        }
    }

    while (1) {
        if (!pathString[currentIndex] || pathString[currentIndex] == ':') {
            path = duplicateCharacters(pathString, currentPosition, currentIndex);

            if (!*path) {
                _strcat(path, commandName);
            } else {
                _strcat(path, "/");
                _strcat(path, commandName);
            }

            if (isExecutable(infoStruct, path)) {
                return path;
            }

            if (!pathString[currentIndex]) {
                break;
            }

            currentPosition = currentIndex;
        }
        currentIndex++;
    }

    return NULL;
}

