#include <stdio.h>

int main(void) {
	int c, pc;

	for (pc = 0; (c=getchar()) != EOF; pc = c)
		if (c != ' ')
			putchar(c);
		else if (pc != ' ')
			putchar(c);

	return 0;
}
