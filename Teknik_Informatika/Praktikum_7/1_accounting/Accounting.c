#include "Accounting.h"
#include <stdio.h>
#include <stdlib.h>

// typedef struct {
//     int idTrx; // unik
//     int idCompany;
//     int timestamp; // unik
//     long long debit;
//     long long kredit;
// } Transaction;
//
// typedef struct {
//     Transaction *buffer;
//     int capacity;
//     int nEff;
// } Journal;

void CreateJournal(Journal *l, int capacity)
/* I.S. l sembarang, capacity > 0 */
/* F.S. Terbentuk list l kosong dengan kapasitas capacity */
{
    l->nEff = 0;
    l->capacity = capacity;
    l->buffer = malloc(capacity * sizeof(Transaction));
}

void DealokasiJournal(Journal *l)
/* I.S. l terdefinisi */
/* F.S. List l dikembalikan ke sistem, l.capacity=0, l.nEff=0 */
{
    l->nEff = 0;
    l->capacity = 0;
    free(l->buffer);
}

boolean IsEmpty(Journal l)
/* Mengirimkan true jika list l kosong, false jika tidak */
{
    return l.nEff == 0;
}

boolean IsFull(Journal l)
/* Mengirimkan true jika list l penuh, false jika tidak */
{
    return l.nEff == l.capacity;
}

void ExpandJournal(Journal *l)
/* Meningkatkan kapasitas list sebesar dua kali lipat */
{
    l->capacity *= 2;
    Transaction *newptr = malloc(l->capacity * sizeof(Transaction));

    for (int i = 0; i < l->nEff; i++) {
        newptr[i] = l->buffer[i];
    }

    free(l->buffer);
    l->buffer = newptr;
}

void InsertLastTrx(Journal *l, Transaction val)
/* Memasukkan Transaction val ke ujung akhir list */
/* Sebelum insert, jika list sudah lebih dari atau sama dengan 75% penuh,
   maka kapasitas list digandakan secara otomatis */
{
    if (l->nEff * 100 / l->capacity >= 75) {
        ExpandJournal(l);
    }

    l->buffer[l->nEff] = val;
    l->nEff++;
}

void CloneJournal(Journal lIn, Journal *lOut)
/* Menyalin seluruh isi lIn ke lOut di alamat memori berbeda.
   Kapasitas lOut disesuaikan tepat sebesar nEff dari lIn. */
{
    CreateJournal(lOut, lIn.nEff);
    for (int i = 0; i < lIn.nEff; i++) {
        lOut->buffer[i] = lIn.buffer[i];
    }
    lOut->nEff = lIn.nEff;
}

long long GetCompanyBalance(Journal l, int idCompany)
/* Mengembalikan total saldo (Total Debit - Total Kredit)
   khusus untuk idCompany tertentu di dalam List. */
/* Keluarkan 0 jika company tidak valid */
{
	long long td = 0;
	long long tk = 0;
    for (int i = 0; i < l.nEff; i++) {
        if (l.buffer[i].idCompany != idCompany)
            continue;

		td += l.buffer[i].debit;
		tk += l.buffer[i].kredit;
    }

	return td - tk;
}

void SortByTimestamp(Journal *l, boolean ascending)
/* Mengurutkan elemen berdasarkan timestamp */
/* Algoritma sorting bebas */
{
    // Bubble sort

    if (l->nEff <= 1)
        return;

    for (int i = 0; i < l->nEff; i++) {
        for (int j = 0; j + i + 1 < l->nEff; j++) {
            boolean asc_should_swap =
                l->buffer[j].timestamp > l->buffer[j + 1].timestamp;
            if ((ascending && asc_should_swap) ||
                (!ascending && !asc_should_swap)) {
                Transaction tmp = l->buffer[j];
                l->buffer[j] = l->buffer[j + 1];
                l->buffer[j + 1] = tmp;
            }
        }
    }
}

void MergeJournal(Journal l1, Journal l2, Journal *lOut)
/* Menggabungkan dua list tidak terurut l1 dan l2
   ke list lOut yang terurut dengan timestamp menaik */
{
    CreateJournal(lOut, l1.nEff + l2.nEff);

	Journal l1s;
	CloneJournal(l1, &l1s);
	Journal l2s;
	CloneJournal(l2, &l2s);

	SortByTimestamp(&l1s, true);
	SortByTimestamp(&l2s, true);

    int p1 = 0;
    int p2 = 0;
    while (p1 < l1s.nEff && p2 < l2s.nEff) {
        if (l1s.buffer[p1].timestamp < l2s.buffer[p2].timestamp) {
            InsertLastTrx(lOut, l1s.buffer[p1]);
            p1++;
        } else {
            InsertLastTrx(lOut, l2s.buffer[p2]);
            p2++;
        }
    }

    while (p1 < l1s.nEff) {
        InsertLastTrx(lOut, l1s.buffer[p1]);
        p1++;
    }
    while (p2 < l2s.nEff) {
        InsertLastTrx(lOut, l2s.buffer[p2]);
        p2++;
    }
}

void PrintJournal(Journal l)
/* Print list saat ini dengan format:
    Capacity: <capacity> | nEff: <nEff>
diikuti dengan:
    [1] TrxID: <idTrx> | CompID: <idCompany> | TS: <timestamp> | D: <debit> | K:
<kredit>
    ...
    [N] TrxID: <idTrx> | CompID: <idCompany> | TS: <timestamp> | D: <debit> | K:
<kredit> jika list berisi, atau: LIST KOSONG jika list kosong.

Semua baris diakhiri newline.
*/
{
    printf("Capacity: %d | nEff: %d\n", l.capacity, l.nEff);

    if (l.nEff == 0) {
        printf("LIST KOSONG\n");
    }

    for (int i = 0; i < l.nEff; i++) {
        printf("[%d] TrxID: %d | CompID: %d | TS: %d | D: %lld | K: %lld\n", i + 1,
                l.buffer[i].idTrx, l.buffer[i].idCompany,
               l.buffer[i].timestamp, l.buffer[i].debit, l.buffer[i].kredit);
    }
}
