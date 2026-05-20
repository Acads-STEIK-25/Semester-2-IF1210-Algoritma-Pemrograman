// Driver file for testing logic validity

#include "listberkait.h"
#include <stdio.h>

int main() {
    {
        List l;
        CreateList(&l);
        printf("=== insertLast ===\n");
        for (int i = 0; i < 10; i++) {
            insertLast(&l, i);
        }

        displayList(l);
        printf("\n");

        for (int i = 0; i < 10; i++) {
            printf("%d:%d\n", i, getElmt(l, i));
        }

        printf("=== setElmt ===\n");
        for (int i = 0; i < 10; i++) {
            setElmt(&l, i, 10 - 1 - i);
        }

        displayList(l);
        printf("\n");

        printf("=== indexOf ===\n");
        for (int i = 0; i < 11; i++) {
            printf("%d: %d\n", i, indexOf(l, i));
        }

        printf("=== deleteLast ===\n");
        for (int i = 0; i < 10; i++) {
            ElType val;
            deleteLast(&l, &val);
            displayList(l);
            printf("\n");
        }

        printf("=== insertFirst ===\n");
        for (int i = 0; i < 10; i++) {
            insertFirst(&l, i);
        }

        displayList(l);
        printf("\n");

        printf("=== deleteFirst ===\n");
        for (int i = 0; i < 10; i++) {
            ElType val;
            deleteFirst(&l, &val);
            displayList(l);
            printf("\n");
        }
    }

    {
        List l;
        CreateList(&l);

        for (int i = 0; i < 10; i++) {
            insertLast(&l, i);
        }

        printf("=== insertAt ===\n");
        for (int i = 0; i < 10; i++) {
            insertAt(&l, i + 10, i * 2);
        }

        displayList(l);
        printf("\n");

        printf("=== deleteAt ===\n");
        for (int i = 0; i < 10; i++) {
            ElType val;
            deleteAt(&l, i, &val);
            printf("V: %d\n", val);
        }

        displayList(l);
        printf("\n");
    }

    {
        printf("=== concat ===\n");

        List l1;
        CreateList(&l1);
        List l2;
        CreateList(&l2);

        for (int i = 0; i < 10; i++) {
            insertLast(&l1, i);
            insertLast(&l2, i);
        }

        printf("Len1: %d\n", length(l1));
        printf("Len2: %d\n", length(l2));

        displayList(l1);
        printf("\n");
        displayList(l2);
        printf("\n");

        List l3 = concat(l1, l2);
        displayList(l3);
        printf("\n");
    }

    return 0;
}
