#ifndef LIST_H
#define LIST_H

#include <stdbool.h>

struct ListNode {
	void *data;
	struct ListNode *prev, *next;
};

struct List {
	struct ListNode *head, *tail;
};

struct List *listnew(void);
struct ListNode *listappend(struct List *l, void *data);
bool listremove(struct List *l, struct ListNode *node);
void listclear(struct List *l);
void listfree(struct List *l);

#endif
