#include <stdio.h>

#define NALPHA 26

int main(void) {
	int c, hist[NALPHA], i, j;

	for (i = 0; i < NALPHA; i++)
		hist[i] = 0;

	while ((c = getchar()) != EOF) {
		if ('a' <= c && c <= 'z')
			++hist[c-'a'];
	}

	for (i = 0; i < NALPHA; i++) {
		printf("%c: ", (char) i+'a');
		for (j = 0; j < hist[i]; j++)
			printf("#");
		printf("\n");
	}

	return 0;
}
