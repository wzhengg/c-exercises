#include <stdio.h>

int main(int argc, char *argv[]) {
	if (argc == 1) {
		fprintf(stdout, "wunzip: file1 [file2 ...]\n");
		return 1;
	}

	for (int i = 1; i < argc; ++i) {
		FILE *fp = fopen(argv[i], "r");
		if (fp == NULL) {
			fprintf(stdout, "wunzip: cannot open file\n");
			return 1;
		}

		int n;
		char c;

		while (fread(&n, 4, 1, fp) && fread(&c, 1, 1, fp)) {
			for (int j = 0; j < n; ++j) {
				putchar(c);
			}
		}

		if (fclose(fp) != 0) {
			return 1;
		}
	}

	return 0;
}
