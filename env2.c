#include "shell.h"

/**
 * get_environn - returns the string array copy of our environ
 * @info1: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
char **get_environn(info_t *info1)
{
	if (!info1->environ || info1->env_changed)
	{
		info1->environ = list_to_strings(info1->env);
		info1->env_changed = 0;
	}

	return (info1->environ);
}

/**
 * _unset_envi - Remove an environment variable
 * @info1: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @var: the string env var property
 */
int _unset_envi(info_t *info1, char *var)
{
	list_t *nodes = info1->env;
	size_t i = 0;
	char *p;

	if (!nodes || !var)
		return (0);

	while (nodes)
	{
		p = starts_with(nodes->str, var);
		if (p && *p == '=')
		{
			info1->env_changed = delete_nodes_at_index(&(info1->env), i);
			i = 0;
			nodes = info1->env;
			continue;
		}
		nodes = nodes->next;
		i++;
	}
	return (info1->env_changed);
}

/**
 * _set_env - Initialize a new environment variable
 * @info1: Structure containing potential arguments.
 * @var: the string env var property
 * @values: the string env var values
 *  Return: Always 0
 */
int _set_env(info_t *info1, char *var, char *values)
{
	char *buff = NULL;
	list_t *nodes;
	char *p;

	if (!var || !values)
		return (0);

	buff = malloc(_strlen(var) + _strlen(values) + 2);
	if (!buff)
		return (1);
	_strcpy(buff, var);
	_strcat(buff, "=");
	_strcat(buff, values);
	nodes = info1->env;
	while (nodes)
	{
		p = starts_with(nodes->str, var);
		if (p && *p == '=')
		{
			free(nodes->str);
			nodes->str = buff;
			info1->env_changed = 1;
			return (0);
		}
		nodes = nodes->next;
	}
	add_nodes_end(&(info1->env), buff, 0);
	free(buff);
	info1->env_changed = 1;
	return (0);
}
