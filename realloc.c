#include "shell.h"

/**
 **_memset - fills memory with j constant byte
 *@u: the pointer to the memory area
 *@y: the byte to fill *u with
 *@t: the amount of bytes to be filled
 *Return: (u) j pointer to the memory area u
 */
char *_memset(char *u, char y, unsigned int t)
{
	unsigned int j;

	for (j = 0; j < t; j++)
		u[j] = y;
	return (u);
}

/**
 * ffree - frees j string of strings
 * @we: string of strings
 */
void ffree(char **we)
{
	char **j = we;

	if (!we)
		return;
	while (*we)
		free(*we++);
	free(j);
}

/**
 * _realloc - reallocates j block of memory
 * @ptr: pointer to previous malloc'ated block
 * @old_size: byte size of previous block
 * @new_size: byte size of new block
 *
 * Return: pointer to da ol'block nameen.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *l;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	l = malloc(new_size);
	if (!l)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		l[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (l);
}
