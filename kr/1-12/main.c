#include <stdio.h>

#define OUT 0
#define IN  1

int main(void) {
	int c, state;

	state = OUT;
	while ((c = getchar()) != EOF) {
		if (c != ' ' && c != '\n' && c != '\t') {
			state = IN;
			putchar(c);
		} else if (state == IN) {
			state = OUT;
			putchar('\n');
		}
	}

	return 0;
}
