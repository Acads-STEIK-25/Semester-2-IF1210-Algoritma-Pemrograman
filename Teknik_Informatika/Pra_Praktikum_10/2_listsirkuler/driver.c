#include "listsirkuler.h"
#include <stdio.h>

int main() {
    {
        printf("=== Sample Test ===\n");
        List l;
        CreateList(&l);

        insertFirst(&l, 10);
        displayList(l);
        printf("\n");

        insertLast(&l, 20);
        displayList(l);
        printf("\n");
    }

    {
        List l;
        CreateList(&l);

        printf("=== insertFirst ===\n");
        for (int i = 0; i < 10; i++) {
            insertFirst(&l, i);
        }
        displayList(l);
        printf("\n");

        printf("=== insertLast ===\n");
        for (int i = 0; i < 10; i++) {
            insertLast(&l, i);
        }
        displayList(l);
        printf("\n");

        printf("=== deleteFirst ===\n");
        for (int i = 0; i < 20; i++) {
            ElType val;
            deleteFirst(&l, &val);
            printf("%d:%d\n", i, val);
        }
        displayList(l);
        printf("\n");
    }

    return 0;
}
