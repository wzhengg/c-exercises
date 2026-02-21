#include <ctype.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define PATH "/bin"
#define PROMPT "wish> "

struct command {
	char **tokens;
	size_t size;
	size_t cap;
};

void error(void) {
	char *msg = "An error has occurred\n";
	write(STDERR_FILENO, msg, strlen(msg));
}

void fatal(void) {
	exit(1);
}

void skipwhitespace(char **linep) {
	while (**linep && isspace(**linep))
		++*linep;
}

struct command parseline(char *line) {
	struct command cmd;
	char *token;

	cmd.tokens = NULL;
	cmd.cap = cmd.size = 0;

	skipwhitespace(&line);

	if (*line == '\0')
		return cmd;

	while ((token = strsep(&line, " \t\n\v\f\r"))) {
		/* after skipping trailing whitespace, token will be an empty string */
		if (*token == '\0')
			break;

		if (cmd.size == cmd.cap) {
			cmd.cap = cmd.cap ? cmd.cap*2 : 1;
			cmd.tokens = realloc(cmd.tokens, (cmd.cap+1) * sizeof(char *));
			if (!cmd.tokens)
				fatal();
		}
		
		cmd.tokens[cmd.size++] = token;

		/* line is NULL if strsep reaches end of string without finding delim */
		if (line)
			skipwhitespace(&line);
	}

	/* NULL-terminate tokens so it's ready for use by execv */
	cmd.tokens[cmd.size] = NULL;

	return cmd;
}

int main(int argc, char *argv[]) {
	if (argc > 2)
		exit(1);

	FILE *in;
	char *line;
	size_t linecap;
	ssize_t linelen;
	struct command cmd;
	pid_t pid;
	int status;

	in = stdin;
	if (argc == 2) {
		in = fopen(argv[1], "r");
		if (!in)
			fatal();
	}

	line = NULL;
	linecap = 0;

	while (1) {
		fprintf(stdout, PROMPT);

		if ((linelen = getline(&line, &linecap, in)) == -1)
			exit(1);

		cmd = parseline(line);
		if (!cmd.size)
			continue;

		if (strcmp(*cmd.tokens, "exit") == 0) {
			if (cmd.size != 1) {
				error();
				continue;
			}
			exit(0);
		} else if (strcmp(*cmd.tokens, "cd") == 0) {
			if (cmd.size != 2) {
				error();
			} else {
				if (chdir(cmd.tokens[1]) == -1)
					error();
			}
			continue;
		} else if (strcmp(*cmd.tokens, "path") == 0) {
			continue;
		}

		char execpath[100];
		sprintf(execpath, "%s/%s", PATH, *cmd.tokens);

		if (access(execpath, X_OK) == -1) {
			error();
			continue;
		}

		switch (pid = fork()) {
			case -1:
				error();
				break;
			case 0:
				if (execv(execpath, cmd.tokens))
					exit(1);
			default:
				waitpid(pid, &status, 0);
		}

		free(cmd.tokens);
	}

	free(line);

	exit(0);
}
