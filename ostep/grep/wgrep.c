#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void grep(FILE *in, char *term);

int main(int argc, char *argv[]) {
	if (argc == 1) {
		printf("wgrep: searchterm [file ...]\n");
		return 1;
	}

	char *term = argv[1];
	FILE *in = stdin;

	if (argc == 2) {
		grep(in, term);
		return 0;
	}

	for (int i = 2; i < argc; ++i) {
		in = fopen(argv[i], "r");
		if (in == NULL) {
			printf("wgrep: cannot open file\n");
			return 1;
		}

		grep(in, term);

		if (fclose(in) != 0) {
			return 1;
		}
	}

	return 0;
}

void grep(FILE *in, char *term) {
	char *line = NULL;
	size_t n;

	while (getline(&line, &n, in) != -1) {
		if (strstr(line, term) != NULL) {
			printf("%s", line);
		}
	}

	free(line);
}
