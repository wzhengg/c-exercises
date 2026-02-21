#include <stdio.h>

int main(int argc, char *argv[]) {
	if (argc == 1) {
		return 0;
	}

	for (int i = 1; i < argc; ++i) {
		FILE *fp = fopen(argv[i], "r");
		if (fp == NULL) {
			printf("wcat: cannot open file\n");
			return 1;
		}

		char buf[128];
		while (fgets(buf, sizeof(buf), fp) != NULL) {
			printf("%s", buf);
		}

		if (fclose(fp) != 0) {
			return 1;
		}
	}

	return 0;
}
