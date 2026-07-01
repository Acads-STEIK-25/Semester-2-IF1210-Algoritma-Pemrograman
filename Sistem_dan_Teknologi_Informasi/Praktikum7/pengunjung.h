#ifndef PENGUNJUNG_H
#define PENGUNJUNG_H

/* Struktur data pengunjung wahana */
typedef struct {
    int id;           // ID unik pengunjung
    int arrivalTime;  // Waktu kedatangan pengunjung
    int patience;     // Batas waktu menunggu (dalam satuan waktu)
} Pengunjung;

#endif