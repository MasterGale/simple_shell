#include "shell.h"

/**
 * _erratoi - converts a string to an integer
 * @f: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */
int _erratoi(char *f)
{
	int j = 0;
	unsigned long int result = 0;

	if (*f == '+')
		f++;  /* TODO: why does this make main return 255? */
	for (j = 0;  f[j] != '\0'; j++)
	{
		if (f[j] >= '0' && f[j] <= '9')
		{
			result *= 10;
			result += (f[j] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * print_error - prints an error message
 * @inf: the parameter & return inf struct
 * @esti: string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void print_error(info_t *inf, char *esti)
{
	_eputs(inf->fname);
	_eputs(": ");
	print_d(inf->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(inf->argv[0]);
	_eputs(": ");
	_eputs(esti);
}

/**
 * print_d - function prints a decimal (integer) number (base 10)
 * @inp: the input
 * @fdi: the filedescriptor to write to
 *
 * Return: number of characters printed
 */
int print_d(int inp, int fdi)
{
	int (*__putchar)(char) = _putchar;
	int j, count = 0;
	unsigned int _abs_, current;

	if (fdi == STDERR_FILENO)
		__putchar = _eputchar;
	if (inp < 0)
	{
		_abs_ = -inp;
		__putchar('-');
		count++;
	}
	else
		_abs_ = inp;
	current = _abs_;
	for (j = 1000000000; j > 1; j /= 10)
	{
		if (_abs_ / j)
		{
			__putchar('0' + current / j);
			count++;
		}
		current %= j;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * convert_number - converter function, a clone of itoa
 * @numb: number
 * @base: base
 * @flag: argument flag
 *
 * Return: string
 */
char *convert_number(long int numb, int base, int flag)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long a = numb;

	if (!(flag & CONVERT_UNSIGNED) && numb < 0)
	{
		a = -numb;
		sign = '-';

	}
	array = flag & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[a % base];
		a /= base;
	} while (a != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * remove_comments - function replaces first instance of '#' with '\0'
 * @buf: address of the string to modify
 *
 * Return: Always 0;
 */
void remove_comments(char *buf)
{
	int j;

	for (j = 0; buf[j] != '\0'; j++)
		if (buf[j] == '#' && (!j || buf[j - 1] == ' '))
		{
			buf[j] = '\0';
			break;
		}
}
