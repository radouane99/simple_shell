#include "shell.h"

/**
 * _myenvi - prints the current environment
 * @infos: Structure containing potential arguments.
 * Return: Always 0
 */
int _myenvi(info_t *infos)
{
	print_list_str(infos->env);
	return (0);
}

/**
 * _getenvi - gets the value of an environ variable
 * @infos: Structure containing potential arguments. Used to maintain
 * @names: env var name
 *
 * Return: the value
 */
char *_getenvi(info_t *infos, const char *names)
{
	list_t *nodes = infos->env;
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
 * _mysetenvi - Initialize a new environment variable,
 *             or modify an existing one
 * @infos: Structure containing potential arguments. 
 *  Return: Always 0
 */
int _mysetenvi(info_t *infos)
{
	if (infos->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(infos, infos->argv[1], infos->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenvi - Remove an environment variable
 * @infos: Structure containing potential arguments.
 *  Return: Always 0
 */
int _myunsetenvi(info_t *infos)
{
	int i;

	if (infos->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= infos->argc; i++)
		_unsetenv(infos, infos->argv[i]);
	return (0);
}

/**
 * populate_env_list01 - populates env linked list
 * @infos: Structure containing potential arguments. 
 * Return: Always 0
 */
int populate_env_list01(info_t *infos)
{
	list_t *nodes = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_nodes_end(&nodes, environ[i], 0);
	infos->env = nodes;
	return (0);
}
