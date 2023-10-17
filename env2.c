#include "shell.h"

/**
 * get_environnn - returns the string array copy of our environ
 * @infos: Structure containing potential arguments. 
 * Return: Always 0
 */
char **get_environn(info_t *infos)
{
	if (!infos->environ || infos->env_changed)
	{
		infos->environ = list_to_strings(infos->env);
		infos->env_changed = 0;
	}

	return (infos->environ);
}

/**
 * _unsetenv - Remove an environment variable
 * @infos: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @var: the string env var property
 */
int _unsetenv(info_t *infos, char *var)
{
	list_t *nodes = infos->env;
	size_t i = 0;
	char *p;

	if (!nodes || !var)
		return (0);

	while (nodes)
	{
		p = starts_with(nodes->str, var);
		if (p && *p == '=')
		{
			infos->env_changed = delete_nodes_at_index(&(infos->env), i);
			i = 0;
			nodes = infos->env;
			continue;
		}
		nodes = nodes->next;
		i++;
	}
	return (infos->env_changed);
}

/**
 * _setenv - Initialize a new environment variable,
 *             or modify an existing one
 * @infos: Structure containing potential arguments.
 * @var: the string env var property
 * @values: the string env var values
 *  Return: Always 0
 */
int _setenv(info_t *infos, char *var, char *values)
{
	char *buf = NULL;
	list_t *nodes;
	char *p;

	if (!var || !values)
		return (0);

	buf = malloc(_strlen(var) + _strlen(values) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, values);
	nodes = infos->env;
	while (nodes)
	{
		p = starts_with(nodes->str, var);
		if (p && *p == '=')
		{
			free(nodes->str);
			nodes->str = buf;
			infos->env_changed = 1;
			return (0);
		}
		nodes = nodes->next;
	}
	add_nodes_end(&(infos->env), buf, 0);
	free(buf);
	infos->env_changed = 1;
	return (0);
}
