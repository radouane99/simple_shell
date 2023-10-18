#include "shell.h"

/**
 *_e_puts - prints an input string
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void _e_puts(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_e_putchar(str[i]);
		i++;
	}
}

/**
 * _e_putchar - writes the character c to stderr
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _e_putchar(char c)
{
	static int i;
	static char buff[WRITE_buff_SIZE];

	if (c == buff_FLUSH || i >= WRITE_buff_SIZE)
	{
		write(2, buff, i);
		i = 0;
	}
	if (c != buff_FLUSH)
		buff[i++] = c;
	return (1);
}

/**
 * _putf_d - writes the character c to given fd
 * @c: The character to print
 * @fd: The filedescriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putf_d(char c, int fd)
{
	static int i;
	static char buff[WRITE_buff_SIZE];

	if (c == buff_FLUSH || i >= WRITE_buff_SIZE)
	{
		write(fd, buff, i);
		i = 0;
	}
	if (c != buff_FLUSH)
		buff[i++] = c;
	return (1);
}

/**
 *_put_sfd - prints an input string
 * @str: the string to be printed
 * @fd: the filedescriptor to write to
 *
 * Return: the number of chars put
 */
int _put_sfd(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += _putf_d(*str++, fd);
	}
	return (i);
}
