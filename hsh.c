#include "shell.h"

/**
 * hsh - main shell loop
 * @infos: the parameter & return infos struct
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int hsh(infos_t *infos, char **av)
{
	ssize_t r = 0;
	int builtin_rett = 0;

	while (r != -1 && builtin_rett != -2)
	{
		clear_infos(infos);
		if (interactive(infos))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		r = get_input(infos);
		if (r != -1)
		{
			set_infos(infos, av);
			builtin_rett = find_builtin(infos);
			if (builtin_rett == -1)
				find_cmd(infos);
		}
		else if (interactive(infos))
			_putchar('\n');
		free_infos(infos, 0);
	}
	write_history(infos);
	free_infos(infos, 1);
	if (!interactive(infos) && infos->status)
		exit(infos->status);
	if (builtin_rett == -2)
	{
		if (infos->err_num == -1)
			exit(infos->status);
		exit(infos->err_num);
	}
	return (builtin_rett);
}

/**
 * find_builtin - finds a builtin command
 * @infos: the parameter & return infos struct
 *
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */
int find_builtin(infos_t *infos)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (_strcmp(infos->argv[0], builtintbl[i].type) == 0)
		{
			infos->line_count++;
			built_in_ret = builtintbl[i].func(infos);
			break;
		}
	return (built_in_ret);
}

/**
 * find_cmd - finds a command in PATH
 * @infos: the parameter & return infos struct
 *
 * Return: void
 */
void find_cmd(infos_t *infos)
{
	char *path = NULL;
	int i, k;

	infos->path = infos->argv[0];
	if (infos->linecount_flag == 1)
	{
		infos->line_count++;
		infos->linecount_flag = 0;
	}
	for (i = 0, k = 0; infos->arg[i]; i++)
		if (!is_delim(infos->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = find_path(infos, _getenv(infos, "PATH="), infos->argv[0]);
	if (path)
	{
		infos->path = path;
		fork_cmd(infos);
	}
	else
	{
		if ((interactive(infos) || _getenv(infos, "PATH=")
			|| infos->argv[0][0] == '/') && is_cmd(infos, infos->argv[0]))
			fork_cmd(infos);
		else if (*(infos->arg) != '\n')
		{
			infos->status = 127;
			print_error(infos, "not found\n");
		}
	}
}

/**
 * fork_cmd - forks a an exec thread to run cmd
 * @infos: the parameter & return infos struct
 *
 * Return: void
 */
void fork_cmd(infos_t *infos)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(infos->path, infos->argv, get_environ(infos)) == -1)
		{
			free_infos(infos, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(infos->status));
		if (WIFEXITED(infos->status))
		{
			infos->status = WEXITSTATUS(infos->status);
			if (infos->status == 126)
				print_error(infos, "Permission denied\n");
		}
	}
}
