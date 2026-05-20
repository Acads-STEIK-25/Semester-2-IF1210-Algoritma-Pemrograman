#include "listsirkuler.h"
#include <stdio.h>
#include <stdlib.h>

/* PROTOTYPE */
/****************** TEST LIST KOSONG ******************/
boolean isEmpty(List l)
/* Mengirim true jika list kosong. Lihat definisi di atas. */
{
    return l.first == NULL;
}

/****************** PEMBUATAN LIST KOSONG ******************/
void CreateList(List *l)
/* I.S. l sembarang             */
/* F.S. Terbentuk list kosong. Lihat definisi di atas. */
{
    l->first = NULL;
}

/****************** Manajemen Memori ******************/
Address allocate(ElType val)
/* Mengirimkan Address hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka Address tidak NULL, dan misalnya */
/* menghasilkan P, maka INFO(P)=val, NEXT(P)=NULL */
/* Jika alokasi gagal, mengirimkan NULL */
{
    Address p = malloc(sizeof(ElmtList));
    if (p == NULL) {
        return NULL;
    }

    p->info = val;
    p->next = NULL;

    return p;
}

void deallocate(Address P)
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian Address P */
{
    free(P);
}

/****************** PRIMITIF BERDASARKAN NILAI ******************/
/*** PENAMBAHAN ELEMEN ***/
void insertFirst(List *l, ElType val)
/* I.S. l mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen pertama dengan nilai val jika alokasi berhasil */
{
    if (isEmpty(*l)) {
        l->first = allocate(val);
        l->first->next = l->first;
        return;
    }

    Address p = l->first;
    while (p->next != l->first) {
        p = p->next;
    }
    p->next = allocate(val);
    p->next->next = l->first;
    l->first = p->next;
}

void insertLast(List *l, ElType val)
/* I.S. l mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen list di akhir: elemen terakhir yang baru */
/* bernilai val jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */
{
    if (isEmpty(*l)) {
        l->first = allocate(val);
        l->first->next = l->first;
        return;
    }

    Address p = l->first;
    while (p->next != l->first) {
        p = p->next;
    }
    p->next = allocate(val);
    p->next->next = l->first;
}

/*** PENGHAPUSAN ELEMEN ***/
void deleteFirst(List *l, ElType *val)
/* I.S. List l tidak kosong  */
/* F.S. val adalah elemen pertama list l sebelum penghapusan */
/*      Elemen list berkurang satu (mungkin menjadi kosong) */
/*      First element yg baru adalah suksesor elemen pertama yang lama */
/*      Alamat elemen terakhir di-dealokasi */
{
    Address p = l->first;
    while (p->next != l->first) {
        p = p->next;
    }

    if (p == l->first) {
        *val = p->info;
        deallocate(p);
        l->first = NULL;
    } else {
        Address tmp = l->first;
        *val = tmp->info;
        l->first = tmp->next;
        deallocate(tmp);
        p->next = l->first;
    }
}

/****************** PROSES SEMUA ELEMEN LIST ******************/
void displayList(List l)
/* I.S. List mungkin kosong */
/* F.S. Jika list tidak kosong, iai list dicetak ke kanan: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika list kosong : menulis [] */
/* Tidak ada tambahan karakter apa pun di awal, akhir, atau di tengah */
{
    if (isEmpty(l)) {
        printf("[]");
        return;
    }

    printf("[");
    Address p = l.first;
    while (p->next != l.first) {
        printf("%d,", p->info);
        p = p->next;
    }
    printf("%d]", p->info);
}
