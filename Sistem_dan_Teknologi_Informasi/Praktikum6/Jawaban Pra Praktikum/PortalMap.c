#include <stdio.h>
#include "PortalMap.h"

/* Inisialisasi map kosong. Parameter: M = map yang akan diinisialisasi. */
void CREATE_MAP(PortalMap *M) {
    M->count = 0;
}

/* Tambah/update pasangan key-value. Jika key sudah ada, value diperbarui. */
void PUT(PortalMap *M, const char *key, int value) {
    int total = M->count;
    for (int i = 0; i < total; i++) {
        if (strcmp(M->records[i].key, key) == 0) {
            M->records[i].value = value;
            return;
        }
    }
    strcpy(M->records[total].key, key);
    M->records[total].value = value;
    M->count++;
}

/* Ambil value dari key. Return true jika key ditemukan, false jika tidak. */
bool GET(const PortalMap *M, const char *key, int *value) {
    int total = M->count;
    for (int i = 0; i < total; i++) {
        if (strcmp(M->records[i].key, key) == 0) {
            *value = M->records[i].value;
            return true;
        }
    }
    return false; 
}

/* Cek apakah key ada di map. Return true jika ada, false jika tidak. */
bool EXISTS(const PortalMap *M, const char *key) {
    int total = M->count;
    for (int i = 0; i < total; i++) {
        if (strcmp(M->records[i].key, key) == 0) {
            return true;
        }
    }
    return false; 
}

/* Hapus key jika ada. Return true jika berhasil dihapus, false jika tidak ditemukan. */
bool REMOVE_KEY(PortalMap *M, const char *key) {
    int total = M->count;
    for (int i = 0; i < total; i++) {
        if (strcmp(M->records[i].key, key) == 0) {
            for (int j = i; j < total - 1; j++) {
                M->records[j] = M->records[i + 1];
            }
            M->count--;
            return true;
        }
    }
    return false;
}

/* Jumlah key aktif saat ini. */
int SIZE(const PortalMap *M) {
    return M->count;
}