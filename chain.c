#include "shell.h"

/**
 * is_chainn - test if current char in bufffer is a chain delimeter
 * @infos: the parameter struct
 * @buff: the char bufffer
 * @p: address of current position in buff
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int is_chainn(infos_t *infos, char *buff, size_t *p)
{
	size_t j = *p;

	if (buff[j] == '|' && buff[j + 1] == '|')
	{
		buff[j] = 0;
		j++;
		infos->cmd_buff_type = CMD_OR;
	}
	else if (buff[j] == '&' && buff[j + 1] == '&')
	{
		buff[j] = 0;
		j++;
		infos->cmd_buff_type = CMD_AND;
	}
	else if (buff[j] == ';') /* found end of this command */
	{
		buff[j] = 0; /* replace semicolon with null */
		infos->cmd_buff_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}

/**
 * check_chainn - checks we should continue chaining based on last status
 * @infos: the parameter struct
 * @buff: the char bufffer
 * @p: address of current position in buff
 * @i: starting position in buff
 * @len: length of buff
 *
 * Return: Void
 */
void check_chainn(infos_t *infos, char *buff, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (infos->cmd_buff_type == CMD_AND)
	{
		if (infos->status)
		{
			buff[i] = 0;
			j = len;
		}
	}
	if (infos->cmd_buff_type == CMD_OR)
	{
		if (!infos->status)
		{
			buff[i] = 0;
			j = len;
		}
	}

	*p = j;
}

/**
 * replace_alias - replaces an aliases in the tokenized string
 * @infos: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_alias(infos_t *infos)
{
	int i;
	list_t *nodes;
	char *p;

	for (i = 0; i < 10; i++)
	{
		nodes = nodes_starts_with(infos->alias, infos->argv[0], '=');
		if (!nodes)
			return (0);
		free(infos->argv[0]);
		p = _strchr(nodes->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		infos->argv[0] = p;
	}
	return (1);
}

/**
 * replaces_vaars - replaces vars in the tokenized string
 * @infos: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replaces_vaars(infos_t *infos)
{
	int i = 0;
	list_t *nodes;

	for (i = 0; infos->argv[i]; i++)
	{
		if (infos->argv[i][0] != '$' || !infos->argv[i][1])
			continue;

		if (!_strcmp(infos->argv[i], "$?"))
		{
			replace_strings(&(infos->argv[i]),
				_strdup(convert_number(infos->status, 10, 0)));
			continue;
		}
		if (!_strcmp(infos->argv[i], "$$"))
		{
			replace_strings(&(infos->argv[i]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		nodes = nodes_starts_with(infos->env, &infos->argv[i][1], '=');
		if (nodes)
		{
			replace_strings(&(infos->argv[i]),
				_strdup(_strchr(nodes->str, '=') + 1));
			continue;
		}
		replace_strings(&infos->argv[i], _strdup(""));

	}
	return (0);
}

/**
 * replace_strings - replaces string
 * @olds: address of old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_strings(char **olds, char *new)
{
	free(*old);
	*olds = new;
	return (1);
}
