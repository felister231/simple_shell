#include "shell.h"

/**
 * get_userinput - Reads user input and processes command chains.
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

ssize_t get_userinput(data_info *data)
{
	static char *buffer; /* the ';' command chain buffer */
	static size_t a, b, length;
	ssize_t i = 0;
	char **buffer_pointer = &(data->arg), *pointer;

	_putchar(BUF_FLUSH);
	i = input_buffer(data, &buffer, &length);
	if (i == -1) /* EOF */
		return (-1);
	if (length)	/* we have commands left in the chain buffer */
	{
		b = a; /* init new iterator to current buf position */
		pointer = buffer + a; /* get pointer for return */

		bufferUpdate_check(data, buffer, &b, a, length);
		while (b < length) /* iterate to semicolon or end */
		{
			if (chainCmd(data, buffer, &a))
				break;
			b++;
		}

		a = b + 1; /* increment past nulled ';'' */
		if (a >= length) /* reached end of buffer? */
		{
			a = length = 0; /* reset position and length */
			data->cmd_buf_type = CMD_NORM;
		}

		*buffer_pointer = pointer; /* pass back pointer to current command position */
		return (_strlen(pointer)); /* return length of current command */
	}

	*buffer_pointer = buffer; /* else not a chain, pass back buffer from _getline() */
	return (i); /* return length of buffer from _getline() */
}

/**
 * input_buffer - Reads user input from stdin and processes command chains.
 * @info: Pointer to the info_t struct that holds shell information.
 * @buf: Pointer to a pointer that holds the input buffer.
 * @len: Pointer to the size of the input buffer.
 *
 * Return: Length of the input buffer. Returns -1 on EOF.
 */


ssize_t input_buffer(data_info *data, char **buffer, size_t *length)
{
	ssize_t a = 0;
	size_t length_pointer = 0;

	if (!*length) /* if nothing left in the buffer, fill it */
	{
		/*free_memory((void **)info->cmd_buf);*/
		free(*buffer);
		*buffer = NULL;
		signal(SIGINT, singleintHandler);
#if USE_GETLINE
		a = getline(buffer, &length_pointer, stdin);
#else
		a = _getline(data, buffer, &length_pointer);
#endif
		if (a > 0)
		{
			if ((*buffer)[a - 1] == '\n')
			{
				(*buffer)[a - 1] = '\0'; /* remove trailing newline */
				a--;
			}
			data->linecount_flag = 1;
			remove_Bufcomments(*buffer);
			history_build_ls(data, *buffer, data->histcount++);
			/* if (_strchr(*buf, ';')) is this a command chain? */
			{
				*length = a;
				data->cmd_buf = buffer;
			}
		}
	}
	return (a);
}

/**
 * _getline - Reads input from the buffer 'buf' and handles line processing.
 * @info: Pointer to the info_t struct that holds shell information.
 * @ptr: Pointer to a pointer that holds the input buffer.
 * @length: Pointer to the size of the input buffer.
 *
 * Return: Length of input buffer. Returns -1 on read failure or malloc error.
 */

int _getline(data_info *data, char **ptr, size_t *longg)
{
	static char buffer[READ_BUF_SIZE];
	static size_t a, lenth;
	size_t b;
	ssize_t c = 0, d = 0;
	char *pointer = NULL, *new_pointer = NULL, *e;

	pointer = *ptr;
	if (pointer && longg)
		d = *longg;
	if (a == lenth)
		a = lenth = 0;

	c = read_buffer(data, buffer, &lenth);
	if (c == -1 || (c == 0 && lenth == 0))
		return (-1);

	e = _strchr(buffer + a, '\n');
	b = e ? 1 + (unsigned int)(e - buffer) : lenth;
	new_pointer = _realloc(pointer, d, d ? d + b : b + 1);
	if (!new_pointer) /* MALLOC FAILURE! */
		return (pointer ? free(pointer), -1 : -1);

	if (d)
		_strncat(new_pointer, buffer + a, b - a);
	else
		_strncpy(new_pointer, buffer + a, b - a + 1);

	d += b - a;
	a = b;
	pointer = new_pointer;

	if (longg)
		*longg = d;
	*ptr = pointer;
	return (d);
}

/**
 * read_buffer - Reads input from the file descriptor into the buffer 'buf'.
 * @info: Pointer to the info_t struct that holds shell information.
 * @buf: Pointer to the buffer to store the read input.
 * @i: Pointer to a size_t variable representing the buffer's current position.
 *
 * This function reads input from the file descriptor 'info->readfd' into the
 * buffer 'buf'. It updates the 'i' pointer with the number of bytes read.
 *
 * Return: Number of bytes read, or -1 on read error.
 */

ssize_t read_buffer(data_info *data, char *buffer, size_t *a)
{
	ssize_t b = 0;

	if (*a)
		return (0);
	b = read(data->readfd, buffer, READ_BUF_SIZE);
	if (b >= 0)
		*a = b;
	return (b);
}
/**
 * singleintHandler - Signal handler function for SIGINT (Ctrl+C) signal.
 * @sig_num: The signal number (unused in the function).
 *
 * This function is called when the SIGINT signal is received.
 *
 * Return: This function does not return a value.
 */


void singleintHandler(__attribute__((unused))int signal_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
