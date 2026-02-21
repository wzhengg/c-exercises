#include "list.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

static struct ListNode *nodenew(void *data) {
	struct ListNode *node = malloc(sizeof(struct ListNode));
	if (!node) return NULL;

	node->data = data;
	node->prev = node->next = NULL;

	return node;
}

struct List *listnew(void) {
	struct List *l = malloc(sizeof(struct List));
	if (!l) return NULL;

	l->head = l->tail = NULL;

	return l;
}

struct ListNode *listappend(struct List *l, void *data) {
	if (!l) return NULL;

	struct ListNode *node = nodenew(data);
	if (!node) return NULL;

	if (!l->head) {
		l->head = l->tail = node;
	} else {
		l->tail->next = node;
		node->prev = l->tail;
		l->tail = node;
	}

	return node;
}

bool listremove(struct List *l, struct ListNode *node) {
	if (!l || !node) return false;

	if (node->prev)
		node->prev->next = node->next;
	if (node->next)
		node->next->prev = node->prev;

	if (node == l->head)
		l->head = node->next;
	if (node == l->tail)
		l->tail = node->prev;

	free(node);

	return true;
}

void listclear(struct List *l) {
	if (!l) return;

	struct ListNode *node;

	for (node = l->head; node != NULL; node = node->next)
		listremove(l, node);
}

void listfree(struct List *l) {
	if (!l) return;
	listclear(l);
	free(l);
}
