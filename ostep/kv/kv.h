#ifndef KV_H
#define KV_H

#include "list.h"

#include <stdbool.h>

struct KV {
	long long key;
	char *val;
};

struct KVStore {
	struct List *l;
};

struct KVStore *kvstorenew(void);
void kvstorefree(struct KVStore *s);
char *kvget(struct KVStore *s, long long key);
bool kvput(struct KVStore *s, long long key, char *val);
bool kvdel(struct KVStore *s, long long key);
void kvclear(struct KVStore *s);
void kvprintall(struct KVStore *s);

#endif
