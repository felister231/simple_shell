#include "shell.h"

/**
 * get_input - Reads user input and processes command chains.
 * @info: Pointer to the info_t struct that holds shell information.
 *
 * This function reads user input from the command line and processes
 * command chains separated by semicolons (';'). It handles command chains
 * using a static buffer 'buf', 'i', and 'len'. The function returns the
 * length of the current command if it's part of a chain, or the length of
 * the entire input buffer if there are no command chains.
 *
 * Return: Length of the current command if part of a chain
 */

ssize_t get_input(info_t *info)
{
	static char *buf; /* the ';' command chain buffer */
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	r = input_buf(info, &buf, &len);
	if (r == -1) /* EOF */
		return (-1);
	if (len)	/* we have commands left in the chain buffer */
	{
		j = i; /* init new iterator to current buf position */
		p = buf + i; /* get pointer for return */

		check_chain(info, buf, &j, i, len);
		while (j < len) /* iterate to semicolon or end */
		{
			if (is_chain(info, buf, &j))
				break;
			j++;
		}

		i = j + 1; /* increment past nulled ';'' */
		if (i >= len) /* reached end of buffer? */
		{
			i = len = 0; /* reset position and length */
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p; /* pass back pointer to current command position */
		return (_strlen(p)); /* return length of current command */
	}

	*buf_p = buf; /* else not a chain, pass back buffer from _getline() */
	return (r); /* return length of buffer from _getline() */
}

/**
 * input_buf - Reads user input from stdin and processes command chains.
 * @info: Pointer to the info_t struct that holds shell information.
 * @buf: Pointer to a pointer that holds the input buffer.
 * @len: Pointer to the size of the input buffer.
 *
 * Return: Length of the input buffer. Returns -1 on EOF.
 */


ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len) /* if nothing left in the buffer, fill it */
	{
		/*bfree((void **)info->cmd_buf);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		r = getline(buf, &len_p, stdin);
#else
		r = _getline(info, buf, &len_p);
#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0'; /* remove trailing newline */
				r--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			/* if (_strchr(*buf, ';')) is this a command chain? */
			{
				*len = r;
				info->cmd_buf = buf;
			}
		}
	}
	return (r);
}

/**
 * _getline - Reads input from the buffer 'buf' and handles line processing.
 * @info: Pointer to the info_t struct that holds shell information.
 * @ptr: Pointer to a pointer that holds the input buffer.
 * @length: Pointer to the size of the input buffer.
 *
 * Return: Length of input buffer. Returns -1 on read failure or malloc error.
 */

int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = read_buf(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
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
 * read_buf - Reads input from the file descriptor into the buffer 'buf'.
 * @info: Pointer to the info_t struct that holds shell information.
 * @buf: Pointer to the buffer to store the read input.
 * @i: Pointer to a size_t variable representing the buffer's current position.
 *
 * This function reads input from the file descriptor 'info->readfd' into the
 * buffer 'buf'. It updates the 'i' pointer with the number of bytes read.
 *
 * Return: Number of bytes read, or -1 on read error.
 */

ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(info->readfd, buf, READ_BUF_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}
/**
 * sigintHandler - Signal handler function for SIGINT (Ctrl+C) signal.
 * @sig_num: The signal number (unused in the function).
 *
 * This function is called when the SIGINT signal is received.
 *
 * Return: This function does not return a value.
 */


void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
