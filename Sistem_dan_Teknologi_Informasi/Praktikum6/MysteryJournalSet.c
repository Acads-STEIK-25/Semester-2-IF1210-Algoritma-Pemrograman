#include "MysteryJournalSet.h"
#include <stdio.h>
#include <stdlib.h>
 
void CREATE_SET(MysteryJournalSet *S) {
    S->count = 0;
}
 
bool IS_EMPTY(const MysteryJournalSet *S) {
    return S->count == 0;
}
 
bool INSERT_PAGE(MysteryJournalSet *S, int x) {
    for (int i = 0; i < S->count; i++) {
        if (S->data[i] == x) {
            return false;
        }
    }
    
    if (S->count >= MAX_PAGE) {
        return false; 
    }
    
    S->data[S->count] = x;
    S->count++;
    return true;
}
 
bool DELETE_PAGE(MysteryJournalSet *S, int x) {
    for (int i = 0; i < S->count; i++) {
        if (S->data[i] == x) {
            for (int j = i; j < S->count - 1; j++) {
                S->data[j] = S->data[j + 1];
            }
            S->count--;
            return true;
        }
    }
    return false;
}
 
bool IS_MEMBER(const MysteryJournalSet *S, int x) {
    for (int i = 0; i < S->count; i++) {
        if (S->data[i] == x) {
            return true;
        }
    }
    return false;
}
 
int CARDINALITY(const MysteryJournalSet *S) {
    return S->count;
}
 
MysteryJournalSet UNION_SET(const MysteryJournalSet *S1, const MysteryJournalSet *S2) {
    MysteryJournalSet result;
    CREATE_SET(&result);
    
    for (int i = 0; i < S1->count; i++) {
        INSERT_PAGE(&result, S1->data[i]);
    }
    
    for (int i = 0; i < S2->count; i++) {
        INSERT_PAGE(&result, S2->data[i]);
    }
    
    return result;
}
 
MysteryJournalSet INTERSECTION_SET(const MysteryJournalSet *S1, const MysteryJournalSet *S2) {
    MysteryJournalSet result;
    CREATE_SET(&result);
    
    for (int i = 0; i < S1->count; i++) {
        if (IS_MEMBER(S2, S1->data[i])) {
            INSERT_PAGE(&result, S1->data[i]);
        }
    }
    
    return result;
}
 
MysteryJournalSet DIFFERENCE_SET(const MysteryJournalSet *S1, const MysteryJournalSet *S2) {
    MysteryJournalSet result;
    CREATE_SET(&result);
    
    for (int i = 0; i < S1->count; i++) {
        if (!IS_MEMBER(S2, S1->data[i])) {
            INSERT_PAGE(&result, S1->data[i]);
        }
    }
    
    return result;
}
 
void PRINT_SET(const MysteryJournalSet *S) {
    if (S->count == 0) {
        printf("{}");
        return;
    }
    
    int temp[MAX_PAGE];
    for (int i = 0; i < S->count; i++) {
        temp[i] = S->data[i];
    }
    
    for (int i = 0; i < S->count - 1; i++) {
        for (int j = 0; j < S->count - i - 1; j++) {
            if (temp[j] > temp[j + 1]) {
                int swap = temp[j];
                temp[j] = temp[j + 1];
                temp[j + 1] = swap;
            }
        }
    }
    
    printf("{");
    for (int i = 0; i < S->count; i++) {
        if (i > 0) printf(", ");
        printf("%d", temp[i]);
    }
    printf("}");
}