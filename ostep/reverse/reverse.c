#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

struct stack {
	char **arr;
	int size;
	int cap;
};

struct stack stack = {.arr=NULL, .size=0, .cap=0};
void stackpush(char *s);
char *stackpop(void);

int is_same_file(FILE *fp1, FILE *fp2);

int main(int argc, char *argv[]) {
	if (argc > 3) {
		fprintf(stderr, "usage: reverse <input> <output>\n");
		exit(1);
	}

	FILE *in, *out;

	in = stdin;
	out = stdout;

	if (argc >= 2) {
		in = fopen(argv[1], "r");
		if (in == NULL) {
			fprintf(stderr, "reverse: cannot open file '%s'\n", argv[1]);
			exit(1);
		}
	}

	if (argc == 3) {
		out = fopen(argv[2], "w");
		if (out == NULL) {
			fprintf(stderr, "reverse: cannot open file '%s'\n", argv[2]);
			exit(1);
		}
	}

	if (is_same_file(in, out)) {
		fprintf(stderr, "reverse: input and output file must differ\n");
		exit(1);
	}

	char *line;
	size_t n;

	while (getline(&line, &n, in) != -1) {
		char *cpy = malloc(n * sizeof(char));
		if (cpy == NULL) {
			fprintf(stderr, "malloc failed\n");
			exit(1);
		}
		strcpy(cpy, line);
		stackpush(cpy);
	}

	while ((line = stackpop()) != NULL) {
		fprintf(out, "%s", line);
	}

	fclose(in);
	fclose(out);

	exit(0);
}

void stackpush(char *s) {
	if (stack.size == stack.cap) {
		stack.cap = stack.cap == 0 ? 1 : stack.cap * 2;
		stack.arr = realloc(stack.arr, stack.cap * sizeof(char *));
		if (stack.arr == NULL) {
			fprintf(stderr, "malloc failed\n");
			exit(1);
		}
	}

	stack.arr[stack.size++] = s;
}

char *stackpop() {
	if (stack.size == 0) {
		return NULL;
	}
	return stack.arr[--stack.size];
}

int is_same_file(FILE *fp1, FILE *fp2) {
	int fno1 = fileno(fp1);
	if (fno1 == -1) {
		exit(1);
	}

	int fno2 = fileno(fp2);
	if (fno2 == -1) {
		exit(1);
	}

	struct stat s1, s2;

	if (fstat(fno1, &s1) == -1) {
		exit(1);
	}
	if (fstat(fno2, &s2) == -1) {
		exit(1);
	}

	return s1.st_dev == s2.st_dev && s1.st_ino == s2.st_ino;
}
