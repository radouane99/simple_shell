#include "shell.h"

/**
 * _myenvi - prints the current environment
 * @info1: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int _myenvi(info_t *info1)
{
	prints_list_str(info1->env);
	return (0);
}

/**
 * _getenvi - gets the value of an environ variable
 * @info1: Structure containing potential arguments.
 * @names: env var names
 *
 * Return: the value
 */
char *_getenvi(info_t *info1, const char *names)
{
	list_t *nodes = info1->env;
	char *p;

	while (nodes)
	{
		p = starts_with(nodes->str, names);
		if (p && *p)
			return (p);
		nodes = nodes->next;
	}
	return (NULL);
}

/**
 * _my_setenv - Initialize a new environment variable,
 *             or modify an existing one
 * @info1: Structure containing potential arguments.
 *  Return: Always 0
 */
int _my_setenv(info_t *info1)
{
	if (info1->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(info1, info1->argv[1], info1->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - Remove an environment variable
 * @info1: Structure containing potential arguments.
 *  Return: Always 0
 */
int _myunsetenv(info_t *info1)
{
	int i;

	if (info1->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= info1->argc; i++)
		_unsetenv(info1, info1->argv[i]);

	return (0);
}

/**
 * populate_env_lists - populates env linked list
 * @info1: Structure containing potential arguments.
 * Return: Always 0
 */
int populate_env_lists(info_t *info1)
{
	list_t *nodes = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_nodes_end(&nodes, environ[i], 0);
	info1->env = nodes;
	return (0);
}
