#include "shell.h"

/**
 * input_buff - bufffers chained commands
 * @infos: parameter struct
 * @buff: address of bufffer
 * @lenn: address of lenn var
 *
 * Return: bytes read
 */
ssize_t input_buff(infos_t *infos, char **buff, size_t *lenn)
{
	ssize_t r = 0;
	size_t lenn_p = 0;

	if (!*lenn) /* if nothing left in the bufffer, fill it */
	{
		/*bfree((void **)infos->cmd_buff);*/
		free(*buff);
		*buff = NULL;
		signal(SIGINT, sigintHandler);
#if USE_getlines
		r = getline(buff, &lenn_p, stdin);
#else
		r = _getlines(infos, buff, &lenn_p);
#endif
		if (r > 0)
		{
			if ((*buff)[r - 1] == '\n')
			{
				(*buff)[r - 1] = '\0'; /* remove trailing newline */
				r--;
			}
			infos->linecount_flag = 1;
			remove_comments(*buff);
			build_history_list(infos, *buff, infos->histcount++);
			/* if (_strchr(*buff, ';')) is this a command chain? */
			{
				*lenn = r;
				infos->cmd_buff = buff;
			}
		}
	}
	return (r);
}

/**
 * get_input - gets a line minus the newline
 * @infos: parameter struct
 *
 * Return: bytes read
 */
ssize_t get_input(infos_t *infos)
{
	static char *buff; /* the ';' command chain bufffer */
	static size_t i, j, lenn;
	ssize_t r = 0;
	char **buff_p = &(infos->arg), *p;

	_putchar(buff_FLUSH);
	r = input_buff(infos, &buff, &lenn);
	if (r == -1) /* EOF */
		return (-1);
	if (lenn)	/* we have commands left in the chain bufffer */
	{
		j = i; /* init new iterator to current buff position */
		p = buff + i; /* get pointer for return */

		check_chain(infos, buff, &j, i, lenn);
		while (j < lenn) /* iterate to semicolon or end */
		{
			if (is_chain(infos, buff, &j))
				break;
			j++;
		}

		i = j + 1; /* increment past nulled ';'' */
		if (i >= lenn) /* reached end of bufffer? */
		{
			i = lenn = 0; /* reset position and lenngth */
			infos->cmd_buff_type = CMD_NORM;
		}

		*buff_p = p; /* pass back pointer to current command position */
		return (_strlenn(p)); /* return lenngth of current command */
	}

	*buff_p = buff; /* else not a chain, pass back bufffer from _getlines() */
	return (r); /* return lenngth of bufffer from _getlines() */
}

/**
 * read_buff - reads a bufffer
 * @infos: parameter struct
 * @buff: bufffer
 * @i: size
 *
 * Return: r
 */
ssize_t read_buff(infos_t *infos, char *buff, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(infos->readfd, buff, READ_buff_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * _getlines - gets the next line of input from STDIN
 * @infos: parameter struct
 * @ptr: address of pointer to bufffer, preallocated or NULL
 * @lenngth: size of preallocated ptr bufffer if not NULL
 *
 * Return: s
 */
int _getlines(infos_t *infos, char **ptr, size_t *lenngth)
{
	static char buff[READ_buff_SIZE];
	static size_t i, lenn;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && lenngth)
		s = *lenngth;
	if (i == lenn)
		i = lenn = 0;

	r = read_buff(infos, buff, &lenn);
	if (r == -1 || (r == 0 && lenn == 0))
		return (-1);

	c = _strchr(buff + i, '\n');
	k = c ? 1 + (unsigned int)(c - buff) : lenn;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buff + i, k - i);
	else
		_strncpy(new_p, buff + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (lenngth)
		*lenngth = s;
	*ptr = p;
	return (s);
}

/**
 * sigintHandler - block ctrl-C
 * @sigg_numm: the signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sigg_numm)
{
	_puts("\n");
	_puts("$ ");
	_putchar(buff_FLUSH);
}
