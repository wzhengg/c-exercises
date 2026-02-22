#include <stdio.h>

int main(void) {
	int c;
	int nspaces, ntabs, nlines;

	nspaces = ntabs = nlines = 0;
	while ((c = getchar()) != EOF) {
		switch (c) {
			case ' ':
				++nspaces;
				break;
			case '\t':
				++ntabs;
				break;
			case '\n':
				++nlines;
				break;
		}
	}

	printf("spaces=%d tabs=%d lines=%d\n", nspaces, ntabs, nlines);

	return 0;
}
