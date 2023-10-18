#include "shell.h"
/**
* _strcpys - copies a string
* @dests: the destsination
* @srcs: the source
*
* Return: pointers to destsination
*/
char *_strcpys(char *dests, char *srcs)
{
int i = 0;

if (dests == srcs || srcs == 0)
return (dests);
while (srcs[i])
{
dests[i] = srcs[i];
i++;
}
dests[i] = 0;
return (dests);
}

/**
 * _strdupp - duplicates a string
 * @strr: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *_strdupp(const char *strr)
{
int length = 0;
char *rett;

if (strr == NULL)
return (NULL);
while (*strr++)
length++;
rett = malloc(sizeof(char) * (length + 1));
if (!rett)
return (NULL);
for (length++; length--;)
rett[length] = *--strr;
return (rett);
}

/**
*_puts - prints an input string
*@strr: the string to be printed
*
* Return: Nothing
*/
void _puts(char *strr)
{
int i = 0;

if (!strr)
return;
while (strr[i] != '\0')
{
_putchar(str[i]);
i++;
}
}
/**
 * _putchar - writes the character cc to stdout
 * @cc: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately..
 */
int _putchar(char cc)
{
static int i;
static char buff[WRITE_BUF_SIZE];

if (cc == BUF_FLUSH || i >= WRITE_BUF_SIZE)
{
write(1, buff, i);
i = 0;
}
if (cc != BUF_FLUSH)
buff[i++] = cc;
return (1);
}

