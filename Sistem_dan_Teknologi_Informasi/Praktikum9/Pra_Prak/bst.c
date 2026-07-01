#include "boolean.h"
#include <stdio.h>
#include <stdlib.h>

/* *** Definisi Tipe TreeNode dengan info berupa ElType bertipe Map (Key dan
 * Count) *** */
typedef struct {
    int key;
    int count;
} ElType;

typedef struct treeNode *Address;
typedef struct treeNode {
    ElType info;
    Address left;
    Address right;
} TreeNode;

typedef Address BinTree;

#define NIL NULL

/* ********* AKSES (Selektor) ********* */
#define ROOT(p) (p)->info
#define LEFT(p) (p)->left
#define RIGHT(p) (p)->right

/* ********* KONSTRUKTOR DAN DEALOKASI ********* */
/* Mengalokasikan sebuah simpul baru dengan info x */
Address newTreeNode(ElType x);
/* I.S. Sembarang
   F.S. Menghasilkan address simpul baru dengan info = x serta anak kiri dan
   kanan = NIL Return NIL jika alokasi gagal */

/* Mengembalikan address p ke sistem */
void deallocTreeNode(Address p);
/* I.S. p terdefinisi
   F.S. p didealokasi (free) */

/* ********* PREDIKAT PENTING ********* */
/* Mengirimkan true jika p adalah pohon kosong */
boolean isTreeEmpty(BinTree p);

/* Mengirimkan true jika p hanya terdiri dari satu simpul
   anak kiri dan kanan bernilai NIL */
boolean isOneElmt(BinTree p);

/* Mengirimkan true jika p hanya memiliki anak kiri */
boolean isUnerLeft(BinTree p);

/* Mengirimkan true jika p hanya memiliki anak kanan */
boolean isUnerRight(BinTree p);

/* Mengirimkan true jika p memiliki dua anak */
boolean isBiner(BinTree p);

/* ********* PEMBENTUK TREE ********* */
/* Membentuk pohon seimbang dari n simpul dengan input x per simpul */
BinTree buildBalancedTree(int n);
/* I.S. n ≥ 0
   F.S. Menghasilkan pohon biner seimbang dengan n simpul,
        setiap simpul diisi dengan input nilai key dan count = 1
   Proses:
      - Jika n = 0, return NIL
      - Setiap simpul diisi dengan input x.key dan count = 1
      - Jumlah simpul anak kiri (nL) = n div 2
      - Jumlah simpul anak kanan(nR) = n - nL - 1
      - Simpul kiri akan direkursif dengan n = nL
      - Simpul kanan akan direkursif dengan n = nR
      - Return nilai root paling atas */

/* ********* OPERASI BST ********* */
/* Menyisipkan x ke dalam BST p */
void insSearchTree(ElType x, BinTree *p);
/* I.S. p mungkin kosong, x terdefinisi
   F.S. Jika x.key sudah ada di p, maka count bertambah
        Jika belum ada, simpul baru ditambahkan di tempat sesuai properti BST
        - Jika pohon kosong, buat node baru
        - Semua simpul pada subpohon kiri < akar p
        - Semua simpul pada subpohon kanan >= akar p */

/* Prosedur pembantu untuk menghapus node maksimum dari subtree kiri */
void delNode(BinTree *p);
/* I.S. *p menunjuk ke subtree kiri dari simpul yang ingin digantikan (p tidak
 * kosong) */
/* F.S. Node paling kanan dari subtree kiri (nilai maksimum) dihapus dari pohon,
         dan anak kirinya (jika ada) dinaikkan menggantikannya */
/* Proses:
   - Jika RIGHT(*p) ≠ NIL, lanjut ke kanan (rekursif)
   - Jika RIGHT(*p) = NIL, berarti node saat ini adalah node maksimum
     → *p digantikan dengan anak kirinya (bisa NIL)
     → node tersebut didealokasi */

/* Menghapus simpul dengan key = x.key dari Binary Search Tree */
void delBTree(BinTree *p, ElType x);
/* I.S. *p menunjuk ke root dari subtree yang sedang diperiksa,
        x.key pasti ada dalam BST */
/* F.S. Simpul dengan nilai key = x.key dihapus dari BST,
        struktur dan sifat BST tetap dipertahankan */
