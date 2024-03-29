#include "shell.h"

/**
 * input_buf - buffers chained commands
 * @inf: parameter struct
 * @buf: address of buffer
 * @lenv: address of lenv var
 *
 * Return: bytes read
 */
ssize_t input_buf(info_t *inf, char **buf, size_t *lenv)
{
	ssize_t v = 0;
	size_t len_p = 0;

	if (!*lenv) /* if nothing left in the buffer, fill it */
	{
		/*bfree((void **)inf->cmd_buf);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		v = getline(buf, &len_p, stdin);
#else
		v = _getline(inf, buf, &len_p);
#endif
		if (v > 0)
		{
			if ((*buf)[v - 1] == '\n')
			{
				(*buf)[v - 1] = '\0'; /* remove trailing newline */
				v--;
			}
			inf->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(inf, *buf, inf->histcount++);
			/* if (_strchr(*buf, ';')) is this a command chain? */
			{
				*lenv = v;
				inf->cmd_buf = buf;
			}
		}
	}
	return (v);
}

/**
 * get_input - gets a line minus the newline
 * @inf: parameter struct
 *
 * Return: bytes read
 */
ssize_t get_input(info_t *inf)
{
	static char *buf; /* the ';' command chain buffer */
	static size_t i, j, lenv;
	ssize_t v = 0;
	char **buf_p = &(inf->arg), *p;

	_putchar(BUF_FLUSH);
	v = input_buf(inf, &buf, &lenv);
	if (v == -1) /* EOF */
		return (-1);
	if (lenv)	/* we have commands left in the chain buffer */
	{
		j = i; /* init new iterator to current buf position */
		p = buf + i; /* get pointer for return */

		check_chain(inf, buf, &j, i, lenv);
		while (j < lenv) /* iterate to semicolon or end */
		{
			if (is_chain(inf, buf, &j))
				break;
			j++;
		}

		i = j + 1; /* increment past nulled ';'' */
		if (i >= lenv) /* reached end of buffer? */
		{
			i = lenv = 0; /* reset position and length */
			inf->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p; /* pass back pointer to current command position */
		return (_strlen(p)); /* return length of current command */
	}

	*buf_p = buf; /* else not a chain, pass back buffer from _getline() */
	return (v); /* return length of buffer from _getline() */
}

/**
 * read_buf - reads a buffer
 * @inf: parameter struct
 * @buf: buffer
 * @i: size
 *
 * Return: v
 */
ssize_t read_buf(info_t *inf, char *buf, size_t *i)
{
	ssize_t v = 0;

	if (*i)
		return (0);
	v = read(inf->readfd, buf, READ_BUF_SIZE);
	if (v >= 0)
		*i = v;
	return (v);
}

/**
 * _getline - gets the next line of input from STDIN
 * @inf: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int _getline(info_t *inf, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, lenv;
	size_t k;
	ssize_t v = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == lenv)
		i = lenv = 0;

	v = read_buf(inf, buf, &lenv);
	if (v == -1 || (v == 0 && lenv == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : lenv;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + i, k - i);
	else
		_strncpy(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * sigintHandler - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
