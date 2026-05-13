#include "queue.h"

/* *** Konstruktor *** */
void CreateQueue(Queue *q)
/* I.S. sembarang */
/* F.S. Sebuah q kosong terbentuk dengan idxHead dan idxTail bernilai IDX_UNDEF
 */
{
    q->idxHead = IDX_UNDEF;
    q->idxTail = IDX_UNDEF;
}

/* ********* Prototype ********* */
boolean isEmpty(Queue q)
/* Mengirim true jika q kosong: idxHead dan idxTail bernilai IDX_UNDEF */
{
    return q.idxHead == IDX_UNDEF && q.idxTail == IDX_UNDEF;
}

boolean isFull(Queue q)
/* Mengirim true jika idxTail sudah mencapai CAPACITY - 1 */
{
    return q.idxTail == CAPACITY - 1;
}

int length(Queue q)
/* Mengirimkan banyaknya elemen queue. Mengirimkan 0 jika q kosong. */
{
    if (isEmpty(q))
        return 0;
    return q.idxTail - q.idxHead + 1;
}

/* *** Primitif Add/Delete *** */
void enqueue(Queue *q, ElType val)
/* Proses: Menambahkan val pada q dengan aturan FIFO */
/* I.S. q mungkin kosong, q TIDAK penuh */
/* F.S. val menjadi TAIL yang baru, idxTail bertambah 1.
        Jika q kosong, idxHead diset ke 0. */
{
    if (isEmpty(*q)) {
        q->buffer[0] = val;
        q->idxHead = 0;
        q->idxTail = 0;
        return;
    }

    q->idxTail++;
    q->buffer[q->idxTail] = val;
}

void dequeue(Queue *q, ElType *val)
/* Proses: Menghapus val pada q dengan aturan FIFO */
/* I.S. q tidak mungkin kosong */
/* F.S. val = nilai elemen HEAD pd I.S., idxHead bertambah 1.
        Jika q menjadi kosong setelah penghapusan (idxHead > idxTail),
        idxHead dan idxTail dikembalikan ke IDX_UNDEF */
{
    *val = q->buffer[q->idxHead];
    q->idxHead++;

    if (q->idxHead > q->idxTail) {
        q->idxHead = IDX_UNDEF;
        q->idxTail = IDX_UNDEF;
    }
}