/* Proses:
   - Jika x.key < key node saat ini → rekursif ke kiri
   - Jika x.key > key node saat ini → rekursif ke kanan
   - Jika x.key = key node saat ini:
       - Jika node adalah daun (leaf) → langsung hapus
       - Jika hanya memiliki satu anak → naikkan anak ke atas
       - Jika memiliki dua anak:
           - Cari nilai maksimum di subtree kiri (RIGHT-most dari LEFT(*p))
           - Salin info dari node maksimum ke node saat ini
           - Hapus node maksimum tersebut (dengan delNode) */

/* Mencari node dengan key = value dalam BST */
Address searchNode(BinTree p, int value);
/* I.S. p mungkin kosong, value terdefinisi
   F.S. Mengembalikan address node dengan key = value jika ditemukan,
        mengembalikan NIL jika tidak ditemukan */

/* Mencari node dengan nilai minimum dalam BST */
Address findMinimum(BinTree p);
/* I.S. p mungkin kosong
   F.S. Mengembalikan address node dengan nilai key minimum dalam BST,
        mengembalikan NIL jika pohon kosong */


Address newTreeNode(ElType x) {
    Address p = (Address) malloc(sizeof(TreeNode));

    if (p != NIL) {
        ROOT(p) = x;
        LEFT(p) = NIL;
        RIGHT(p) = NIL;
    }

    return p;
}

void deallocTreeNode(Address p) {
    free(p);
}

boolean isTreeEmpty(BinTree p) {
    return p == NIL;
}

boolean isOneElmt(BinTree p) {
    return p != NIL && LEFT(p) == NIL && RIGHT(p) == NIL;
}

boolean isUnerLeft(BinTree p) {
    return p != NIL && LEFT(p) != NIL && RIGHT(p) == NIL;
}

boolean isUnerRight(BinTree p) {
    return p != NIL && LEFT(p) == NIL && RIGHT(p) != NIL;
}

boolean isBiner(BinTree p) {
    return p != NIL && LEFT(p) != NIL && RIGHT(p) != NIL;
}

BinTree buildBalancedTree(int n) {
    if (n == 0) {
        return NIL;
    }

    int key;
    ElType x;

    scanf("%d", &key);

    x.key = key;
    x.count = 1;

    BinTree p = newTreeNode(x);

    if (p != NIL) {
        int nL = n / 2;
        int nR = n - nL - 1;

        LEFT(p) = buildBalancedTree(nL);
        RIGHT(p) = buildBalancedTree(nR);
    }

    return p;
}

void insSearchTree(ElType x, BinTree *p) {
    if (*p == NIL) {
        x.count = 1;
        *p = newTreeNode(x);
    } else if (x.key == ROOT(*p).key) {
        ROOT(*p).count++;
    } else if (x.key < ROOT(*p).key) {
        insSearchTree(x, &LEFT(*p));
    } else {
        insSearchTree(x, &RIGHT(*p));
    }
}

void delNode(BinTree *p) {
    Address temp;

    if (RIGHT(*p) != NIL) {
        delNode(&RIGHT(*p));
    } else {
        temp = *p;
        *p = LEFT(*p);
        deallocTreeNode(temp);
    }
}

void delBTree(BinTree *p, ElType x) {
    Address temp;
    Address maxLeft;

    if (x.key < ROOT(*p).key) {
        delBTree(&LEFT(*p), x);
    } else if (x.key > ROOT(*p).key) {
        delBTree(&RIGHT(*p), x);
    } else {
        if (isOneElmt(*p)) {
            temp = *p;
            *p = NIL;
            deallocTreeNode(temp);
        } else if (isUnerLeft(*p)) {
            temp = *p;
            *p = LEFT(*p);
            deallocTreeNode(temp);
        } else if (isUnerRight(*p)) {
            temp = *p;
            *p = RIGHT(*p);
            deallocTreeNode(temp);
        } else {
            maxLeft = LEFT(*p);

            while (RIGHT(maxLeft) != NIL) {
                maxLeft = RIGHT(maxLeft);
            }

            ROOT(*p) = ROOT(maxLeft);
            delNode(&LEFT(*p));
        }
    }
}

Address searchNode(BinTree p, int value) {
    if (p == NIL) {
        return NIL;
    } else if (value == ROOT(p).key) {
        return p;
    } else if (value < ROOT(p).key) {
        return searchNode(LEFT(p), value);
    } else {
        return searchNode(RIGHT(p), value);
    }
}

Address findMinimum(BinTree p) {
    if (p == NIL) {
        return NIL;
    }

    while (LEFT(p) != NIL) {
        p = LEFT(p);
    }

    return p;
}