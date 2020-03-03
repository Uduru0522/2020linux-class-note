#include <stdint.h>

typedef struct __list list;
struct __list {
    int data;
    struct __list *addr;
};

#define XOR(a, b) ((list *) ((uintptr_t) (a) ^ (uintptr_t) (b)))

// Comment for passing pointer of head
void insert_node(list **l, int d) {
    // Create temporary node for new data
    list *tmp = malloc(sizeof(list));
    tmp->data = d;

    // "If list is empty"
    if (!(*l)) {
        tmp->addr = NULL;
    } else {
        // Insert new node at head
        // (*l)->addr = XOR(prev, next) = XOR(0, next) = next
        // a.k.a. combine prev(temp) and next(original (*l)->addr)
        // into (*l)->next
        (*l)->addr = XOR(tmp, (*l)->addr);
        // Save address of next into temp->addr
        // Since XOR(0, next) == next(l)
        tmp->addr = *l;
    }
    // `tmp` is now head. 
    *l = tmp;

    /*-------------------------------------------------
        If (*l) passed into is the tail of list, 
        Line25 makes 
        (*l)->addr = XOR(XOR(prev of l, 0), tmp),
        So current list is prev => l => tmp

        In Line28, tmp->addr set into XOR(*l, 0) = *l
                r------
                V     |
        prev => l => tmp

        Then in Line31, the order is set into 
        prev => tmp => l, 
        but l->addr is XOR(prev, tmp), broke
    --------------------------------------------------*/
}

void delete_list(list *l) {
    while (l) {
        // l->addr = XOR(0, next) = next,
        // Since l is head
        list *next = l->addr;

        // "If next exists"
        if (next)
            // Get addr of Node#3 from head
            next->addr = XOR(next->addr, l);
        free(l);
        // Set Node#2 as head
        l = next;
    }
}