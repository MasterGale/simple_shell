#include "shell.h"

/**
 **_strncpy - copies a string
 *@dst: the destination string to be copied to
 *@scr: the source string
 *@b: the amount of characters to be copied
 *Return: the concatenated string
 */
char *_strncpy(char *dst, char *scr, int b)
{
	int k, n;
	char *u = dst;

	k = 0;
	while (scr[k] != '\0' && k < b - 1)
	{
		dst[k] = scr[k];
		k++;
	}
	if (k < b)
	{
		n = k;
		while (n < b)
		{
			dst[n] = '\0';
			n++;
		}
	}
	return (u);
}

/**
 **_strncat - concatenates two strings
 *@dst: the first string
 *@scr: the second string
 *@b: the amount of bytes to be maximally used
 *Return: the concatenated string
 */
char *_strncat(char *dst, char *scr, int b)
{
	int k, n;
	char *u = dst;

	k = 0;
	n = 0;
	while (dst[k] != '\0')
		k++;
	while (scr[n] != '\0' && n < b)
	{
		dst[k] = scr[n];
		k++;
		n++;
	}
	if (n < b)
		dst[k] = '\0';
	return (u);
}

/**
 **_strchr - locates a character in a string
 *@u: the string to be parsed
 *@c: the character to look for
 *Return: (u) a pointer to the memory area u
 */
char *_strchr(char *u, char c)
{
	do {
		if (*u == c)
			return (u);
	} while (*u++ != '\0');

	return (NULL);
}
