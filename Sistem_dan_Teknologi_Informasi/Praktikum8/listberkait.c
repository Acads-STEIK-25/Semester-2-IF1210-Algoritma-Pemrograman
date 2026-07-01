/* File : listberkait.c */
/* Implementasi ADT list berkait dengan representasi fisik pointer */
#include <stdio.h>
#include "boolean.h"

#define IDX_UNDEF (-1)

/* Definisi Node : */
typedef int ElType;
typedef struct node *Address;
typedef struct node {
    ElType info;
    Address next;
} Node;

#define INFO(p) (p)->info
#define NEXT(p) (p)->next

/****************** DEFINISI LIST ******************/
/* List kosong : FIRST(l) = NULL */
/* Setiap elemen dengan Address p dapat diacu INFO(p), NEXT(p) */
/* Elemen terakhir list: jika addressnya Last, maka NEXT(Last)=NULL */

/* 
 * PENJELASAN TIPE STRUKTUR DATA:
 * 1. Node adalah representasi elemen yang menyimpan data (info) dan tali (next).
 * 2. Address adalah alamat memori dari Node tersebut (pointer ke Node).
 * 3. List adalah nama lain untuk sebuah Address yang menunjuk ke Node pertama (Head).
 *    Oleh karena itu, secara teknis Address adalah List. Namun agar tidak salah paham,
 *    pada praktikum ini List mengacu pada Address pertama pada suatu stuktur list berkait.
 */
typedef Address List;

#define FIRST(l) (l)

/****************** MANAJEMEN MEMORI ******************/
Address newNode(ElType val);
/* Mengembalikan address hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka address tidak NULL, dan misalnya */
/* menghasilkan p, maka INFO(p)=val, NEXT(p)=NULL */
/* Jika alokasi gagal, mengirimkan NULL (alokasi gagal jika malloc mengembalikan null) */
/* Catatan: Praktikan WAJIB mengimplementasikan fungsi ini. */

/* PROTOTYPE */
/****************** PEMBUATAN LIST KOSONG ******************/
void CreateList(List *l);
/* I.S. sembarang             */
/* F.S. Terbentuk list kosong */

/****************** TEST LIST KOSONG ******************/
boolean isEmpty(List l);
/* Mengembalikan true jika list kosong */

/****************** GETTER SETTER ******************/
ElType getElmt(List l, int idx);
/* I.S. l terdefinisi, idx indeks yang valid dalam l, yaitu 0..length(l) */
/* F.S. Mengembalikan nilai elemen l pada indeks idx */

void setElmt(List *l, int idx, ElType val);
/* I.S. l terdefinisi, idx indeks yang valid dalam l, yaitu 0..length(l) */
/* F.S. Mengubah elemen l pada indeks ke-idx menjadi val */

int indexOf(List l, ElType val);
/* I.S. l, val terdefinisi */
/* F.S. Mencari apakah ada elemen list l yang bernilai val */
/* Jika ada, mengembalikan indeks elemen pertama l yang bernilai val */
/* Mengembalikan IDX_UNDEF jika tidak ditemukan */

/****************** PRIMITIF BERDASARKAN NILAI ******************/
/*** PENAMBAHAN ELEMEN ***/
void insertFirst(List *l, ElType val);
/* I.S. l mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen pertama dengan nilai val. */

void insertLast(List *l, ElType val);
/* I.S. l mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen list di akhir: elemen terakhir yang baru */
/* bernilai val. */

void insertAt(List *l, ElType val, int idx);
/* I.S. l tidak mungkin kosong, idx indeks yang valid dalam l, yaitu 0..length(l) */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menyisipkan elemen dalam list pada indeks ke-idx (bukan menimpa elemen di i) */
/* yang bernilai val. */

/*** PENGHAPUSAN ELEMEN ***/
void deleteFirst(List *l, ElType *val);
/* I.S. List l tidak kosong  */
/* F.S. Elemen pertama list dihapus: nilai info disimpan pada val */
/*      dan alamat elemen pertama di-dealokasi */

void deleteLast(List *l, ElType *val);
/* I.S. list tidak kosong */
/* F.S. Elemen terakhir list dihapus: nilai info disimpan pada val */
/*      dan alamat elemen terakhir di-dealokasi */

