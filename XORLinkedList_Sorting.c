list *sort(list *start)
{
    if (!start || !start->addr)
        return start;

    list *left = start, *right = start->addr;
    left->addr = NULL;
    right->addr = XOR(right->addr, left);

    left = sort(left);
    right = sort(right);

    for (list *merge = NULL; left || right;) {
        if (!right || (left && left->data < right->data)) {
            list *next = left->addr;
            /*A(head)  B  C*/
            // if next exists, put the address of C in B->addr
            if (next)
                next->addr = XOR(left, next->addr);

            // first node
            if (!merge) {
                start = merge = left;
                merge->addr = NULL;
            }else {
                // put Xor(address of merge's prev, left) in merge->addr
                merge->addr = LL1;
                // put merge in left->addr, become left's prev
                left->addr = LL2;
                // merge keep as the tail of list
                merge = left;
            }
            //left = left->next
            left = next;
        } else {
            list *next = right->addr;
            if (next)
                next->addr = XOR(right, next->addr);

            if (!merge) {
                start = merge = right;
                merge->addr = NULL;
            } else {
                merge->addr = RR1;
                right->addr = RR2;
                merge = right;
            }
            right = next;
        }
    }

    return start;
}
