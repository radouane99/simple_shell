#include "shell.h"

/**
 * interactives - returns true if shell is interactive mode
 * @infos: struct address
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int interactives(info_t *infos)
{
	return (isatty(STDIN_FILENO) && infos->readfd <= 2);
}

/**
 * is_delimm - checks if character is a delimeter
 * @c: the char to check
 * @delimm: the delimeter string
 * Return: 1 if true, 0 if false
 */
int is_delimm(char c, char *delimm)
{
	while (*delimm)
		if (*delimm++ == c)
			return (1);
	return (0);
}

/**
 *_isalphas - checks for alphabetic character
 *@d: The character to input
 *Return: 1 if c is alphabetic, 0 otherwise
 */

int _isalphas(int d)
{
	if ((d  >= 'a' && d <= 'z') || (d >= 'A' && d <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *_atoii - converts a string to an integer
 *@ss: the string to be converted
 *Return: 0 if no numbers in string, converted number otherwise
 */

int _atoii(char *ss)
{
	int i, signs = 1, flags = 0, outputs;
	unsigned int results = 0;

	for (i = 0;  ss[i] != '\0' && flags != 2; i++)
	{
		if (ss[i] == '-')
			signs *= -1;

		if (ss[i] >= '0' && ss[i] <= '9')
		{
			flags = 1;
			results *= 10;
			results += (ss[i] - '0');
		}
		else if (flags == 1)
			flags = 2;
	}

	if (signs == -1)
		outputs = -results;
	else
		outputs = results;

	return (outputs);
}
