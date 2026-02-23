#include <stdio.h>

#define MAXLEN 9

#define OUT 0
#define IN  1

int main(void) {
	int c, nc, hist[MAXLEN+1], state, i, j;

	for (i = 0; i <= MAXLEN; i++)
		hist[i] = 0;

	state = OUT;
	while ((c = getchar()) != EOF) {
		if (c != ' ' && c != '\n' && c != '\t') {
			if (state == OUT)
				nc = 0;
			state = IN;
			++nc;
		} else if (state == IN) {
			state = OUT;
			if (nc <= MAXLEN)
				++hist[nc];
		}
	}

	for (i = 1; i <= MAXLEN; i++) {
		printf("%d: ", i);
		for (j = 0; j < hist[i]; j++)
			printf("#");
		printf("\n");
	}

	return 0;
}
