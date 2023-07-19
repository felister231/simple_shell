#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_INPUT_SIZE 1024
#define MAX_TOKEN_SIZE 64
#define MAX_NUM_TOKENS 64

// Function to print the shell prompt
void printPrompt() {
	printf(">>> ");
}

// Function to read the user input
int readInput(char **input) {
	size_t bufsize = 0;
	return getline(input, &bufsize, stdin);
}

// Function to parse the input into tokens
void tokenizeInput(char *input, char **tokens, int *numTokens) {
	char *token = strtok(input, " \t\n");
	int i = 0;
	while (token != NULL) {
		tokens[i] = token;
		i++;
		token = strtok(NULL, " \t\n");
	}
	tokens[i] = NULL;
	*numTokens = i;
}

// Function to execute the command
void executeCommand(char **tokens) {
	pid_t pid = fork();
	if (pid < 0) {
		printf("Fork failed.\n");
		return;
	} else if (pid == 0) {
		// Child process
		if (execvp(tokens[0], tokens) < 0) {
			printf("Command execution failed.\n");
			exit(1);
		}
	} else {
		// Parent process
		wait(NULL);
		return;
	}
}

// Function to handle the built-in commands
int handleBuiltInCommands(char **tokens) {
	if (strcmp(tokens[0], "exit") == 0) {
		printf("Goodbye!\n");
		return 1;
	} else if (strcmp(tokens[0], "cd") == 0) {
		if (chdir(tokens[1]) != 0)
			printf("Directory not found.\n");
		return 1;
	} else if (strcmp(tokens[0], "help") == 0) {
		printf("List of commands supported:\n");
		printf("- exit\n");
		printf("- cd <directory>\n");
		printf("- help\n");
		return 1;
	} else if (strcmp(tokens[0], "hello") == 0) {
		printf("Hello! This is a simple shell.\n");
		return 1;
	}
	return 0;
}

int main() {
	char *input = NULL;
	char *tokens[MAX_NUM_TOKENS];
	int numTokens;

	printf("******************\n");
	printf("**** MY SHELL ****\n");
	printf("******************\n");

	while (1) {
		printPrompt();
		if (readInput(&input) == -1)
			break;

		if (strlen(input) <= 1) {
			free(input);
			continue;
		}

		tokenizeInput(input, tokens, &numTokens);

		// Handle built-in commands
		if (handleBuiltInCommands(tokens)) {
			free(input);
			continue;
		}

		// Execute the command
		executeCommand(tokens);

		free(input);
	}

	free(input); // Free input before exiting

	return 0;
}
