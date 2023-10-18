#include "shell.h"

/**
 * _strlen - returns the length of a string
 * @b: the string whose length to check
 *
 * Return: integer length of string
 */
int _strlen(char *b)
{
	int v = 0;

	if (!b)
		return (0);

	while (*b++)
		v++;
	return (v);
}

/**
 * _strcmp - performs lexicogarphic comparison of two strangs.
 * @m1: the first strang
 * @m2: the second strang
 *
 * Return: negative if m1 < m2, positive if m1 > m2, zero if m1 == m2
 */
int _strcmp(char *m1, char *m2)
{
	while (*m1 && *m2)
	{
		if (*m1 != *m2)
			return (*m1 - *m2);
		m1++;
		m2++;
	}
	if (*m1 == *m2)
		return (0);
	else
		return (*m1 < *m2 ? -1 : 1);
}

/**
 * starts_with - checks if needle starts with haystack
 * @haystack: string to search
 * @needle: the substring to find
 *
 * Return: address of next char of haystack or NULL
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _strcat - concatenates two strings
 * @dest: the destination buffer
 * @src: the source buffer
 *
 * Return: pointer to destination buffer
 */
char *_strcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}
