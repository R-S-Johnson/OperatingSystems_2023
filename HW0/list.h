#include <stdio.h>
#include <stdlib.h>

#ifndef LIST_H
#define LIST_H

struct node {
    int value;
    struct node* next;
};

struct linked_list {
    int size;
    struct node* head;
};

static inline struct linked_list * ll_create(void) {
    struct linked_list* ll = (struct linked_list*)malloc(sizeof(struct linked_list));
    ll->size = 0;
	return ll;
}

static inline int ll_destroy(struct linked_list *ll) {
    if (ll->size == 0) {
        free(ll);
        return 1;
    }
    return 0;
}

static inline void ll_add(struct linked_list *ll, int value) {
    struct node *toEnter = (struct node*)malloc(sizeof(struct node));
    toEnter->value = value;
    struct node *tmp = ll->head;
    ll->head = toEnter;
    toEnter->next = tmp;
    free(tmp);
    ll->size++;
}

static inline int ll_length(struct linked_list *ll) {
	return (ll->size);
}

static inline int ll_remove_first(struct linked_list *ll) {
    if (ll->size == 0) {
        return 0;
    }
    struct node *tmp = ll->head;
    ll->head = tmp->next;
    free(tmp);
    ll->size--;
	return 1;
}

static inline int ll_contains(struct linked_list *ll, int value) {
    if (ll->size == 0) {
        return 0;
    }
    struct node *cur = ll->head;
    for (int i = 0; i < ll->size; i++) {
        if (cur->value == value) {
            return (i+1);
        }
        cur = cur->next;
    }
	return 0;
}

#endif