#include "HiddenFace.h"
#include <stdio.h>

void CreateFaces(HiddenFaces *f) {
    for (int i = 0; i < CAPACITY; i++) {
        f->contents[i] = MARK;
    }
}

boolean isEmpty(HiddenFaces f) {
    for (int i = 0; i < CAPACITY; i++) {
        if (f.contents[i] != MARK) return false;
    }
    return true;
}

boolean isFull(HiddenFaces f) {
    for (int i = 0; i < CAPACITY; i++) {
        if (f.contents[i] == MARK) return false;
    }
    return true;
}

IdxType getFirstIdx(HiddenFaces f) {
    for (int i = 0; i < CAPACITY; i++) {
        if (f.contents[i] != MARK) return i;
    }
    return IDX_UNDEF;
}

IdxType getLastIdx(HiddenFaces f) {
    for (int i = CAPACITY - 1; i >= 0; i--) {
        if (f.contents[i] != MARK) return i;
    }
    return IDX_UNDEF;
}

int length(HiddenFaces f) {
    int count = 0;
    for (int i = 0; i < CAPACITY; i++) {
        if (f.contents[i] != MARK) count++;
    }
    return count;
}

ElType getElmt(HiddenFaces f, IdxType i) {
    return ELMT(f, i);
}

void setElmt(HiddenFaces *f, IdxType i, ElType val) {
    ELMT(*f, i) = val;
}

boolean isIdxValid(HiddenFaces f, IdxType i) {
    return (i >= IDX_MIN && i < CAPACITY);
}

boolean isIdxEff(HiddenFaces f, IdxType i) {
    if (!isIdxValid(f, i)) return false;
    if (isEmpty(f)) return false;
    return (i >= getFirstIdx(f) && i <= getLastIdx(f) && ELMT(f, i) != MARK);
}

void insertFirst(HiddenFaces *f, ElType val) {
    if (isEmpty(*f)) {
        ELMT(*f, CAPACITY / 2) = val;
    } else {
        IdxType first = getFirstIdx(*f);
        ELMT(*f, first - 1) = val;
    }
}

void insertAt(HiddenFaces *f, ElType val, IdxType i) {
    ELMT(*f, i) = val;
}

void insertLast(HiddenFaces *f, ElType val) {
    if (isEmpty(*f)) {
        ELMT(*f, CAPACITY / 2) = val;
    } else {
        IdxType last = getLastIdx(*f);
        ELMT(*f, last + 1) = val;
    }
}

void deleteFirst(HiddenFaces *f, ElType *val) {
    IdxType first = getFirstIdx(*f);
    *val = ELMT(*f, first);
    ELMT(*f, first) = MARK;
}

void deleteAt(HiddenFaces *f, ElType *val, IdxType i) {
    *val = ELMT(*f, i);
    ELMT(*f, i) = MARK;
}

void deleteLast(HiddenFaces *f, ElType *val) {
    IdxType last = getLastIdx(*f);
    *val = ELMT(*f, last);
    ELMT(*f, last) = MARK;
}

void printAll(HiddenFaces f) {
    if (isEmpty(f)) {
        printf("[]\n");
        return;
    }
    IdxType first = getFirstIdx(f);
    IdxType last = getLastIdx(f);
    printf("[");
    boolean firstPrinted = false;
    for (IdxType i = first; i <= last; i++) {
        if (ELMT(f, i) == MARK) continue;
        if (firstPrinted) printf(",");
        printf("'%c'", ELMT(f, i));
        firstPrinted = true;
    }
    printf("]\n");
}

HiddenFaces concat(HiddenFaces f1, HiddenFaces f2) {
    HiddenFaces result;
    CreateFaces(&result);

    int idx = 0;

    if (!isEmpty(f1)) {
        IdxType first1 = getFirstIdx(f1);
        IdxType last1 = getLastIdx(f1);
        for (IdxType i = first1; i <= last1; i++) {
            if (ELMT(f1, i) != MARK) {
                ELMT(result, idx++) = ELMT(f1, i);
            }
        }
    }

    if (!isEmpty(f2)) {
        IdxType first2 = getFirstIdx(f2);
        IdxType last2 = getLastIdx(f2);
        for (IdxType i = first2; i <= last2; i++) {
            if (ELMT(f2, i) != MARK) {
                ELMT(result, idx++) = ELMT(f2, i);
            }
        }
    }

    return result;
}