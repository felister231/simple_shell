#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_INPUT_SIZE 1024
#define MAX_TOKEN_SIZE 64
#define MAX_NUM_TOKENS 64


void printPrompt();
int readInput(char **input);
void tokenizeInput(char *input, char **tokens, int *numTokens);
void executeCommand(char **tokens);
int handleBuiltInCommands(char **tokens);
