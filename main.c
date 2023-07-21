#include "shell.h"
int main() {
	char *input = NULL;
	char *tokens[MAX_NUM_TOKENS];
	int numTokens;

	while (1) {
		printPrompt();
		if (readInput(&input) == -1)
			break;

		if (strlen(input) <= 1) {
			free(input);
			continue;
		}

		tokenizeInput(input, tokens, &numTokens);

		if (handleBuiltInCommands(tokens)) {
			free(input);
			continue;
		}

		
		executeCommand(tokens);

		free(input);
	}

	free(input);

	return 0;
}
