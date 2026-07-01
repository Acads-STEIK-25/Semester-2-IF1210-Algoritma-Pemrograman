/* File: anomalinangor.c */
#include <stdio.h>
#include "boolean.h"
#include "listberkait.h"

/*
 * DILARANG melakukan iterasi menggunakan kombinasi for loop dan fungsi
 * getElmt() maupun length()! Penggunaan getElmt di dalam loop sangat tidak
 * efisien untuk Linked List dan akan membuat program Anda terkena 
 * Time Limit Exceeded (TLE) pada test case berukuran besar.
*/

/*
 * Fungsi isEscalating
 * Menerima input sebuah list linier L.
 * Mengembalikan true jika nilai elemen list terus meningkat
 * (strictly increasing) dari elemen pertama hingga elemen terakhir.
 * Jika list kosong atau hanya berisi 1 elemen, kembalikan true.
 */
boolean isEscalating(List L);

/*
 * Fungsi peakAnomaly
 * Menerima input sebuah list linier L.
 * Mengembalikan nilai elemen paling besar (maksimum) di dalam list L.
 * Prekondisi (I.S.): L tidak kosong.
 */
int peakAnomaly(List L);

/*
 * Fungsi isEscalating
 * Menerima input sebuah list linier L.
 * Mengembalikan true jika nilai elemen list terus meningkat
 * (strictly increasing) dari elemen pertama hingga elemen terakhir.
 * Jika list kosong atau hanya berisi 1 elemen, kembalikan true.
 */
boolean isEscalating(List L) {
    if (isEmpty(L)) {
        return true;
    }

    Address P = FIRST(L);
    
    while (NEXT(P) != NULL) {
        if (INFO(NEXT(P)) <= INFO(P)) {
            return false;
        }
        P = NEXT(P);
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
    Address P = FIRST(L);
    int max_val = INFO(P);
    
    P = NEXT(P);
    
    while (P != NULL) {
        if (INFO(P) > max_val) {
            max_val = INFO(P);
        }
        P = NEXT(P);
    }
    
    return max_val;
}