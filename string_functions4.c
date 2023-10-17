#include "shell.h"

/**
 * **strtows - splits a string into words. Repeat delimiters are ignored
 * @str1: the input string
 * @d: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **strtows(char *str1, char *d)
{
	int i, j, k, m, numwords1 = 0;
	char **s;

	if (str1 == NULL || str1[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (i = 0; str1[i] != '\0'; i++)
		if (!is_delim(str1[i], d) && (is_delim(str1[i + 1], d) || !str1[i + 1]))
			numwords1++;

	if (numwords1 == 0)
		return (NULL);
	s = malloc((1 + numwords1) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < numwords1; j++)
	{
		while (is_delim(str1[i], d))
			i++;
		k = 0;
		while (!is_delim(str1[i + k], d) && str1[i + k])
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = str1[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}

/**
 * **strtows2 - splits a str1ing into words
 * @str1: the input str1ing
 * @d: the delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **strtows2(char *str1, char d)
{
	int i, j, k, m, numwords1 = 0;
	char **s;

	if (str1 == NULL || str1[0] == 0)
		return (NULL);
	for (i = 0; str1[i] != '\0'; i++)
		if ((str1[i] != d && str1[i + 1] == d) ||
		    (str1[i] != d && !str1[i + 1]) || str1[i + 1] == d)
			numwords1++;
	if (numwords1 == 0)
		return (NULL);
	s = malloc((1 + numwords1) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < numwords1; j++)
	{
		while (str1[i] == d && str1[i] != d)
			i++;
		k = 0;
		while (str1[i + k] != d && str1[i + k] && str1[i + k] != d)
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = str1[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}
