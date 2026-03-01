#include <stdio.h>

#define MAXLINE 4

int get_line(char s[], int lim);
void copy(char to[], char from[]);

int main(void) {
	int tmplen, curlen, maxlen;
	char tmpline[MAXLINE], curline[MAXLINE], maxline[MAXLINE];

	curlen = maxlen = 0;
	while ((tmplen = get_line(tmpline, MAXLINE)) > 0) {
		if (curlen == 0)
			copy(curline, tmpline);

		curlen += tmplen;

		if (tmpline[tmplen-1] != '\n')
			continue;

		if (curlen > maxlen) {
			maxlen = curlen;
			copy(maxline, curline);
		}

		curlen = 0;
	}

	if (maxlen > 0)
		printf("len=%d %s", maxlen, maxline);

	return 0;
}

int get_line(char s[], int lim) {
	int c, i;

	for (i = 0; i < lim-1 && (c=getchar())!=EOF && c != '\n'; ++i)
		s[i] = c;
	if (c == '\n')
		s[i++] = c;

	s[i] = '\0';

	return i;
}

void copy(char to[], char from[]) {
	while (*to++ = *from++)
		;
}
