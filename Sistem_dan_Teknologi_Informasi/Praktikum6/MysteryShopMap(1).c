#include "MysteryShopMap.h"
#include <stdio.h>
#include <string.h>

void CREATE_MAP(MysteryShopMap *M) {
    M->count = 0;
}

bool IS_EMPTY(const MysteryShopMap *M) {
    return M->count == 0;
}

bool SET_ITEM(MysteryShopMap *M, const char *key, int value) {
    for (int i = 0; i < M->count; i++) {
        if (strcmp(M->data[i].key, key) == 0) {
            M->data[i].value = value;
            return true;
        }
    }
    
    if (M->count >= MAX_ITEM) {
        return false;
    }
    
    strcpy(M->data[M->count].key, key);
    M->data[M->count].value = value;
    M->count++;
    return true;
}

bool UNSET_ITEM(MysteryShopMap *M, const char *key) {
    for (int i = 0; i < M->count; i++) {
        if (strcmp(M->data[i].key, key) == 0) {
            for (int j = i; j < M->count - 1; j++) {
                M->data[j] = M->data[j + 1];
            }
            M->count--;
            return true;
        }
    }
    return false;
}

bool FIND_ITEM(const MysteryShopMap *M, const char *key, int *value) {
    for (int i = 0; i < M->count; i++) {
        if (strcmp(M->data[i].key, key) == 0) {
            *value = M->data[i].value;
            return true;
        }
    }
    return false;
}

int TOTAL_STOCK(const MysteryShopMap *M) {
    int total = 0;
    for (int i = 0; i < M->count; i++) {
        total += M->data[i].value;
    }
    return total;
}

void PRINT_MAP(const MysteryShopMap *M) {
    for (int i = 0; i < M->count; i++) {
        printf("%s %d\n", M->data[i].key, M->data[i].value);
    }
}