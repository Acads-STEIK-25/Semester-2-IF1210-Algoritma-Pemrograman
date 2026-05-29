/* File : mergeportal.h */
/* Header untuk operasi penggabungan sequence portal dimensi */
/* Menggunakan ADT List Sirkuler sebagai basis */

#ifndef MERGEPORTAL_H
#define MERGEPORTAL_H

#include "listsirkuler.h"

/****************** OPERASI PENCARIAN ******************/
Address findMax(List L);
/* Mencari dan mengembalikan Address node dengan nilai maksimum dalam list L */
/* I.S. L tidak kosong */
/* F.S. Mengembalikan Address node dengan INFO tertinggi */
/*      Jika ada beberapa nilai maksimum yang sama, kembalikan yang pertama ditemukan */

Address findMin(List L);
/* Mencari dan mengembalikan Address node dengan nilai minimum dalam list L */
/* I.S. L tidak kosong */
/* F.S. Mengembalikan Address node dengan INFO terendah */
/*      Jika ada beberapa nilai minimum yang sama, kembalikan yang pertama ditemukan */

/****************** OPERASI KALKULASI ******************/
int sumList(List L);
/* Menghitung total sum dari semua nilai node dalam list L */
/* I.S. L mungkin kosong */
/* F.S. Mengembalikan jumlah total semua INFO dalam list */
/*      Jika list kosong, mengembalikan 0 */

/****************** OPERASI PENGGABUNGAN ******************/
List concatCircular(List A, List B);
/* Menggabungkan dua circular list A dan B dengan aturan khusus untuk stabilitas portal */
/* I.S. A dan B adalah circular list yang tidak kosong */
/* F.S. Mengembalikan circular list hasil gabungan dengan algoritma:
        1. Cari node dengan nilai MAX di list A
        2. Cari node dengan nilai MIN di list B
        3. Hubungkan node MAX(A) dengan node MIN(B)
        4. Setelah semua node B, buat node baru dengan nilai = sumList(A) + sumList(B)
        5. Hubungkan kembali ke sisa node A, membentuk lingkaran yang utuh
        
        Contoh:
        A = [1,5,3] (circular, max=5)
        B = [2,4] (circular, min=2)
        sum(A)=9, sum(B)=6, node penghubung=15
        
        Hasil = [1,5,2,4,15,3] (circular)
        
        Penjelasan alur:
        - Dimulai dari FIRST(A): 1
        - Lanjut hingga MAX(A): 5
        - Sambung ke MIN(B): 2
        - Lanjut seluruh B: 4
        - Node penghubung: 15
        - Sisa A setelah max: 3
        - Kembali ke awal: 1
        
        List A dan B menjadi tidak terdefinisi setelah operasi ini */

#endif