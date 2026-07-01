#include "bst.h"

/****************** FUNGSI RANGE SUM ******************/
/* Menghitung jumlah total key dalam range [L, R] dengan mempertimbangkan count */
int rangeSumBST(BinTree p, int L, int R);
/* I.S. p terdefinisi (bisa kosong atau tidak), L dan R terdefinisi
   F.S. Mengembalikan jumlah total dari semua key di dalam BST yang berada di range [L, R]
        Jika sebuah key memiliki count > 1, kontribusinya adalah key * count
        Range bersifat inklusif: L dan R ikut dihitung jika ditemukan
        Jika pohon kosong atau tidak ada node dalam range, return 0 */  

int rangeSumBST(BinTree p, int L, int R) {
    if (p == NIL) {
        return 0;
    }

    if (ROOT(p).key < L) {
        return rangeSumBST(RIGHT(p), L, R);
    }

    if (ROOT(p).key > R) {
        return rangeSumBST(LEFT(p), L, R);
    }

    return (ROOT(p).key * ROOT(p).count) + rangeSumBST(LEFT(p), L, R) + rangeSumBST(RIGHT(p), L, R);
}