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

boolean isInTree(BinTree p, int num) {
    if (isTreeEmpty(p)) {
        return false;
    }
    if (ROOT(p).key == num) {
        return true;
    } else if (num < ROOT(p).key) {
        return isInTree(LEFT(p), num);
    } else {
        return isInTree(RIGHT(p), num);
    }
}

int nbLeaf(BinTree p) {
    if (isTreeEmpty(p)) {
        return 0;
    }
    if (isOneElmt(p)) {
        return 1;
    }
    return nbLeaf(LEFT(p)) + nbLeaf(RIGHT(p));
}

int sumLeaf(BinTree p) {
    if (isTreeEmpty(p)) {
        return 0;
    }
    if (isOneElmt(p)) {
        return ROOT(p).key;
    }
    return sumLeaf(LEFT(p)) + sumLeaf(RIGHT(p));
}
