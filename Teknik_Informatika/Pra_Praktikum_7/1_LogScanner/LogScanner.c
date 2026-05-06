#include "LogScanner.h"
#include <stdio.h>
#include <stdlib.h>

void CreateLogScanner(LogScanner *l, int capacity)
/* I.S. l sembarang, capacity > 0 */
/* F.S. Terbentuk list l kosong dengan kapasitas capacity */
{
    l->buffer = (LogItem *)malloc(capacity * sizeof(LogItem));
    l->nEff = 0;
    l->capacity = capacity;
}

void DealokasiLogScanner(LogScanner *l)
/* I.S. l terdefinisi */
/* F.S. List l dikembalikan ke sistem, l.capacity=0, l.nEff=0 */
{
    free(l->buffer);
    l->capacity = 0;
    l->nEff = 0;
}

boolean IsEmpty(LogScanner l)
/* Mengirimkan true jika list l kosong, false jika tidak */
{
    return l.nEff == 0;
}

boolean IsFull(LogScanner l)
/* Mengirimkan true jika list l penuh, false jika tidak */
{
    return l.nEff == l.capacity;
}

void ExpandList(LogScanner *l)
/* Melipatgandakan kapasitas list (capacity * 2) */
{
    l->capacity *= 2;
    LogItem *newbuf = (LogItem *)malloc(l->capacity * sizeof(LogItem));

    // technically you can use memcpy but whatever
    // manual implementation it is
    for (int i = 0; i < l->nEff; i++) {
        newbuf[i] = l->buffer[i];
    }
    free(l->buffer);
    l->buffer = newbuf;
}

void ShrinkToFit(LogScanner *l)
/* Mengecilkan kapasitas list agar sama dengan nEff */
/* Jika nEff == 0, set kapasitas ke INITIAL_CAPACITY */
{
    if (l->nEff == 0) {
        l->capacity = INITIAL_CAPACITY;
    } else {
        l->capacity = l->nEff;
    }
    LogItem *newbuf = (LogItem *)malloc(l->capacity * sizeof(LogItem));

    // technically you can use memcpy but whatever
    // manual implementation it is
    for (int i = 0; i < l->nEff; i++) {
        newbuf[i] = l->buffer[i];
    }
    free(l->buffer);
    l->buffer = newbuf;
}

void TambahLog(LogScanner *l, LogItem val)
/* Menambahkan elemen LogItem di akhir list */
/* Jika list penuh, list akan menggandakan (kali dua) kapasitas secara otomatis
 */
{
    if (IsFull(*l)) {
        ExpandList(l);
    }
    l->buffer[l->nEff] = val;
    l->nEff++;
}

void HapusLog(LogScanner *l, int idx, LogItem *val)
/* Menghapus log pada indeks tertentu */
/* print "INDEKS INVALID" tanpa tanda kutip diikuti newline, jika idx tidak
 * valid */
/* Elemen sisa digeser ke depan, kapasitas tidak berubah */
{
    if (idx < 0 || idx >= l->nEff) {
        printf("INDEKS INVALID\n");
        return;
    }

    *val = l->buffer[idx];
    for (int i = idx + 1; i < l->nEff; i++) {
        l->buffer[i - 1] = l->buffer[i];
    }
    l->nEff--;
}

void FilterHighSeverity(LogScanner l, LogScanner *l_out)
/* I.S. l terdefinisi, l_out belum terdefinisi */
/* Mengkopi semua log dengan severity == 3 (High) ke l_out */
/* Kapasitas l_out sama dengan jumlah log High yang ditemukan */
/* Jika jumlah log High = 0, maka set kapasitas ke INITIAL_CAPACITY */
{

    int count = 0;
    for (int i = 0; i < l.nEff; i++) {
        if (l.buffer[i].severity == 3) {
            count++;
        }
    }

    if (count == 0) {
        CreateLogScanner(l_out, INITIAL_CAPACITY);
        return;
    }

    CreateLogScanner(l_out, count);
    for (int i = 0; i < l.nEff; i++) {
        if (l.buffer[i].severity == 3) {
            TambahLog(l_out, l.buffer[i]);
        }
    }
}

void CetakStatusList(LogScanner l)
/* Print list saat ini dengan format:
    Capacity: <capacity> | nEff: <nEff>
diikuti dengan:
    [1] TS: <timestamp> | Port: <port> | Sev: <severity>
    ...
    [N] TS: <timestamp> | Port: <port> | Sev: <severity>
jika list berisi, atau:
    LIST KOSONG
jika list kosong.

Semua baris diakhiri newline.
*/
{
    printf("Capacity: %d | nEff: %d\n", l.capacity, l.nEff);
    if (l.nEff == 0) {
        printf("LIST KOSONG\n");
        return;
    }

    for (int i = 0; i < l.nEff; i++) {
        printf("[%d] TS: %d | Port: %d | Sev: %d\n", i + 1,
               l.buffer[i].timestamp, l.buffer[i].port, l.buffer[i].severity);
    }
}
