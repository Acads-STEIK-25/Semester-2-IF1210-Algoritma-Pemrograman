#include <stdio.h>
#include "listberkait.h"

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
    return (FIRST(l) == NULL);
}

/****************** GETTER SETTER ******************/

/* I.S. l terdefinisi, idx indeks yang valid dalam l, yaitu 0..length(l) */
/* F.S. Mengembalikan nilai elemen l pada indeks idx */
ElType getElmt(List l, int idx) {
    Address p = FIRST(l);
    int i = 0; 
    while (i < idx) { 
        p = NEXT(p);
        i++;
    }
    return INFO(p);
}

/* I.S. l terdefinisi, idx indeks yang valid dalam l, yaitu 0..length(l) */
/* F.S. Mengubah elemen l pada indeks ke-idx menjadi val */
void setElmt(List *l, int idx, ElType val) {
    Address p = FIRST(*l);
    int i = 0; 
    while (i < idx) { 
        p = NEXT(p);
        i++;
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
        p = NEXT(p);
        idx++;
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
    Address p = newNode(val);
    if (p == NULL) return; 

    if (isEmpty(*l)) { 
        FIRST(*l) = p;
    } else { 
        Address last = FIRST(*l);
        while (NEXT(last) != NULL) {
            last = NEXT(last);
        }
        NEXT(last) = p;
    }
}

/* I.S. l tidak mungkin kosong, idx indeks yang valid dalam l, yaitu 0..length(l) */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menyisipkan elemen dalam list pada indeks ke-idx (bukan menimpa elemen di i) */
/* yang bernilai val. */
void insertAt(List *l, ElType val, int idx) {
    if (idx == 0) { 
        insertFirst(l, val);
        return;
    }

    Address prev = FIRST(*l);
    int i = 0; 
    while (i < idx - 1) { 
        prev = NEXT(prev);
        i++;
    }

    Address p = newNode(val);
    if (p != NULL) {
        NEXT(p) = NEXT(prev);
        NEXT(prev) = p;
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
    if (NEXT(FIRST(*l)) == NULL) { 
        *val = INFO(FIRST(*l));
        free(FIRST(*l));
        FIRST(*l) = NULL;
        return;
    }

    Address prev = FIRST(*l);
    while (NEXT(NEXT(prev)) != NULL) { 
        prev = NEXT(prev);
    }

    Address last = NEXT(prev);
    *val = INFO(last);
    NEXT(prev) = NULL;
    free(last);
}

/* I.S. list tidak kosong, idx indeks yang valid dalam l, yaitu 0..length(l) */
/* F.S. val diset dengan elemen l pada indeks ke-idx. */
/*      Elemen l pada indeks ke-idx dihapus dari l */
void deleteAt(List *l, int idx, ElType *val) {
    if (idx == 0) { 
        deleteFirst(l, val);
        return;
    }

    Address prev = FIRST(*l);
    int i = 0; 
    while (i < idx - 1) {
        prev = NEXT(prev);
        i++;
    }

    Address target = NEXT(prev);
    *val = INFO(target);
    NEXT(prev) = NEXT(target);
    free(target);
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
    int count = 0; 
    Address p = FIRST(l);
    while (p != NULL) { 
        count++;
        p = NEXT(p);
    }
    return count; 
}

/****************** PROSES TERHADAP LIST ******************/

/* I.S. l1 dan l2 sembarang */
/* F.S. l1 dan l2 kosong, l3 adalah hasil konkatenasi l1 & l2 */
/* Konkatenasi dua buah list : l1 dan l2    */
/* menghasilkan l3 yang baru (dengan elemen list l1 dan l2 secara beurutan). */
List concat(List l1, List l2) {
    List result; 
    FIRST(result) = NULL;

    if (isEmpty(l1) && isEmpty(l2)) { 
        return result;
    }

    if (isEmpty(l1)) {
        FIRST(result) = FIRST(l2);
        FIRST(l2) = NULL;
        return result;
    }

    if (isEmpty(l2)) { 
        FIRST(result) = FIRST(l1);
        FIRST(l1) = NULL;
        return result; 
    }

    FIRST(result) = FIRST(l1);
    Address last = FIRST(l1);
    while (NEXT(last) != NULL) {
        last = NEXT(last);
    }
    NEXT(last) = FIRST(l2);

    FIRST(l1) = NULL;
    FIRST(l2) = NULL; 

    return result;
}