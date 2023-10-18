#include "shell.h"

/**
 * _myhistory1 - Showcases the history list, with each command on a separate line.
 *			    accompanied by line numbers beginning at 0.
 * @info1: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _myhistory1(info_t *info1)
{
	print_list(info1->history);
	return (0);
}

/**
 * unset_alias11 - sets alias to string
 * @info1: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_alias11(info_t *info1, char *str)
{
	char *p, c;
	int ret;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = delete_nude1_at_index(&(info1->alias),
		get_nude1_index(info1->alias, nude1_starts_with(info1->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * set_alias1 - sets alias to string
 * @info1: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias1(info_t *info1, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias11(info1, str));

	unset_alias11(info1, str);
	return (add_nude1_end(&(info1->alias), str, 0) == NULL);
}

/**
 * print_alias1 - prints an alias string
 * @nude1: the alias nude1
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias1(list_t *nude1)
{
	char *p = NULL, *a = NULL;

	if (nude1)
	{
		p = _strchr(nude1->str, '=');
		for (a = nude1->str; a <= p; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias1 - mimics the alias builtin (man alias)
 * @info1: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _myalias1(info_t *info1)
{
	int i = 0;
	char *p = NULL;
	list_t *nude1 = NULL;

	if (info1->argc == 1)
	{
		nude1 = info1->alias;
		while (nude1)
		{
			print_alias1(nude1);
			nude1 = nude1->next;
		}
		return (0);
	}
	for (i = 1; info1->argv[i]; i++)
	{
		p = _strchr(info1->argv[i], '=');
		if (p)
			set_alias1(info1, info1->argv[i]);
		else
			print_alias1(nude1_starts_with(info1->alias, info1->argv[i], '='));
	}

	return (0);
}
