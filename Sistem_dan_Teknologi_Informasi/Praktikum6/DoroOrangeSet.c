#include <stdio.h>
#include "DoroOrangeSet.h"

/* Inisialisasi set kosong. */
void CREATE_SET(DoroOrangeSet *S) {
    S->count = 0;
}

/* Tambah x jika belum ada. Return true jika berhasil, false jika duplikat/penuh. */
bool ADD_ORANGE(DoroOrangeSet *S, int x) {
    if (IS_MEMBER(S, x) == true || S->count == MAX_ORANGE) {
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

/* Hapus x jika ada. Return true jika berhasil dihapus. */
bool REMOVE_ORANGE(DoroOrangeSet *S, int x) {
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

/* Cek apakah x anggota set. */
bool IS_MEMBER(const DoroOrangeSet *S, int x) {
    int total = S->count;
    for (int i = 0; i < total; i++) {
        if (S->data[i] == x) {
            return true;
        }
    }
    return false;
}

/* Jumlah elemen unik pada set. */
int CARDINALITY(const DoroOrangeSet *S) {
    return S->count;
}

/* Jumlah total diameter semua orange di set. */
int TOTAL_ENERGY(const DoroOrangeSet *S) {
    int total = S->count;
    int count = 0; 
    for (int i = 0; i < total; i++) {
        count += S->data[i];
    }
    return count;
}

/* "output": cetak set dengan format {a, b, c}; jika kosong cetak "{}". */
void PRINT_SET(const DoroOrangeSet *S) {
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