void deleteAt(List *l, int idx, ElType *val);
/* I.S. list tidak kosong, idx indeks yang valid dalam l, yaitu 0..length(l) */
/* F.S. val diset dengan elemen l pada indeks ke-idx. */
/*      Elemen l pada indeks ke-idx dihapus dari l */

/****************** PROSES SEMUA ELEMEN LIST ******************/
void displayList(List l);
/* I.S. List mungkin kosong */
/* F.S. Jika list tidak kosong, isi list dicetak ke kanan: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika list kosong : [] */
/* Tidak ada tambahan karakter apa pun di awal, akhir, atau di tengah */

int length(List l);
/* Mengembalikan banyaknya elemen list; mengembalikan 0 jika list kosong */

/****************** PROSES TERHADAP LIST ******************/
List concat(List l1, List l2);
/* I.S. l1 dan l2 sembarang */
/* F.S. l1 dan l2 kosong, l3 adalah hasil konkatenasi l1 & l2 */
/* Konkatenasi dua buah list : l1 dan l2    */
/* menghasilkan l3 yang baru (dengan elemen list l1 dan l2 secara beurutan). */

/****************** MANAJEMEN MEMORI ******************/
/* Mengembalikan address hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka address tidak NULL, dan misalnya */
/* menghasilkan p, maka INFO(p)=val, NEXT(p)=NULL */
/* Jika alokasi gagal, mengirimkan NULL (alokasi gagal jika malloc mengembalikan null) */
/* Catatan: Praktikan WAJIB mengimplementasikan fungsi ini. */
Address newNode(ElType val) {
    Address p = (Address) malloc(sizeof(Node));
    if (p != NULL) {
        INFO(p) = val;
        NEXT(p) = NULL;
    }
    return p;
}

/* PROTOTYPE */
/****************** PEMBUATAN LIST KOSONG ******************/
/* I.S. sembarang             */
/* F.S. Terbentuk list kosong */
void CreateList(List *l) {
    FIRST(*l) = NULL;
}

/****************** TEST LIST KOSONG ******************/
/* Mengembalikan true jika list kosong */
boolean isEmpty(List l) {
    return FIRST(l) == NULL;
}

/****************** GETTER SETTER ******************/
/* I.S. l terdefinisi, idx indeks yang valid dalam l, yaitu 0..length(l) */
/* F.S. Mengembalikan nilai elemen l pada indeks idx */
ElType getElmt(List l, int idx) {
    Address p = FIRST(l);
    int i;
    for (i = 0; i < idx; i++) {
        p = NEXT(p);
    }
    return INFO(p);
}

/* I.S. l terdefinisi, idx indeks yang valid dalam l, yaitu 0..length(l) */
/* F.S. Mengubah elemen l pada indeks ke-idx menjadi val */
void setElmt(List *l, int idx, ElType val) {
    Address p = FIRST(*l);
    int i;
    for (i = 0; i < idx; i++) {
        p = NEXT(p);
    }
    INFO(p) = val;
}

/* I.S. l, val terdefinisi */
/* F.S. Mencari apakah ada elemen list l yang bernilai val */
/* Jika ada, mengembalikan indeks elemen pertama l yang bernilai val */
/* Mengembalikan IDX_UNDEF jika tidak ditemukan */
int indexOf(List l, ElType val) {
    Address p = FIRST(l);
    int idx = 0;
    while (p != NULL) {
        if (INFO(p) == val) {
            return idx;
        }
        idx++;
        p = NEXT(p);
    }
    return IDX_UNDEF;
}

/****************** PRIMITIF BERDASARKAN NILAI ******************/
/*** PENAMBAHAN ELEMEN ***/
/* I.S. l mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen pertama dengan nilai val. */
void insertFirst(List *l, ElType val) {
    Address p = newNode(val);
    if (p != NULL) {
        NEXT(p) = FIRST(*l);
        FIRST(*l) = p;
    }
}

/* I.S. l mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen list di akhir: elemen terakhir yang baru */
/* bernilai val. */
void insertLast(List *l, ElType val) {
    if (isEmpty(*l)) {
        insertFirst(l, val);
    } else {
        Address p = newNode(val);
        if (p != NULL) {
            Address last = FIRST(*l);
            while (NEXT(last) != NULL) {
                last = NEXT(last);
            }
            NEXT(last) = p;
        }
    }
}

