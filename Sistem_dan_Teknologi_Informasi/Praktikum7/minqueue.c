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

int minOf(int a, int b) {
    return (a < b) ? a : b;
}

void CreateMinQueue(MinQueue *mq) {
    CreateStack(&mq->sIn);
    CreateStack(&mq->sInMin);
    CreateStack(&mq->sOut);
    CreateStack(&mq->sOutMin);
}

boolean isMQEmpty(MinQueue mq) {
    return (isEmpty(mq.sIn) && isEmpty(mq.sOut));
}

boolean isMQFull(MinQueue mq) {
    return (length(mq.sIn) + length(mq.sOut)) >= CAPACITY;
}

void enqueue(MinQueue *mq, ElType val) {
    push(&mq->sIn, val);
    if (isEmpty(mq->sInMin)) {
        push(&mq->sInMin, val);
    } else {
        push(&mq->sInMin, minOf(val, TOP(mq->sInMin)));
    }
}

void transfer(MinQueue *mq) {
    ElType val, dummy;
    while (!isEmpty(mq->sIn)) {
        pop(&mq->sIn, &val);
        pop(&mq->sInMin, &dummy);

        push(&mq->sOut, val);
        if (isEmpty(mq->sOutMin)) {
            push(&mq->sOutMin, val);
        } else {
            push(&mq->sOutMin, minOf(val, TOP(mq->sOutMin)));
        }
    }
}

void dequeue(MinQueue *mq, ElType *val) {
    if (isEmpty(mq->sOut)) {
        transfer(mq);
    }
    pop(&mq->sOut, val);
    ElType dummy;
    pop(&mq->sOutMin, &dummy);
}

ElType getMin(MinQueue mq) {
    if (isEmpty(mq.sOut)) {
        return TOP(mq.sInMin);
    } else if (isEmpty(mq.sIn)) {
        return TOP(mq.sOutMin);
    } else {
        return minOf(TOP(mq.sInMin), TOP(mq.sOutMin));
    }
}