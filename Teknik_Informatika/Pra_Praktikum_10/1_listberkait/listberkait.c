#include "listberkait.h"
#include <stdio.h>
#include <stdlib.h>

/****************** MANAJEMEN MEMORI ******************/
Address newNode(ElType val)
/* Mengembalikan address hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka address tidak NULL, dan misalnya */
/* menghasilkan p, maka INFO(p)=val, NEXT(p)=NULL */
/* Jika alokasi gagal, mengirimkan NULL (alokasi gagal jika malloc mengembalikan
 * null) */
/* Catatan: Praktikan WAJIB mengimplementasikan fungsi ini. */
{
    Address addr = malloc(sizeof(Node));
    if (addr == NULL)
        return NULL;

    addr->info = val;
    addr->next = NULL;

    return addr;
}

/* PROTOTYPE */
/****************** PEMBUATAN LIST KOSONG ******************/
void CreateList(List *l)
/* I.S. sembarang             */
/* F.S. Terbentuk list kosong */
{
    *l = NULL;
}

/****************** TEST LIST KOSONG ******************/
boolean isEmpty(List l)
/* Mengembalikan true jika list kosong */
{
    return l == NULL;
}

/****************** GETTER SETTER ******************/
ElType getElmt(List l, int idx)
/* I.S. l terdefinisi, idx indeks yang valid dalam l, yaitu 0..length(l) */
/* F.S. Mengembalikan nilai elemen l pada indeks idx */
{
    Address p = l;
    for (int i = 0; i < idx; i++) {
        p = p->next;
    }
    return p->info;
}

void setElmt(List *l, int idx, ElType val)
/* I.S. l terdefinisi, idx indeks yang valid dalam l, yaitu 0..length(l) */
/* F.S. Mengubah elemen l pada indeks ke-idx menjadi val */
{
    if (isEmpty(*l))
        return;

    Address p = *l;
    for (int i = 0; i < idx; i++) {
        p = p->next;
    }
    p->info = val;
}

int indexOf(List l, ElType val)
/* I.S. l, val terdefinisi */
/* F.S. Mencari apakah ada elemen list l yang bernilai val */
/* Jika ada, mengembalikan indeks elemen pertama l yang bernilai val */
/* Mengembalikan IDX_UNDEF jika tidak ditemukan */
{
    if (isEmpty(l)) {
        return IDX_UNDEF;
    }

    Address p = l;
    int idx = 0;
    while (p->next != NULL && p->info != val) {
        p = p->next;
        idx++;
    }
    if (p->info == val) {
        return idx;
    }
    return IDX_UNDEF;
}

/****************** PRIMITIF BERDASARKAN NILAI ******************/
/*** PENAMBAHAN ELEMEN ***/
void insertFirst(List *l, ElType val)
/* I.S. l mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen pertama dengan nilai val. */
{
    Address n = newNode(val);
    n->next = *l;
    *l = n;
}

void insertLast(List *l, ElType val)
/* I.S. l mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen list di akhir: elemen terakhir yang baru */
/* bernilai val. */
{
    Address n = newNode(val);
    if (isEmpty(*l)) {
        *l = n;
        return;
    }

    Address p = *l;
    while (p->next != NULL) {
        p = p->next;
    }
    p->next = n;
}

void insertAt(List *l, ElType val, int idx)
/* I.S. l tidak mungkin kosong, idx indeks yang valid dalam l, yaitu
 * 0..length(l) */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menyisipkan elemen dalam list pada indeks ke-idx (bukan menimpa elemen di i)
 */
/* yang bernilai val. */
{
    if (idx == 0) {
        insertFirst(l, val);
        return;
    }

    Address prev = *l;
    for (int i = 0; i < idx - 1; i++) {
        prev = prev->next;
    }

    Address n = newNode(val);
    n->next = prev->next;
    prev->next = n;
}

/*** PENGHAPUSAN ELEMEN ***/
void deleteFirst(List *l, ElType *val)
/* I.S. List l tidak kosong  */
/* F.S. Elemen pertama list dihapus: nilai info disimpan pada val */
/*      dan alamat elemen pertama di-dealokasi */
{
    *val = (*l)->info;
    Address tmp = *l;
    (*l) = tmp->next;
    free(tmp);
}

void deleteLast(List *l, ElType *val)
/* I.S. list tidak kosong */
/* F.S. Elemen terakhir list dihapus: nilai info disimpan pada val */
/*      dan alamat elemen terakhir di-dealokasi */
{
    if ((*l)->next == NULL) {
        *val = (*l)->info;
        free(*l);
        *l = NULL;
        return;
    }

    Address p = *l;
    while (p->next->next != NULL) {
        p = p->next;
    }
    *val = p->next->info;
    free(p->next);
    p->next = NULL;
}

void deleteAt(List *l, int idx, ElType *val)
/* I.S. list tidak kosong, idx indeks yang valid dalam l, yaitu 0..length(l) */
/* F.S. val diset dengan elemen l pada indeks ke-idx. */
/*      Elemen l pada indeks ke-idx dihapus dari l */
{
    if (idx == 0) {
        deleteFirst(l, val);
        return;
    }

    Address prev = *l;
    for (int i = 0; i < idx - 1; i++) {
        prev = prev->next;
    }

    *val = prev->next->info;
    Address tmp = prev->next;
    prev->next = tmp->next;
    free(tmp);
}

/****************** PROSES SEMUA ELEMEN LIST ******************/
void displayList(List l)
/* I.S. List mungkin kosong */
/* F.S. Jika list tidak kosong, isi list dicetak ke kanan: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika list kosong : [] */
/* Tidak ada tambahan karakter apa pun di awal, akhir, atau di tengah */
{
    if (isEmpty(l)) {
        printf("[]");
        return;
    }
    printf("[");
    Address p = l;
    printf("%d", p->info);
    p = p->next;
    while (p != NULL) {
        printf(",%d", p->info);
        p = p->next;
    }
    printf("]");
}

int length(List l)
/* Mengembalikan banyaknya elemen list; mengembalikan 0 jika list kosong */
{
    if (isEmpty(l))
        return 0;
    Address p = l;
    int len = 1;
    while (p->next != NULL) {
        p = p->next;
        len++;
    }
    return len;
}

/****************** PROSES TERHADAP LIST ******************/
List concat(List l1, List l2)
/* I.S. l1 dan l2 sembarang */
/* F.S. l1 dan l2 kosong, l3 adalah hasil konkatenasi l1 & l2 */
/* Konkatenasi dua buah list : l1 dan l2    */
/* menghasilkan l3 yang baru (dengan elemen list l1 dan l2 secara beurutan). */
{
    List l3;
    CreateList(&l3);

    while (!isEmpty(l1)) {
        ElType val;
        deleteFirst(&l1, &val);

        insertLast(&l3, val);
    }

    while (!isEmpty(l2)) {
        ElType val;
        deleteFirst(&l2, &val);

        insertLast(&l3, val);
    }

    return l3;
}
