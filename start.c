#include "shell.h"


void start()
{
	char *start_command;

	while(1)
	{
		start_command = prompt_user();
		/* handling for the control D */
		if (start_command == NULL)
		{
			printf("\n");
			break;
		}
        	execute(start_command);
	}
}
