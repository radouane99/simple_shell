#include "shell.h"

/**
 * list_lenn - determines length of linked list
 * @h: pointer to first nodess
 *
 * Return: size of list
 */
size_t list_lenn(const lists_t *h)
{
	size_t i = 0;

	while (h)
	{
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * lisst_to_strings - returns an array of strings of the list->str
 * @head: pointer to first nodes
 *
 * Return: array of strings
 */
char **lisst_to_strings(lists_t *head)
{
	lists_t *nodes = head;
	size_t i = list_lenn(head), j;
	char **strs1;
	char *str;

	if (!head || !i)
		return (NULL);
	strs1 = malloc(sizeof(char *) * (i + 1));
	if (!strs1)
		return (NULL);
	for (i = 0; nodes; nodes = nodes->next, i++)
	{
		str = malloc(_strlen(nodes->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs1[j]);
			free(strs1);
			return (NULL);
		}

		str = _strcpy(str, nodes->str);
		strs1[i] = str;
	}
	strs1[i] = NULL;
	return (strs1);
}


/**
 * print_list1 - prints all elements of a lists_t linked list
 * @h: pointer to first nodes
 *
 * Return: size of list
 */
size_t print_list1(const lists_t *h)
{
	size_t i = 0;

	while (h)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * nodes_starts_withh - returns nodes whose string starts with prefix1
 * @nodes: pointer to list head
 * @prefix1: string to match
 * @c: the next character after prefix1 to match
 *
 * Return: match nodes or null
 */
lists_t *nodes_starts_withh(lists_t *nodes, char *prefix1, char c)
{
	char *p = NULL;

	while (nodes)
	{
		p = starts_with(nodes->str, prefix1);
		if (p && ((c == -1) || (*p == c)))
			return (nodes);
		nodes = nodes->next;
	}
	return (NULL);
}

/**
 * get_nodes_indexx - gets the index of a nodes
 * @head: pointer to list head
 * @nodes: pointer to the nodes
 *
 * Return: index of nodes or -1
 */
ssize_t get_nodes_indexx(lists_t *head, lists_t *nodes)
{
	size_t i = 0;

	while (head)
	{
		if (head == nodes)
			return (i);
		head = head->next;
		i++;
	}
	return (-1);
}
