#include "shell.h"

/**
 * add_nodes - adds a nodes to the start of the list
 * @head: address of pointer to head nodes
 * @str: str field of nodes
 * @num: nodes index used by histore
 *
 * Return: size of list
 */
list_t *add_nodes(list_t **head, const char *str, int num)
{
	list_t *new_head;

	if (!head)
		return (NULL);
	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return (NULL);
	_memset((void *)new_head, 0, sizeof(list_t));
	new_head->num = num;
	if (str)
	{
		new_head->str = _strdup(str);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *head;
	*head = new_head;
	return (new_head);
}

/**
 * add_nodes_end_ - adds a nodes to the end of the list
 * @head: address of pointer to head nodes
 * @str: str field of nodes
 * @num: nodes index used by histore
 *
 * Return: size of list
 */
list_t *add_nodes_end_(list_t **head, const char *str, int num)
{
	list_t *new_nodes, *nodes;

	if (!head)
		return (NULL);

	nodes = *head;
	new_nodes = malloc(sizeof(list_t));
	if (!new_nodes)
		return (NULL);
	_memset((void *)new_nodes, 0, sizeof(list_t));
	new_nodes->num = num;
	if (str)
	{
		new_nodes->str = _strdup(str);
		if (!new_nodes->str)
		{
			free(new_nodes);
			return (NULL);
		}
	}
	if (nodes)
	{
		while (nodes->next)
			nodes = nodes->next;
		nodes->next = new_nodes;
	}
	else
		*head = new_nodes;
	return (new_nodes);
}

/**
 * print_lists_strs - prints only the str element of a list_t linked list
 * @h: pointer to first nodes
 *
 * Return: size of list
 */
size_t print_lists_strs(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * delete_nodes_at_indexx - deletes nodes at given index
 * @head: address of pointer to first nodes
 * @index: index of nodes to deletes
 *
 * Return: 1 on success, 0 on failure
 */
int delete_nodes_at_indexx(list_t **head, unsigned int index)
{
	list_t *nodes, *prev_nodes;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		nodes = *head;
		*head = (*head)->next;
		free(nodes->str);
		free(nodes);
		return (1);
	}
	nodes = *head;
	while (nodes)
	{
		if (i == index)
		{
			prev_nodes->next = nodes->next;
			free(nodes->str);
			free(nodes);
			return (1);
		}
		i++;
		prev_nodes = nodes;
		nodes = nodes->next;
	}
	return (0);
}

/**
 * free_lists - frees all nodess of a list
 * @head_ptrr: address of pointer to head nodes
 *
 * Return: void
 */
void free_lists(list_t **head_ptrr)
{
	list_t *nodes, *next_nodes, *head;

	if (!head_ptrr || !*head_ptrr)
		return;
	head = *head_ptrr;
	nodes = head;
	while (nodes)
	{
		next_nodes = nodes->next;
		free(nodes->str);
		free(nodes);
		nodes = next_nodes;
	}
	*head_ptrr = NULL;
}
