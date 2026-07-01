#include "listberkait.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * Fungsi untuk membalik linked list secara in-place
 * I.S. l terdefinisi, mungkin kosong
 * F.S. Elemen-elemen dalam list l dibalik urutannya
 *
 * Contoh:
 * Jika l adalah [1,2,3,4,5], maka setelah reverseList(&l), l menjadi [5,4,3,2,1]
 * Jika l adalah [], maka setelah reverseList(&l), l tetap []
 * Jika l adalah [1], maka setelah reverseList(&l), l tetap [1]
 *
 */
void reverseList(List *l) {

    // TODO: IMPLEMENTASI
    Node *prev = NULL;
    Node *next = NULL;
    Node *current = FIRST(*l);

    if (current == NULL) return;

    while (current != NULL){
        next = current->next;
        current->next = prev;   
        prev = current;
        current = next;
    }

    FIRST(*l) = prev;

}