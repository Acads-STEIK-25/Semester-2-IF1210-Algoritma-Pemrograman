#include <stdio.h>
#include "anomalinangor.h"

/*
 * Fungsi isEscalating
 * Menerima input sebuah list linier L.
 * Mengembalikan true jika nilai elemen list terus meningkat
 * (strictly increasing) dari elemen pertama hingga elemen terakhir.
 * Jika list kosong atau hanya berisi 1 elemen, kembalikan true.
 */
boolean isEscalating(List L) {
    if (FIRST(L) == NULL || NEXT(FIRST(L)) == NULL) { 
        return true; 
    }

    Address current = FIRST(L);
    while (NEXT(current) != NULL) {
        if (INFO(current) >= INFO(NEXT(current))) {
            return false; 
        }
        current = NEXT(current);
    }

    return true;
}

/*
 * Fungsi peakAnomaly
 * Menerima input sebuah list linier L.
 * Mengembalikan nilai elemen paling besar (maksimum) di dalam list L.
 * Prekondisi (I.S.): L tidak kosong.
 */
int peakAnomaly(List L) {
    int max = INFO(FIRST(L));

    Address p = NEXT(FIRST(L));
    while (p != NULL) {
        if (INFO(p) > max) { 
            max = INFO(p);
        }
        p = NEXT(p);
    }
    
    return max; 
}