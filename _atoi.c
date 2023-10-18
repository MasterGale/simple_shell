#include "shell.h"

/**
 * interactive - returns true if shell is interactive mode
 * @inf: struct address
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int interactive(info_t *inf)
{
	return (isatty(STDIN_FILENO) && inf->readfd <= 2);
}

/**
 * is_delim - checks if character is a delimeter
 * @j: the char to check
 * @deli: the delimeter string
 * Return: 1 if true, 0 if false
 */
int is_delim(char j, char *deli)
{
	while (*deli)
		if (*deli++ == j)
			return (1);
	return (0);
}

/**
 *_isalpha - checks for alphabetic character
 *@j: The character to input
 *Return: 1 if j is alphabetic, 0 otherwise
 */

int _isalpha(int j)
{
	if ((j >= 'a' && j <= 'z') || (j >= 'A' && j <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *_atoi - converts a string to an integer
 *@b: the string to be converted
 *Return: 0 if no numbers in string, converted number otherwise
 */
int _atoi(char *b)
{
	int m, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (m = 0;  b[m] != '\0' && flag != 2; m++)
	{
		if (b[m] == '-')
			sign *= -1;

		if (b[m] >= '0' && b[m] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (b[m] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
