#include <stdio.h>

int main(int argc, char *argv[]) {
	if (argc == 1) {
		fprintf(stdout, "wzip: file1 [file2 ...]\n");
		return 1;
	}

	int prev, cur, n;

	prev = -1;
	n = 0;

	for (int i = 1; i < argc; ++i) {
		FILE *fp = fopen(argv[i], "r");
		if (fp == NULL) {
			fprintf(stdout, "wzip: cannot open file\n");
			return 1;
		}

		while ((cur = fgetc(fp)) != EOF) {
			if (prev == -1) {
				n = 1;
			} else if (cur == prev) {
				++n;
			} else {
				fwrite(&n, 4, 1, stdout);
				fwrite(&prev, 1, 1, stdout);
				n = 1;
			}
			prev = cur;
		}

		if (fclose(fp) != 0) {
			return 1;
		}
	}

	fwrite(&n, 4, 1, stdout);
	fwrite(&prev, 1, 1, stdout);

	return 0;
}
