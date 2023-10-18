#include "shell.h"

/**
 * _myhistore - displays the history list, one command by line, preceded
 * @info1: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _myhistore(info_t *info1)
{
	print_list(info1->history);
	return (0);
}

/**
 * un_set_alias - sets alias to string
 * @info1: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int un_set_alias(info_t *info1, char *str)
{
	char *p, c;
	int rett;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	rett = delete_node_at_index(&(info1->alias),
		get_node_index(info1->alias, nodes_starts_with(info1->alias, str, -1)));
	*p = c;
	return (rett);
}

/**
 * set_alias - sets alias to string
 * @info1: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias(info_t *info1, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (un_set_alias(info1, str));

	un_set_alias(info1, str);
	return (add_node_end(&(info1->alias), str, 0) == NULL);
}

/**
 * print_alias - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _my_alias - mimics the alias builtin (man alias)
 * @info1: Structure containing potential arguments.
 *  Return: Always 0
 */
int _my_alias(info_t *info1)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info1->argc == 1)
	{
		node = info1->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info1->argv[i]; i++)
	{
		p = _strchr(info1->argv[i], '=');
		if (p)
			set_alias(info1, info1->argv[i]);
		else
			print_alias(nodes_starts_with(info1->alias, info1->argv[i], '='));
	}

	return (0);
}
