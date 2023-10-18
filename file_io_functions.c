#include "shell.h"

/**
 * get_history_file1 - gets the history file
 * @info1: parameter struct
 *
 * Return: allocated string containg history file
 */

char *get_history_file1(info_t *info1)
{
	char *buff, *dir;

	dir = _getenv(info1, "HOME=");
	if (!dir)
		return (NULL);
	buff = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!buff)
		return (NULL);
	buff[0] = 0;
	_strcpy(buff, dir);
	_strcat(buff, "/");
	_strcat(buff, HIST_FILE);
	return (buff);
}

/**
 * write_history1 - creates a file, or appends to an existing file
 * @info1: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int write_history1(info_t *info1)
{
	ssize_t fd;
	char *filenames = get_history_file1(info1);
	list_t *nodes = NULL;

	if (!filenames)
		return (-1);

	fd = open(filenames, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filenames);
	if (fd == -1)
		return (-1);
	for (nodes = info1->history; nodes; nodes = nodes->next)
	{
		_putsfd(nodes->str, fd);
		_putfd('\n', fd);
	}
	_putfd(buff_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_history1 - reads history from file
 * @info1: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int read_history1(info_t *info1)
{
	int i, last = 0, linecounts = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buff = NULL, *filenames = get_history_file1(info1);

	if (!filenames)
		return (0);

	fd = open(filenames, O_RDONLY);
	free(filenames);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buff = malloc(sizeof(char) * (fsize + 1));
	if (!buff)
		return (0);
	rdlen = read(fd, buff, fsize);
	buff[fsize] = 0;
	if (rdlen <= 0)
		return (free(buff), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buff[i] == '\n')
		{
			buff[i] = 0;
			build_history_list1(info1, buff + last, linecounts++);
			last = i + 1;
		}
	if (last != i)
		build_history_list1(info1, buff + last, linecounts++);
	free(buff);
	info1->histcount = linecounts;
	while (info1->histcount-- >= HIST_MAX)
		delete_nodes_at_index(&(info1->history), 0);
	renumber_history1(info1);
	return (info1->histcount);
}

/**
 * build_history_list1 - adds entry to a history linked list
 * @info1: Structure containing potential arguments. Used to maintain
 * @buff: bufffer
 * @linecounts: the history linecounts, histcount
 *
 * Return: Always 0
 */
int build_history_list1(info_t *info1, char *buff, int linecounts)
{
	list_t *nodes = NULL;

	if (info1->history)
		nodes = info1->history;
	add_nodes_end(&nodes, buff, linecounts);

	if (!info1->history)
		info1->history = nodes;
	return (0);
}

/**
 * renumber_history1 - renumbers the history linked list after changes
 * @info1: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */
int renumber_history1(info_t *info1)
{
	list_t *nodes = info1->history;
	int i = 0;

	while (nodes)
	{
		nodes->num = i++;
		nodes = nodes->next;
	}
	return (info1->histcount = i);
}
