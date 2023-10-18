#include "shell.h"

/**
 * _myexit1 - exits the shell
 * @info1: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: exits with a given exit status
 *         (0) if info1.argv[0] != "exit"
 */
int _myexit1(info_t *info1)
{
	int exitche;

	if (info1->argv[1])  /* If there is an exit arguement */
	{
		exitche = _erratoi(info1->argv[1]);
		if (exitche == -1)
		{
			info1->status = 2;
			print_error(info1, "Illegal number: ");
			_eputs(info1->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info1->err_num = _erratoi(info1->argv[1]);
		return (-2);
	}
	info1->err_num = -1;
	return (-2);
}

/**
* _mycdd - changes the current directory of the process
* @info1: Structure containing potential arguments.
*  Return: Always 0
*/
int _mycdd(info_t *info1)
{
	char *s, *dir, buffer[1024];
	int chdir_rett;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info1->argv[1])
	{
		dir = _getenv(info1, "HOME=");
		if (!dir)
			chdir_rett = /* TODO: what should this be? */
				chdir((dir = _getenv(info1, "PWD=")) ? dir : "/");
		else
			chdir_rett = chdir(dir);
	}
	else if (_strcmp(info1->argv[1], "-") == 0)
	{
		if (!_getenv(info1, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info1, "OLDPWD=")), _putchar('\n');
		chdir_rett = /* TODO: what should this be? */
			chdir((dir = _getenv(info1, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_rett = chdir(info1->argv[1]);
	if (chdir_rett == -1)
	{
		print_error(info1, "can't cd to ");
		_eputs(info1->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info1, "OLDPWD", _getenv(info1, "PWD="));
		_setenv(info1, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _myhelps - changes the current directory of the process
 * @info1: Structure containing potential arguments.
 *  Return: Always 0
 */
int _myhelps(info_t *info1)
{
	char **arg_arrays;

	arg_arrays = info1->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_arrays); /* temp att_unused workaround */
	return (0);
}
