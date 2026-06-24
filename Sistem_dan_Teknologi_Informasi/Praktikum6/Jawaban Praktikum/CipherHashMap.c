#include "CipherHashMap.h"
#include <stdio.h>
#include <string.h>

void CREATE_HASHMAP(CipherHashMap *M) {
    M->count = 0;
    for (int i = 0; i < TABLE_SIZE; i++) {
        M->table[i].status = SLOT_EMPTY;
    }
}

int HASH_FUNCTION(const char *key) {
    int sum = 0;
    for (int i = 0; key[i] != '\0'; i++) {
        sum += (unsigned char) key[i];
    }
    return sum % TABLE_SIZE;
}

bool SET_SPELL(CipherHashMap *M, const char *key, int value) {
    int hash = HASH_FUNCTION(key);
    int i = hash;
    int first_deleted = -1;
    
    while (1) {
        if (M->table[i].status == SLOT_EMPTY) {
            int target = (first_deleted != -1) ? first_deleted : i;
            strcpy(M->table[target].key, key);
            M->table[target].value = value;
            M->table[target].status = SLOT_OCCUPIED;
            M->count++; 
            return true;
        } else if (M->table[i].status == SLOT_DELETED && first_deleted == -1) {
            first_deleted = i;
        } else if (M->table[i].status == SLOT_OCCUPIED && strcmp(M->table[i].key, key) == 0) {
            M->table[i].value = value;
            return true;
        }
    
        i = (i + 1) % TABLE_SIZE;
        
        if (i == hash) {
            return false;
        }
    }
}

bool UNSET_SPELL(CipherHashMap *M, const char *key) {
    int hash = HASH_FUNCTION(key);
    int i = hash;
    
    while (1) {
        if (M->table[i].status == SLOT_EMPTY) {
            return false;
        } else if (M->table[i].status == SLOT_OCCUPIED && strcmp(M->table[i].key, key) == 0) {
            M->table[i].status = SLOT_DELETED;
            M->count--;
            return true;
        }

        i = (i + 1) % TABLE_SIZE;
        
        if (i == hash) {
            return false;
        }
    }
}

bool FIND_SPELL(const CipherHashMap *M, const char *key, int *value) {
    int hash = HASH_FUNCTION(key);
    int i = hash;
    
    while (1) {
        if (M->table[i].status == SLOT_EMPTY) {
            return false;
        } else if (M->table[i].status == SLOT_OCCUPIED && strcmp(M->table[i].key, key) == 0) {
            *value = M->table[i].value;
            return true;
        }
        
        i = (i + 1) % TABLE_SIZE;
        
        if (i == hash) {
            return false;
        }
    }
}

void PRINT_HASHMAP(const CipherHashMap *M) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (M->table[i].status == SLOT_OCCUPIED) {
            printf("%s %d\n", M->table[i].key, M->table[i].value);
        }
    }
}