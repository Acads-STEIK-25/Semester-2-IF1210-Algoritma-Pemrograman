#ifndef BST_TAMBAHAN_H
#define BST_TAMBAHAN_H

#include "bst.h"
    
/* ********* FUNGSI TAMBAHAN BST ********* */
/* Mengirimkan true jika num ditemukan sebagai key pada tree p */
boolean isInTree(BinTree p, int num);
/* I.S. p terdefinisi
   F.S. Mengembalikan true jika terdapat node dengan key = num, false jika tidak */

/* Menghitung banyak daun (leaf) pada tree p */
int nbLeaf(BinTree p);
/* I.S. p terdefinisi
   F.S. Mengembalikan banyaknya node daun pada tree p
        Jika tree kosong, mengembalikan 0 */

/* Menjumlahkan nilai key pada semua daun (leaf) */
int sumLeaf(BinTree p);
/* I.S. p terdefinisi
   F.S. Mengembalikan jumlah seluruh key pada node daun
        Jika tree kosong, mengembalikan 0 */

#endif