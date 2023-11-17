#include "shell.h"

/**
 * splitString - splits a string into words. Repeat delimiters are ignored
 * @inputStr: the input string
 * @delimiterStr: the delimiter string
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **splitString(char *inputStr, char *delimiterStr)
{
    int i, j, k, m, numWords = 0;
    char **resultArray;

    if (inputStr == NULL || inputStr[0] == 0)
        return NULL;
    if (!delimiterStr)
        delimiterStr = " ";

    for (i = 0; inputStr[i] != '\0'; i++)
        if (!isDelimiter(inputStr[i], delimiterStr) && (isDelimiter(inputStr[i + 1], delimiterStr) || !inputStr[i + 1]))
            numWords++;

    if (numWords == 0)
        return NULL;

    resultArray = malloc((1 + numWords) * sizeof(char *));
    if (!resultArray)
        return NULL;

    for (i = 0, j = 0; j < numWords; j++)
    {
        while (isDelimiter(inputStr[i], delimiterStr))
            i++;

        k = 0;
        while (!isDelimiter(inputStr[i + k], delimiterStr) && inputStr[i + k])
            k++;

        resultArray[j] = malloc((k + 1) * sizeof(char));
        if (!resultArray[j])
        {
            for (k = 0; k < j; k++)
                free(resultArray[k]);
            free(resultArray);
            return NULL;
        }

        for (m = 0; m < k; m++)
            resultArray[j][m] = inputStr[i++];
        resultArray[j][m] = 0;
    }

    resultArray[j] = NULL;
    return resultArray;
}

/**
 * splitString2 - splits a string into words
 * @inputStr: the input string
 * @delimiter: the delimiter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **splitString2(char *inputStr, char delimiter)
{
    int i, j, k, m, numWords = 0;
    char **resultArray;

    if (inputStr == NULL || inputStr[0] == 0)
        return NULL;

    for (i = 0; inputStr[i] != '\0'; i++)
        if ((inputStr[i] != delimiter && inputStr[i + 1] == delimiter) ||
            (inputStr[i] != delimiter && !inputStr[i + 1]) || inputStr[i + 1] == delimiter)
            numWords++;

    if (numWords == 0)
        return NULL;

    resultArray = malloc((1 + numWords) * sizeof(char *));
    if (!resultArray)
        return NULL;

    for (i = 0, j = 0; j < numWords; j++)
    {
        while (inputStr[i] == delimiter && inputStr[i] != delimiter)
            i++;

        k = 0;
        while (inputStr[i + k] != delimiter && inputStr[i + k] && inputStr[i + k] != delimiter)
            k++;

        resultArray[j] = malloc((k + 1) * sizeof(char));
        if (!resultArray[j])
        {
            for (k = 0; k < j; k++)
                free(resultArray[k]);
            free(resultArray);
            return NULL;
        }

        for (m = 0; m < k; m++)
            resultArray[j][m] = inputStr[i++];
        resultArray[j][m] = 0;
    }

    resultArray[j] = NULL;
    return resultArray;
}
