#ifndef ANTREAN_WAHANA_H
#define ANTREAN_WAHANA_H

#include <queue.h>
#include <pengunjung.h>

#define STARVATION_THRESHOLD 3  // Setelah 3x berturut-turut layani prioritas, layani 1x regular

/* Struktur sistem antrean wahana dengan dua queue: prioritas dan regular */
typedef struct {
    Queue prioritas;           // Antrean pengunjung dengan tiket prioritas
    Queue regular;             // Antrean pengunjung dengan tiket regular
    int currentTime;           // Waktu saat ini di sistem
    int priorityServedCount;   // Counter untuk mencegah starvation
} AntreanWahana;

/********** Konstruktor **********/
void CreateAntrean(AntreanWahana *aw, int startTime){
    Queue priority;
    CreateQueue(&priority);
    aw->prioritas = priority;

    Queue regular;
    CreateQueue(&regular);
    aw->regular = regular;

    aw->currentTime = startTime;
    aw->priorityServedCount = 0;
}
/* I.S. Sembarang
   F.S. Membuat sistem antrean wahana baru dengan:
        - Queue prioritas kosong
        - Queue regular kosong
        - currentTime = startTime
        - priorityServedCount = 0 */

/********** Operasi: Status Antrean **********/
boolean isAllEmpty(AntreanWahana aw){
    return (isEmpty(aw.prioritas) && isEmpty(aw.regular));
}
/* Mengirim true jika kedua antrean (prioritas dan regular) kosong */

boolean isPrioritasEmpty(AntreanWahana aw){
    return (isEmpty(aw.prioritas));
}
/* Mengirim true jika antrean prioritas kosong */

boolean isRegularEmpty(AntreanWahana aw){
    return (isEmpty(aw.regular));
}
/* Mengirim true jika antrean regular kosong */

int totalLength(AntreanWahana aw){
    return (length(aw.prioritas) + length(aw.regular));
}
/* Mengirim total jumlah pengunjung di kedua antrean */

int lengthPrioritas(AntreanWahana aw){
    return (length(aw.prioritas));
}
/* Mengirim jumlah pengunjung di antrean prioritas */

int lengthRegular(AntreanWahana aw){
    return (length(aw.regular));
}
/* Mengirim jumlah pengunjung di antrean regular */

/********** Operasi: Manajemen Pengunjung **********/
void AddPengunjung(AntreanWahana *aw, Pengunjung p, boolean isPriority){
    if (isPriority){
        enqueue(&aw->prioritas, p);
    }
    else{
        enqueue(&aw->regular, p);
    }
}
/* Menambahkan pengunjung ke antrean yang sesuai
   I.S. aw terdefinisi, p adalah pengunjung valid
   F.S. Jika isPriority = true, p ditambahkan ke antrean prioritas
        Jika isPriority = false, p ditambahkan ke antrean regular */

boolean ServeNext(AntreanWahana *aw, Pengunjung *served){
    if (isAllEmpty(*aw)) {
        return false;
    }

    if (aw->priorityServedCount >= STARVATION_THRESHOLD && !isRegularEmpty(*aw)) {
        dequeue(&aw->regular, served);
        aw->priorityServedCount = 0; 
        return true;
    }

    if (!isPrioritasEmpty(*aw)) {
        dequeue(&aw->prioritas, served);
        aw->priorityServedCount++;
        return true;
    }

    dequeue(&aw->regular, served);
    aw->priorityServedCount = 0;
    return true;
}
/* Melayani pengunjung berikutnya dengan logika starvation prevention
   I.S. aw terdefinisi
   F.S. Mengembalikan true dan mengisi served dengan pengunjung yang dilayani jika ada
        Mengembalikan false jika kedua antrean kosong
   Logika:
   - Jika priorityServedCount < STARVATION_THRESHOLD dan antrean prioritas tidak kosong:
     layani dari prioritas
   - Jika priorityServedCount >= STARVATION_THRESHOLD dan antrean regular tidak kosong:
     layani dari regular, reset counter
   - Jika salah satu antrean kosong, layani dari yang tidak kosong */

void RemoveTimedOut(AntreanWahana *aw){
    Pengunjung p;

    int lenP = lengthPrioritas(*aw);
    for(int i = 0; i < lenP; i++){
        dequeue(&aw->prioritas, &p);
        if ((aw->currentTime - p.arrivalTime) <= p.patience){
            enqueue(&aw->prioritas, p);
        }
    }

    int lenR = lengthRegular(*aw);
    for(int i = 0; i < lenR; i++){
        dequeue(&aw->regular, &p);
        if ((aw->currentTime - p.arrivalTime) <= p.patience){
            enqueue(&aw->regular, p);
        }
    }
}
/* Menghapus pengunjung yang sudah menunggu terlalu lama
   I.S. aw terdefinisi, currentTime sudah diupdate
   F.S. Semua pengunjung yang (currentTime - arrivalTime) > patience dihapus
        dari kedua antrean */

void UpdateTime(AntreanWahana *aw, int newTime){
    if (newTime >= aw->currentTime) {
        aw->currentTime = newTime;
    }
}
/* Mengupdate waktu sistem
   I.S. aw terdefinisi, newTime >= currentTime
   F.S. currentTime = newTime */

Pengunjung PeekNextPrioritas(AntreanWahana aw){
    return aw.prioritas.buffer[aw.prioritas.idxHead];
}
/* Melihat pengunjung di depan antrean prioritas tanpa menghapus
   I.S. aw terdefinisi, antrean prioritas tidak kosong
   F.S. Mengembalikan pengunjung di HEAD antrean prioritas */

Pengunjung PeekNextRegular(AntreanWahana aw){
    return aw.regular.buffer[aw.regular.idxHead];
}
/* Melihat pengunjung di depan antrean regular tanpa menghapus
   I.S. aw terdefinisi, antrean regular tidak kosong
   F.S. Mengembalikan pengunjung di HEAD antrean regular */

#endif