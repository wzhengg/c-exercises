#include <stdio.h>

#define MAXLINE 1000

int get_line(char s[], int lim);
int trimright(char s[], int len);

int main(void) {
	int len;
	char line[MAXLINE];

	while ((len = get_line(line, MAXLINE)) > 0) {
		len = trimright(line, len);
		if (len > 0 && line[0] != '\n')
			printf("%s", line);
	}

	return 0;
}

int get_line(char s[], int lim) {
	int c, i;

	for (i = 0; i<lim-1 && (c=getchar())!=EOF && c!='\n'; ++i)
		s[i] = c;
	if (c == '\n')
		s[i++] = c;
	s[i] = '\0';

	return i;
}

int trimright(char s[], int len) {
	int i;

	i = s[len-1]=='\n' ? len-2 : len-1;
	while (i >= 0 && (s[i] == ' ' || s[i] == '\t'))
		--i;

	if (s[len-1] == '\n')
		s[++i] = '\n';

	s[++i] = '\0';

	return i;
}
