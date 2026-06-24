#include "MesinKetik.h"

void CreateList(ListKetik *L) {
    L->nEff = 0;
    L->cursor = 0;
}

int length(ListKetik L) {
    return L.nEff;
}

void typeChar(ListKetik *L, ElType x) {
    if (L->nEff >= CAPACITY) return;
    for (int i = L->nEff; i > L->cursor; i--) {
        L->contents[i] = L->contents[i - 1];
    }
    L->contents[L->cursor] = x;
    L->cursor++;
    L->nEff++;
}

void backspace(ListKetik *L) {
    if (L->cursor == 0) return;
    for (int i = L->cursor - 1; i < L->nEff - 1; i++) {
        L->contents[i] = L->contents[i + 1];
    }
    L->cursor--;
    L->nEff--;
}

void deleteAll(ListKetik *L, ElType x) {
    int newIdx = 0;
    int newCursor = L->cursor;
    for (int i = 0; i < L->nEff; i++) {
        if (L->contents[i] == x) {
            if (i < L->cursor) newCursor--;
        } else {
            L->contents[newIdx++] = L->contents[i];
        }
    }
    L->nEff = newIdx;
    L->cursor = newCursor;
}

void cursorLeft(ListKetik *L) {
    if (L->cursor > 0) L->cursor--;
}

void cursorRight(ListKetik *L) {
    if (L->cursor < L->nEff) L->cursor++;
}

void cursorHome(ListKetik *L) {
    L->cursor = 0;
}

void cursorEnd(ListKetik *L) {
    L->cursor = L->nEff;
}

void printTeks(ListKetik L) {
    for (int i = 0; i < L.nEff; i++) {
        printf("%c", L.contents[i]);
    }
    printf("\n");
}