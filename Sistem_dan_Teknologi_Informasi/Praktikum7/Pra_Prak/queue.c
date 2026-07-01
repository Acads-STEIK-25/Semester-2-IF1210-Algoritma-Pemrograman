#include <stdio.h>
#include <stdlib.h>

#define IDX_UNDEF -1
#define CAPACITY 10
#define boolean unsigned char
#define true 1
#define false 0

/* Definisi elemen dan address */
typedef int ElType;

/* Contoh struktur type Queue: array statik, indeks head dan indeks tail disimpan */
typedef struct {
    ElType buffer[CAPACITY];
    int idxHead;
    int idxTail;
} Queue;

/* Definisi Queue kosong: idxHead = idxTail = IDX_UNDEF. */

/********** AKSES (Selektor) **********/
#define IDX_HEAD(q) (q).idxHead
#define IDX_TAIL(q) (q).idxTail
#define HEAD(q) (q).buffer[(q).idxHead]
#define TAIL(q) (q).buffer[(q).idxTail]

/********** Konstruktor **********/
void CreateQueue(Queue *q){
    q->idxHead = IDX_UNDEF;
    q->idxTail = IDX_UNDEF;

}
/* I.S. Sembarang
   F.S. Membuat sebuah Queue q yang kosong berkapasitas CAPACITY
   jadi indeksnya antara 0..CAPACITY-1
   Ciri Queue kosong: idxHead dan idxTail bernilai IDX_UNDEF */

/********** Operasi: pemeriksaan status Queue **********/
boolean isEmpty(Queue q){
    return (q.idxHead == IDX_UNDEF && q.idxTail == IDX_UNDEF);
}
/* Mengirim true jika q kosong: lihat definisi di atas */

boolean isFull(Queue q){
    return (q.idxHead == 0 && q.idxTail == CAPACITY-1);
}
/* Mengirim true jika penyimpanan q penuh */

int length(Queue q){
    if (isEmpty(q)) return 0;
    return ((q.idxTail-q.idxHead)+1);
}
/* Mengirim jumlah elemen q saat ini */

/*** Primitif Add/Delete ***/
void enqueue(Queue *q, ElType val){
    if (isEmpty(*q)){
        q->idxHead = 0;
        q->idxTail = 0;
        q->buffer[q->idxTail] = val;
    }
    else{
        if (q->idxTail == CAPACITY-1){
            int len = length(*q);
            for (int i = 0; i < len; i++){
                q->buffer[i] = q->buffer[q->idxHead+i];
            }
            q->idxHead = 0;
            q->idxTail = len -1;
        }

        q->idxTail++;
        q->buffer[q->idxTail] = val;
    }
}
/* Proses: Menambahkan val sebagai elemen Queue q.
   I.S. queue mungkin kosong, TIDAK penuh
   F.S. queue bertambah elemen val sebagai tail yang baru, TAIL bergeser ke kanan
   Jika IDX_TAIL(queue)=CAPACITY-1, maka geser isi tabel, shg IDX_HEAD(queue)=0 */

void dequeue(Queue *q, ElType *val){
    *val = q->buffer[q->idxHead];

    if (q->idxHead == q->idxTail){
        q->idxHead = IDX_UNDEF;
        q->idxTail = IDX_UNDEF;
    }
    else{
        q->idxHead++;
    }
    
}
/* Menghapus head dari Queue q.
   I.S. queue tidak kosong
   F.S. val berisi nilai head yang lama.
   Jika queue tidak menjadi kosong,
   queue.idxHead berpindah ke elemen berikutnya pada queue.
   Jika queue menjadi kosong,
   queue.idxHead dan queue.idxTail menjadi bernilai IDX_UNDEF. */

ElType front(Queue q){
    return q.buffer[q.idxHead];
}