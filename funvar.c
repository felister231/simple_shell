#include "shell.h"

/**
 * bufferUpdate_check - Check the status of command buffer and update it
 * @data: Pointer to the info_t struct containing command and status info
 * @buffer: Buffer containing the command chain
 * @pointer: Pointer to the current index in the buffer
 * @index: Current index to be checked in the buffer
 * @length: Length of the buffer
 */


void bufferUpdate_check(data_info *data, char *buffer, size_t *pointer,
	size_t index, size_t length)
{
	size_t j = *pointer;

	if (data->cmd_buf_type == CMD_AND)
	{
		if (data->status)
		{
			buffer[index] = 0;
			j = length;
		}
	}
	if (data->cmd_buf_type == CMD_OR)
	{
		if (!data->status)
		{
			buffer[index] = 0;
			j = length;
		}
	}

	*pointer = j;
}

/**
 * chainCmd - Check if current command is type CMD_OR, CMD_AND, or CMD_CHAIN
 * @data: Pointer to the info_t struct containing command buffer type info
 * @buffer: Buffer containing the command chain
 * @pointer: Pointer to the current index in the buffer
 *
 * Return: 1 if a valid command chain is found, 0 otherwise.
 */

int chainCmd(data_info *data, char *buffer, size_t *pointer)
{
	size_t j = *pointer;

	if (buffer[j] == '|' && buffer[j + 1] == '|')
	{
		buffer[j] = 0;
		j++;
		data->cmd_buf_type = CMD_OR;
	}
	else if (buffer[j] == '&' && buffer[j + 1] == '&')
	{
		buffer[j] = 0;
		j++;
		data->cmd_buf_type = CMD_AND;
	}
	else if (buffer[j] == ';') /* found end of this command */
	{
		buffer[j] = 0; /* replace semicolon with null */
		data->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);

	*pointer = j;
	return (1);
}
