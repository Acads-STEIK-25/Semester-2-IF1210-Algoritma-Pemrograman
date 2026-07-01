#ifndef RANGE_SUM_BST_H
#define RANGE_SUM_BST_H

#include "bst.h"

/****************** FUNGSI RANGE SUM ******************/
/* Menghitung jumlah total key dalam range [L, R] dengan mempertimbangkan count */
int rangeSumBST(BinTree p, int L, int R);
/* I.S. p terdefinisi (bisa kosong atau tidak), L dan R terdefinisi
   F.S. Mengembalikan jumlah total dari semua key di dalam BST yang berada di range [L, R]
        Jika sebuah key memiliki count > 1, kontribusinya adalah key * count
        Range bersifat inklusif: L dan R ikut dihitung jika ditemukan
        Jika pohon kosong atau tidak ada node dalam range, return 0 */

#endif