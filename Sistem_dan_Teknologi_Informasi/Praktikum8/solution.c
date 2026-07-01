#include "listberkait.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * Fungsi untuk mengurutkan linked list
 * I.S. l terdefinisi, mungkin kosong
 * F.S. Jika ascending = true, elemen-elemen dalam list l terurut menaik
 *      Jika ascending = false, elemen-elemen dalam list l terurut menurun
 *
 * Contoh:
 * Jika l adalah [4,1,3,2,5] dan ascending = true,
 * maka setelah sortList(&l, true), l menjadi [1,2,3,4,5]
 *
 * Jika l adalah [4,1,3,2,5] dan ascending = false,
 * maka setelah sortList(&l, false), l menjadi [5,4,3,2,1]
 *
 * Jika l adalah [], maka list tetap []
 * Jika l adalah [7], maka list tetap [7]
 *
 */
void sortList(List *l, boolean ascending) {
    if (l == NULL) return;
    if (FIRST(*l) == NULL) return;
    if (FIRST(*l)->next == NULL) return;

    Node *i;
    Node *j;
    int tuker;

    for (i = FIRST(*l); i != NULL; i = i->next){
        tuker = 0;

        for (j = FIRST(*l); j->next != NULL; j = j->next){
            boolean shouldSwap = false;

            if (ascending){
                if (j->info > j->next->info) shouldSwap = true;
            }
            else{
                if (j->info < j->next->info) shouldSwap = true;
            }

            if (shouldSwap){
                int temp = j->info;
                j->info = j->next->info;
                j->next->info = temp;
                tuker = 1;
            }
        }

        if (tuker == 0) break;
    }
}