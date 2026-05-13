#include "stack.h"

/*** Konstruktor/Kreator ***/
void CreateStack(Stack *s)
/* I.S. Sembarang */
/* F.S. Membuat sebuah Stack s yang kosong berkapasitas CAPACITY */
/* jadi indeksnya antara 0..CAPACITY-1 */
{
    s->idxTop = IDX_UNDEF;
}

/* Ciri stack kosong: idxTop bernilai IDX_UNDEF */
/********** Predikat Untuk test keadaan KOLEKSI **********/
boolean isEmpty(Stack s)
/* Mengirim true jika Stack kosong: lihat definisi di atas */
{
    return s.idxTop == IDX_UNDEF;
}

boolean isFull(Stack s)
/* Mengirim true jika Stack penuh */
{
    return s.idxTop + 1 == CAPACITY;
}

int length(Stack s)
/* Mengirim ukuran Stack s saat ini */
{
    return s.idxTop + 1;
}

/*********** Menambahkan sebuah elemen ke Stack **********/
void push(Stack *s, ElType val)
/* Menambahkan val sebagai elemen Stack s.
I.S. s mungkin kosong, tidak penuh
F.S. val menjadi TOP yang baru, TOP bertambah 1 */
{
    if (isFull(*s))
        return;

    s->idxTop++;
    s->buffer[s->idxTop] = val;
}

/*********** Menghapus sebuah elemen Stack **********/
void pop(Stack *s, ElType *val)
/* Menghapus X dari Stack S.
I.S. S tidak mungkin kosong
F.S. X adalah nilai elemen TOP yang lama, TOP berkurang 1 */
{
    if (isEmpty(*s))
        return;

    *val = s->buffer[s->idxTop];
    s->idxTop--;
}
