#ifndef MINQUEUE_H
#define MINQUEUE_H

#include "stack.h"

typedef struct {
    Stack sIn;       // Acts as the inbox for enqueueing
    Stack sInMin;    // Parallel stack tracking the minimum of the inbox
    Stack sOut;      // Acts as the outbox for dequeueing
    Stack sOutMin;   // Parallel stack tracking the minimum of the outbox
} MinQueue;

/* *** Konstruktor *** */
void CreateMinQueue(MinQueue *mq);
/* K.A. mq tidak terdefinisi */
/* K.A. Semua empat stack internal diinisialisasi dan kosong */

/* *** Predikat *** */
boolean isMQEmpty(MinQueue mq);
/* Mengembalikan benar jika MinQueue tidak mengandung elemen */

boolean isMQFull(MinQueue mq);
/* Mengembalikan benar jika MinQueue telah mencapai kapasitas gabungan maksimal */

/* *** Mutator *** */
void enqueue(MinQueue *mq, ElType val);
/* K.A. mq tidak penuh */
/* K.A. val ditambahkan ke bagian belakang antrian. 
   Pelacakan minimum internal diperbarui dalam O(1). */

void dequeue(MinQueue *mq, ElType *val);
/* K.A. mq tidak kosong */
/* K.A. val berisi elemen depan antrian. Elemen dihapus.
   Pelacakan minimum internal diperbarui dalam O(1). */

/* *** Aksesor *** */
ElType getMin(MinQueue mq);
/* K.A. mq tidak kosong */
/* K.A. Mengembalikan elemen minimum absolut saat ini dalam MinQueue dalam waktu O(1). */

#endif