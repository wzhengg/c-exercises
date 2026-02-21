#include "kv.h"

#include "list.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void kvfree(struct KV *kv) {
	if (!kv) return;
	if (kv->val) free(kv->val);
	free(kv);
}

static struct KV *kvnew(long long key, char *val) {
	struct KV *kv = malloc(sizeof(struct KV));
	if (!kv) return NULL;

	kv->key = key;

	kv->val = malloc(strlen(val) + 1);
	if (!kv->val) {
		kvfree(kv);
		return NULL;
	}
	strcpy(kv->val, val);

	return kv;
}

static struct ListNode *kvfindnode(struct KVStore *s, long long key) {
	struct ListNode *node;
	struct KV *kv;

	for (node = s->l->head; node != NULL; node = node->next) {
		kv = node->data;
		if (kv && kv->key == key) return node;
	}

	return NULL;
}

static struct KV *kvfind(struct KVStore *s, long long key) {
	struct ListNode *node;

	node = kvfindnode(s, key);
	if (!node) return NULL;

	return node->data;
}

struct KVStore *kvstorenew(void) {
	struct KVStore *s = malloc(sizeof(struct KVStore));
	if (!s) return NULL;

	s->l = listnew();
	if (!s->l) {
		kvstorefree(s);
		return NULL;
	}

	return s;
}

void kvstorefree(struct KVStore *s) {
	if (!s) return;
	if (s->l) listfree(s->l);
	free(s);
}

char *kvget(struct KVStore *s, long long key) {
	if (!s) return NULL;

	struct KV *kv = kvfind(s, key);
	if (!kv) return NULL;

	return kv->val;
}

bool kvput(struct KVStore *s, long long key, char *val) {
	if (!s) return false;

	struct ListNode *node;
	struct KV *kv;

	node = kvfindnode(s, key);
	if (node) listremove(s->l, node);

	kv = kvnew(key, val);
	if (!kv) return false;

	return listappend(s->l, kv);
}

bool kvdel(struct KVStore *s, long long key) {
	if (!s) return false;

	struct ListNode *node;

	node = kvfindnode(s, key);
	if (!node) return false;

	listremove(s->l, node);

	return true;
}

void kvclear(struct KVStore *s) {
	struct ListNode *node;

	for (node = s->l->head; node != NULL; node = node->next)
		kvfree(node->data);

	listclear(s->l);
}

void kvprintall(struct KVStore *s) {
	if (!s) return;

	struct ListNode *node;
	struct KV *kv;

	for (node = s->l->head; node != NULL; node = node->next) {
		kv = node->data;
		printf("%lld,%s\n", kv->key, kv->val);
	}
}
