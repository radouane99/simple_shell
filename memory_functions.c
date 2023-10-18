#include "shell.h"

/**
 **_memsett - fills memory with a constant byte
 *@s: the pointer to the memory area
 *@b: the byte to fill *s with
 *@n: the amount of bytes to be filled
 *Return: (s) a pointer to the memory area s
 */
char *_memsett(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		s[i] = b;
	return (s);
}

/**
 * ffrees - frees a string of strings
 * @pp: string of strings
 */
void ffrees(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a);
}

/**
 * _realloc - reallocates a block of memory
 * @ptr: pointer to previous malloc'ated block
 * @old_sizes: byte size of previous block
 * @new_sizes: byte size of new block
 *
 * Return: pointer to da ol'block nameen.
 */
void *_realloc(void *ptr, unsigned int old_sizes, unsigned int new_sizes)
{
	char *p;

	if (!ptr)
		return (malloc(new_sizes));
	if (!new_sizes)
		return (free(ptr), NULL);
	if (new_sizes == old_sizes)
		return (ptr);

	p = malloc(new_sizes);
	if (!p)
		return (NULL);

	old_sizes = old_sizes < new_sizes ? old_sizes : new_sizes;
	while (old_sizes--)
		p[old_sizes] = ((char *)ptr)[old_sizes];
	free(ptr);
	return (p);
}
