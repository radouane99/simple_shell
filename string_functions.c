#include "shell.h"

/**
 * _strlenn - returns the length of a string
 * @s: the string whose length to check
 *
 * Return: integer length of string
 */
int _strlenn(char *s)
{
	int i = 0;

	if (!s)
		return (0);

	while (*s++)
		i++;
	return (i);
}

/**
 * _strcmpp - performs lexicogarphics comparison of 2 strangs.
 * @s1: the 1 strangs
 * @s2: the 2 strangs
 *
 * Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
 */
int _strcmpp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * starts_withs - checks if needle starts with haystacks
 * @haystacks: string to search
 * @needle: the substring to find
 *
 * Return: address of next char of haystacks or NULL
 */
char *starts_withs(const char *haystacks, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystacks++)
			return (NULL);
	return ((char *)haystacks);
}

/**
 * _strcatt - concatenates 2 strings
 * @destt: the destination buffer
 * @src: the source buffer
 *
 * Return: pointer to destination buffer
 */
char *_strcatt(char *destt, char *src)
{
	char *ret = destt;
	while (*destt)
		destt++;
	while (*src)
		*destt++ = *src++;
	*destt = *src;
	return (ret);
}
