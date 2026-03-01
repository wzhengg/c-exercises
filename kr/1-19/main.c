#include <stdio.h>

#define MAXLINE 1000

void reverse(char s[], int len);
int get_line(char s[], int lim);

int main(void) {
	int len;
	char line[MAXLINE];

	while ((len = get_line(line, MAXLINE)) > 0) {
		if (line[len-1] == '\n')
			--len;
		reverse(line, len);
		printf("%s", line);
	}

	return 0;
}

int get_line(char s[], int lim) {
	int i, c;

	for (i = 0; i<lim-1 && (c=getchar())!=EOF && c!='\n'; ++i)
		s[i] = c;
	if (c == '\n')
		s[i++] = c;
	s[i] = '\0';

	return i;
}

void reverse(char s[], int len) {
	int l, r;
	char tmp;

	for (l=0, r=len-1; l < r; ++l, --r) {
		tmp = s[l];
		s[l] = s[r];
		s[r] = tmp;
	}
}
