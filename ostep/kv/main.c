#define _DEFAULT_SOURCE

#include "kv.h"

#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define FILENAME "database.txt"

int parseputcmd(char *cmd, long long *keyptr, char **valptr) {
	char *s, *end;

	s = strsep(&cmd, ",");
	if (!cmd || strcmp(s, "p") != 0)
		return -1;

	s = strsep(&cmd, ",");
	if (!cmd)
		return -1;

	errno = 0;
	*keyptr = strtoll(s, &end, 10);
	if (s == end || errno == ERANGE || *end)
		return -1;

	s = strsep(&cmd, ",");
	if (cmd)
		return -1;
	*valptr = s;

	return 0;
}

int parsegetcmd(char *cmd, long long *keyptr) {
	char *s, *end;

	s = strsep(&cmd, ",");
	if (!cmd || strcmp(s, "g") != 0)
		return -1;

	errno = 0;
	*keyptr = strtoll(cmd, &end, 10);
	if (cmd == end || errno == ERANGE || *end)
		return -1;

	return 0;
}

int parsedelcmd(char *cmd, long long *keyptr) {
	char *s, *end;

	s = strsep(&cmd, ",");
	if (!cmd || strcmp(s, "d") != 0)
		return -1;

	errno = 0;
	*keyptr = strtoll(cmd, &end, 10);
	if (cmd == end || errno == ERANGE || *end)
		return -1;

	return 0;
}

int main(int argc, char *argv[]) {
	if (argc == 1) exit(0);

	struct KVStore *store = kvstorenew();
	if (!store) exit(1);

	FILE *fp;
	long long key;
	char *line, *cmd, *val;
	size_t linesize;


	fp = fopen(FILENAME, "r");
	if (!fp) exit(1);

	line = NULL;
	linesize = 0;
	while (getline(&line, &linesize, fp) != -1) {
		val = malloc(linesize);
		if (!val)
			exit(1);
		if (sscanf(line, "%lld,%s", &key, val) != 2)
			exit(1);
		if (!kvput(store, key, val))
			exit(1);
		free(val);
	}

	free(line);
	fclose(fp);

	while (cmd = *++argv) {
		switch (*cmd) {
			case 'p':
				if (parseputcmd(cmd, &key, &val) == 0) {
					if (!kvput(store, key, val)) exit(1);
					continue;
				}
			case 'g':
				if (parsegetcmd(cmd, &key) == 0) {
					if ((val = kvget(store, key)) == NULL)
						printf("%lld not found\n", key);
					else
						printf("%lld,%s\n", key, val);
					continue;
				}
			case 'd':
				if (parsedelcmd(cmd, &key) == 0) {
					if (!kvdel(store, key))
						printf("%lld not found\n", key);
					continue;
				}
			case 'c':
				if (strcmp(cmd, "c") == 0) {
					kvclear(store);
					continue;
				}
			case 'a':
				if (strcmp(cmd, "a") == 0) {
					kvprintall(store);
					continue;
				}
			default:
				printf("bad command\n");
				break;
		}
	}

	fp = fopen(FILENAME, "w");
	if (!fp) exit(1);

	struct ListNode *node;
	struct KV *kv;

	for (node = store->l->head; node != NULL; node = node->next) {
		kv = node->data;
		fprintf(fp, "%lld,%s\n", kv->key, kv->val);
	}

	fclose(fp);

	kvstorefree(store);

	return 0;
}
