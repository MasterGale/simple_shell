#include "shell.h"

/**
 * **strtow - splits a string into words. Repeat delimiters are ignored
 * @asd: the input string
 * @e: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **strtow(char *asd, char *e)
{
	int a, b, c, d, numwords = 0;
	char **s;

	if (asd == NULL || asd[0] == 0)
		return (NULL);
	if (!e)
		e = " ";
	for (a = 0; asd[a] != '\0'; a++)
		if (!is_delim(asd[a], e) && (is_delim(asd[a + 1], e) || !asd[a + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (a = 0, b = 0; b < numwords; b++)
	{
		while (is_delim(asd[a], e))
			a++;
		c = 0;
		while (!is_delim(asd[a + c], e) && asd[a + c])
			c++;
		s[b] = malloc((c + 1) * sizeof(char));
		if (!s[b])
		{
			for (c = 0; c < b; c++)
				free(s[c]);
			free(s);
			return (NULL);
		}
		for (d = 0; d < c; d++)
			s[b][d] = asd[a++];
		s[b][d] = 0;
	}
	s[b] = NULL;
	return (s);
}

/**
 * **strtow2 - splits a string into words
 * @asd: the input string
 * @e: the delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **strtow2(char *asd, char e)
{
	int a, b, c, d, numwords = 0;
	char **s;

	if (asd == NULL || asd[0] == 0)
		return (NULL);
	for (a = 0; asd[a] != '\0'; a++)
		if ((asd[a] != e && asd[a + 1] == e) ||
		    (asd[a] != e && !asd[a + 1]) || asd[a + 1] == e)
			numwords++;
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (a = 0, b = 0; b < numwords; b++)
	{
		while (asd[a] == e && asd[a] != e)
			a++;
		c = 0;
		while (asd[a + c] != e && asd[a + c] && asd[a + c] != e)
			c++;
		s[b] = malloc((c + 1) * sizeof(char));
		if (!s[b])
		{
			for (c = 0; c < b; c++)
				free(s[c]);
			free(s);
			return (NULL);
		}
		for (d = 0; d < c; d++)
			s[b][d] = asd[a++];
		s[b][d] = 0;
	}
	s[b] = NULL;
	return (s);
}
