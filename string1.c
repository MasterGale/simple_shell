#include "shell.h"

/**
 * _strcpy - copies a string
 * @des: the destination
 * @sc: the source
 *
 * Return: pointer to destination
 */
char *_strcpy(char *des, char *sc)
{
	int d = 0;

	if (des == sc || sc == 0)
		return (des);
	while (sc[d])
	{
		des[d] = sc[d];
		d++;
	}
	des[d] = 0;
	return (des);
}

/**
 * _strdup - duplicates a string
 * @st: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *_strdup(const char *st)
{
	int length = 0;
	char *ret;

	if (st == NULL)
		return (NULL);
	while (*st++)
		length++;
	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);
	for (length++; length--;)
		ret[length] = *--st;
	return (ret);
}

/**
 *_puts - prints an input string
 *@st: the string to be printed
 *
 * Return: Nothing
 */
void _puts(char *st)
{
	int d = 0;

	if (!st)
		return;
	while (st[d] != '\0')
	{
		_putchar(st[d]);
		d++;
	}
}

/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
	static int d;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || d >= WRITE_BUF_SIZE)
	{
		write(1, buf, d);
		d = 0;
	}
	if (c != BUF_FLUSH)
		buf[d++] = c;
	return (1);
}
