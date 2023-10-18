#include "shell.h"

/**
 * _erratois - converts a string to an integer
 * @s: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */
int _erratois(char *s)
{
	int i = 0;
	unsigned long int results = 0;

	if (*s == '+')
		s++;  /* TODO: why does this make main return 255? */
	for (i = 0;  s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			results *= 10;
			results += (s[i] - '0');
			if (results > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (results);
}

/**
 * print_errors - prints an error messages
 * @infos: the parameter & return infos struct
 * @estr: string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwises
 *        -1 on error
 */
void print_errors(info_t *infos, char *estr)
{
	_eputs(infos->fname);
	_eputs(": ");
	print_d(infos->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(infos->argv[0]);
	_eputs(": ");
	_eputs(estr);
}

/**
 * print_d - function prints a decimal (integer) number (base 10)
 * @inputs: the input
 * @fd: the filedescriptor to write to
 *
 * Return: number of characters printed
 */
int print_d(int inputs, int fd)
{
	int (*__putchar)(char) = _putchar;
	int i, counts = 0;
	unsigned int _abs, currents;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (inputs < 0)
	{
		_abs = -inputs;
		__putchar('-');
		counts++;
	}
	else
		_abs = inputs;
	currents = _abs;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs / i)
		{
			__putchar('0' + currents / i);
			counts++;
		}
		currents %= i;
	}
	__putchar('0' + currents);
	counts++;

	return (counts);
}

/**
 * convert_numbers - converter function, a clone of itoa
 * @numm: number
 * @base: base
 * @flags: argument flags
 *
 * Return: string
 */
char *convert_numbers(long int numm, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char signs = 0;
	char *ptrs;
	unsigned long n = numm;

	if (!(flags & CONVERT_UNSIGNED) && numm < 0)
	{
		n = -numm;
		signs = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptrs = &buffer[49];
	*ptrs = '\0';

	do	{
		*--ptrs = array[n % base];
		n /= base;
	} while (n != 0);

	if (signs)
		*--ptrs = signs;
	return (ptrs);
}

/**
 * remove_comment - function replaces first instance of '#' with '\0'
 * @buff: address of the string to modify
 *
 * Return: Always 0;
 */
void remove_comment(char *buff)
{
int i;
for (i = 0; buff[i] != '\0'; i++)
if (buff[i] == '#' && (!i || buff[i - 1] == ' '))
{
buff[i] = '\0';
break;
}
}
