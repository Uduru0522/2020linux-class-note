#include <stddef.h>
struct node {
    int data;
    struct node *next;
} *head;

void insert(struct node *newt) {
    struct node *node = head, *prev = NULL;
    while (node != NULL && node->data < newt->data) {
        prev = node;
        node = node->next;
    }
    newt->next = node;
    if (prev == NULL)
        head = newt;
    else
        prev->next = newt;
}

void insert_rm(struct node *newt)
{
    struct node **link = &head;
    while (*link && AA)
        BB;
    newt->next = *link;
    *link = newt;
}