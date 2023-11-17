#include "shell.h"

/**
 * _custom_memset - fills memory with a constant byte
 * @buffer: pointer to the memory area
 * @value: the byte to fill buffer with
 * @size: the number of bytes to be filled
 * Return: a pointer to the memory area buffer
 */
char *_custom_memset(char *buffer, char value, unsigned int size)
{
    unsigned int i;

    for (i = 0; i < size; i++)
        buffer[i] = value;
    return buffer;
}

/**
 * free_string_array - frees an array of strings
 * @str_array: array of strings
 */
void free_string_array(char **str_array)
{
    char **temp = str_array;

    if (!str_array)
        return;
    while (*str_array)
        free(*str_array++);
    free(temp);
}

/**
 * custom_realloc - reallocates a block of memory
 * @ptr: pointer to the previous dynamically allocated block
 * @old_size: byte size of the previous block
 * @new_size: byte size of the new block
 * Return: pointer to the reallocated block
 */
void *custom_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
    char *new_ptr;

    if (!ptr)
        return malloc(new_size);

    if (!new_size)
        return free(ptr), NULL;

    if (new_size == old_size)
        return ptr;

    new_ptr = malloc(new_size);
    if (!new_ptr)
        return NULL;

    old_size = (old_size < new_size) ? old_size : new_size;
    while (old_size--)
        new_ptr[old_size] = ((char *)ptr)[old_size];

    free(ptr);
    return new_ptr;
}
