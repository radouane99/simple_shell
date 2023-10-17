#include "shell.h"

/**
 **_strncpys - copies a string
 *@destt: the destination string to be copied to
 *@srcs: the source string
 *@t: the amount of characters to be copied
 *Return: the concatenated string
 */
char *_strncpys(char *destt, char *srcs, int t)
{
	int i, j;
	char *k = destt;

	i = 0;
	while (srcs[i] != '\0' && i < t - 1)
	{
		destt[i] = srcs[i];
		i++;
	}
	if (i < t)
	{
		j = i;
		while (j < t)
		{
			destt[j] = '\0';
			j++;
		}
	}
	return (k);
}

/**
 **_strncat - concatenates 2 strings
 *@destt: the first string
 *@srcs: the second string
 *@t: the amount of bytes to be maximally used
 *Return: the concatenated string
 */
char *_strncat(char *destt, char *srcs, int t)
{
	int i, j;
	char *k = destt;

	i = 0;
	j = 0;
	while (destt[i] != '\0')
		i++;
	while (srcs[j] != '\0' && j < t)
	{
		destt[i] = srcs[j];
		i++;
		j++;
	}
	if (j < t)
		destt[i] = '\0';
	return (k);
}

/**
 **_strchrs - locates a character in a string
 *@d: the string to be parsed
 *@c: the character to look for
 *Return: (d) a pointer to the memory area d
 */
char *_strchrs(char *d, char c)
{
	do {
		if (*d == c)
			return (d);
	} while (*d++ != '\0');

	return (NULL);
}
