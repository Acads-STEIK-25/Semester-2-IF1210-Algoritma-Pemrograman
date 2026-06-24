#include "JadwalNangor.h"

void CreateList(ListEkspedisi *L) {
    L->nEff = 0;
}

int length(ListEkspedisi L) {
    return L.nEff;
}

void insertFirst(ListEkspedisi *L, ElType x) {
    for (int i = L->nEff; i > 0; i--) {
        L->contents[i] = L->contents[i-1];
    }
    L->contents[0] = x;
    L->nEff++;
}

void insertLast(ListEkspedisi *L, ElType x) {
    L->contents[L->nEff] = x;
    L->nEff++;
}

void deleteFirst(ListEkspedisi *L, ElType *e) {
    *e = L->contents[0];
    for (int i = 0; i < L->nEff - 1; i++) {
        L->contents[i] = L->contents[i+1];
    }
    L->nEff--;
}

void deleteLast(ListEkspedisi *L, ElType *e) {
    *e = L->contents[L->nEff - 1];
    L->nEff--;
}

int TotalJarak(ListEkspedisi L) {
    int total = 0;
    for (int i = 0; i < L.nEff; i++) {
        total += L.contents[i];
    }
    return total;
}

void printList(ListEkspedisi L) {
    if (L.nEff == 0) {
        printf("[]\n");
        return;
    }
    printf("[");
    for (int i = 0; i < L.nEff; i++) {
        if (i > 0) printf(",");
        printf("%d", L.contents[i]);
    }
    printf("]\n");
}