/* I.S. l tidak mungkin kosong, idx indeks yang valid dalam l, yaitu 0..length(l) */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menyisipkan elemen dalam list pada indeks ke-idx (bukan menimpa elemen di i) */
/* yang bernilai val. */
void insertAt(List *l, ElType val, int idx) {
    if (idx == 0) {
        insertFirst(l, val);
    } else {
        Address p = newNode(val);
        if (p != NULL) {
            Address loc = FIRST(*l);
            int i;
            for (i = 0; i < idx - 1; i++) {
                loc = NEXT(loc);
            }
            NEXT(p) = NEXT(loc);
            NEXT(loc) = p;
        }
    }
}

/*** PENGHAPUSAN ELEMEN ***/
/* I.S. List l tidak kosong  */
/* F.S. Elemen pertama list dihapus: nilai info disimpan pada val */
/*      dan alamat elemen pertama di-dealokasi */
void deleteFirst(List *l, ElType *val) {
    Address p = FIRST(*l);
    *val = INFO(p);
    FIRST(*l) = NEXT(p);
    free(p);
}

/* I.S. list tidak kosong */
/* F.S. Elemen terakhir list dihapus: nilai info disimpan pada val */
/*      dan alamat elemen terakhir di-dealokasi */
void deleteLast(List *l, ElType *val) {
    Address p = FIRST(*l);
    Address loc = NULL;
    
    while (NEXT(p) != NULL) {
        loc = p;
        p = NEXT(p);
    }
    
    if (loc == NULL) {
        /* Kondisi jika list hanya memiliki 1 elemen */
        FIRST(*l) = NULL;
    } else {
        NEXT(loc) = NULL;
    }
    
    *val = INFO(p);
    free(p);
}

/* I.S. list tidak kosong, idx indeks yang valid dalam l, yaitu 0..length(l) */
/* F.S. val diset dengan elemen l pada indeks ke-idx. */
/*      Elemen l pada indeks ke-idx dihapus dari l */
void deleteAt(List *l, int idx, ElType *val) {
    if (idx == 0) {
        deleteFirst(l, val);
    } else {
        Address loc = FIRST(*l);
        int i;
        for (i = 0; i < idx - 1; i++) {
            loc = NEXT(loc);
        }
        Address p = NEXT(loc);
        *val = INFO(p);
        NEXT(loc) = NEXT(p);
        free(p);
    }
}

/****************** PROSES SEMUA ELEMEN LIST ******************/
/* I.S. List mungkin kosong */
/* F.S. Jika list tidak kosong, isi list dicetak ke kanan: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika list kosong : [] */
/* Tidak ada tambahan karakter apa pun di awal, akhir, atau di tengah */
void displayList(List l) {
    printf("[");
    Address p = FIRST(l);
    while (p != NULL) {
        printf("%d", INFO(p));
        if (NEXT(p) != NULL) {
            printf(",");
        }
        p = NEXT(p);
    }
    printf("]");
}

/* Mengembalikan banyaknya elemen list; mengembalikan 0 jika list kosong */
int length(List l) {
    int cnt = 0;
    Address p = FIRST(l);
    while (p != NULL) {
        cnt++;
        p = NEXT(p);
    }
    return cnt;
}

/****************** PROSES TERHADAP LIST ******************/
/* I.S. l1 dan l2 sembarang */
/* F.S. l1 dan l2 kosong, l3 adalah hasil konkatenasi l1 & l2 */
/* Konkatenasi dua buah list : l1 dan l2    */
/* menghasilkan l3 yang baru (dengan elemen list l1 dan l2 secara beurutan). */
List concat(List l1, List l2) {
    List l3;
    CreateList(&l3);
    
    Address p = FIRST(l1);
    while (p != NULL) {
        insertLast(&l3, INFO(p));
        p = NEXT(p);
    }
    
    p = FIRST(l2);
    while (p != NULL) {
        insertLast(&l3, INFO(p));
        p = NEXT(p);
    }
    
    /* Berdasarkan F.S "l1 dan l2 kosong" namun karena dilempar by-value (List l1, List l2)
       dan bukan reference (List *l1), secara teknis kita tidak dapat langsung memodifikasi 
       pointer asal milik fungsi pemanggil agar menjadi NULL secara mutlak.
       Tetapi kita menyalin elemennya dengan sukses ke l3 sebagai hasil yang baru. */
    
    return l3;
}