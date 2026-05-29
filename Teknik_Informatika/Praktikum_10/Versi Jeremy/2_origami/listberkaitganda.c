#include "listberkaitganda.h"
#include <stdio.h>
#include <stdlib.h>

Address newNode(ElType val) {
    Address p = (Address) malloc(sizeof(Node));
    if (p != NULL) {
        INFO(p) = val;
        NEXT(p) = NULL;
        PREV(p) = NULL;
    }
    return p;
}

void CreateList(List *l) {
    FIRST(*l) = NULL;
    LAST(*l) = NULL;
}

boolean isEmpty(List l) {
    return FIRST(l) == NULL;
}

ElType getElmt(List l, int idx) {
    int ctr = 0;
    Address p = FIRST(l);
    while (ctr < idx) {
        ctr++;
        p = NEXT(p);
    }
    return INFO(p);
}

void setElmt(List *l, int idx, ElType val) {
    int ctr = 0;
    Address p = FIRST(*l);
    while (ctr < idx) {
        ctr++;
        p = NEXT(p);
    }
    INFO(p) = val;
}

int indexOf(List l, ElType val) {
    Address p = FIRST(l);
    int idx = 0;
    boolean found = false;

    while (p != NULL && !found) {
        if (INFO(p) == val) {
            found = true;
        } else {
            idx++;
            p = NEXT(p);
        }
    }

    if (found) {
        return idx;
    } else {
        return IDX_UNDEF;
    }
}

void insertFirst(List *l, ElType val) {
    Address p = newNode(val);
    if (p != NULL) {
        if (isEmpty(*l)) {
            FIRST(*l) = p;
            LAST(*l) = p;
        } else {
            NEXT(p) = FIRST(*l);
            PREV(FIRST(*l)) = p;
            FIRST(*l) = p;
        }
    }
}

void insertLast(List *l, ElType val) {
    Address p = newNode(val);
    if (p != NULL) {
        if (isEmpty(*l)) {
            FIRST(*l) = p;
            LAST(*l) = p;
        } else {
            PREV(p) = LAST(*l);
            NEXT(LAST(*l)) = p;
            LAST(*l) = p;
        }
    }
}

void insertAt(List *l, ElType val, int idx) {
    if (idx == 0) {
        insertFirst(l, val);
    } else if (idx == length(*l)) {
        insertLast(l, val);
    } else {
        Address p = newNode(val);
        if (p != NULL) {
            int ctr = 0;
            Address loc = FIRST(*l);
            while (ctr < idx) {
                ctr++;
                loc = NEXT(loc);
            }
            PREV(p) = PREV(loc);
            NEXT(p) = loc;
            NEXT(PREV(loc)) = p;
            PREV(loc) = p;
        }
    }
}

void deleteFirst(List *l, ElType *val) {
    Address p = FIRST(*l);
    *val = INFO(p);
    FIRST(*l) = NEXT(p);
    if (FIRST(*l) != NULL) {
        PREV(FIRST(*l)) = NULL;
    } else {
        LAST(*l) = NULL;
    }
    free(p);
}

void deleteLast(List *l, ElType *val) {
    Address p = LAST(*l);
    *val = INFO(p);
    LAST(*l) = PREV(p);
    if (LAST(*l) != NULL) {
        NEXT(LAST(*l)) = NULL;
    } else {
        FIRST(*l) = NULL;
    }
    free(p);
}

void deleteAt(List *l, int idx, ElType *val) {
    if (idx == 0) {
        deleteFirst(l, val);
    } else if (idx == length(*l) - 1) {
        deleteLast(l, val);
    } else {
        int ctr = 0;
        Address p = FIRST(*l);
        while (ctr < idx) {
            ctr++;
            p = NEXT(p);
        }
        *val = INFO(p);
        NEXT(PREV(p)) = NEXT(p);
        PREV(NEXT(p)) = PREV(p);
        free(p);
    }
}

void displayList(List l) {
    Address p = FIRST(l);
    printf("[");
    while (p != NULL) {
        printf("%d", INFO(p));
        if (NEXT(p) != NULL) {
            printf(",");
        }
        p = NEXT(p);
    }
    printf("]");
}

int length(List l) {
    int ctr = 0;
    Address p = FIRST(l);
    while (p != NULL) {
        ctr++;
        p = NEXT(p);
    }
    return ctr;
}

List concat(List l1, List l2) {
    List l3;
    CreateList(&l3);
    Address p = FIRST(l1);

    while (p != NULL) {
        insertLast(&l3, INFO(p));
        p = NEXT(p);
    }

    p = FIRST(l2);
    while (p != NULL) {
        insertLast(&l3, INFO(p));
        p = NEXT(p);
    }

    return l3;
}
