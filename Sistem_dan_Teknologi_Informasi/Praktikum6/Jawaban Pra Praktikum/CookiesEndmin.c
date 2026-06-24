#include <stdio.h>
#include "CookiesEndmin.h"

/* Inisialisasi set kosong. Parameter: S = set yang akan diinisialisasi. */
void CREATE_SET(CookiesEndmin *S) {
    S->count = 0;
}

/* Tambah x jika belum ada. Return true jika berhasil, false jika duplikat/penuh. */
bool INSERT(CookiesEndmin *S, int x) {
    if (IS_MEMBER(S, x) == true || S->count == MAX_COOKIES) {
        return false;
    } else {
        int low = 0, high = S->count - 1, pos = 0; 
        while (low <= high) {
            int mid = (low + high) / 2;
            if (x > S->data[mid]) {
                low = mid + 1; 
            } else {
                high = mid - 1; 
            }
        }
        pos = low;

        int total = S->count;
        for (int i = total; i >= pos + 1; i--) {
            S->data[i] = S->data[i - 1];
        }

        S->data[pos] = x;
        S->count++;
        return true;
    }
}

/* Hapus x jika ada. Return true jika elemen ditemukan dan dihapus. */
bool REMOVE(CookiesEndmin *S, int x) {
    int total = S->count;
    int index = 0;
    if (IS_MEMBER(S, x) == true) {
        for (int i = 0; i < total; i++) {
            if (S->data[i] == x) {
                index = i;
            }
        }

        for (int i = index; i < total - 1; i++) { 
            S->data[i] = S->data[i + 1];
        }
        S->count--;
        return true;
    }
    return false;
}

/* Cek apakah x anggota set. Return true jika ada, false jika tidak. */
bool IS_MEMBER(const CookiesEndmin *S, int x) {
    int total = S->count;
    for (int i = 0; i < total; i++) {
        if (S->data[i] == x) {
            return true;
        }
    }
    return false;
}

/* Jumlah elemen unik saat ini. */
int CARDINALITY(const CookiesEndmin *S) {
    return S->count;
}

/* "output": cetak isi set dengan format {a, b, c}; jika kosong cetak "{}". */
void PRINT_SET(const CookiesEndmin *S) {
    int total = S->count;
    if (total == 0) printf("{}\n");
    else {
        printf("{");
        for (int i = 0; i < total - 1; i++) {
            printf("%d, ", S->data[i]);
        }
        printf("%d", S->data[total - 1]);
        printf("}\n");
    }
}