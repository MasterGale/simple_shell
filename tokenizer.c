#include "shell.h"

/**
 * **strtow - splits a string into words. Repeat delimiters are ignored
 * @str: the input string
 * @d: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **strtow(char *str, char *d)
{
	int b, s, g, n, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (b = 0; str[b] != '\0'; b++)
		if (!is_delim(str[b], d) && (is_delim(str[b + 1], d) || !str[b + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (b = 0, s = 0; s < numwords; s++)
	{
		while (is_delim(str[b], d))
			b++;
		g = 0;
		while (!is_delim(str[b + g], d) && str[b + g])
			g++;
		s[s] = malloc((g + 1) * sizeof(char));
		if (!s[s])
		{
			for (g = 0; g < s; g++)
				free(s[g]);
			free(s);
			return (NULL);
		}
		for (n = 0; n < g; n++)
			s[s][n] = str[b++];
		s[s][n] = 0;
	}
	s[s] = NULL;
	return (s);
}

/**
 * **strtow2 - splits a string into words
 * @str: the input string
 * @d: the delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **strtow2(char *str, char d)
{
	int b, s, g, n, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (b = 0; str[b] != '\0'; b++)
		if ((str[b] != d && str[b + 1] == d) ||
		    (str[b] != d && !str[b + 1]) || str[b + 1] == d)
			numwords++;
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (b = 0, s = 0; s < numwords; s++)
	{
		while (str[b] == d && str[b] != d)
			b++;
		g = 0;
		while (str[b + g] != d && str[b + g] && str[b + g] != d)
			g++;
		s[s] = malloc((g + 1) * sizeof(char));
		if (!s[s])
		{
			for (g = 0; g < s; g++)
				free(s[g]);
			free(s);
			return (NULL);
		}
		for (n = 0; n < g; n++)
			s[s][n] = str[b++];
		s[s][n] = 0;
	}
	s[s] = NULL;
	return (s);
}
