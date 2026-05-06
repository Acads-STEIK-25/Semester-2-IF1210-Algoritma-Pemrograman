// Extra notes
//
// allowing ELEM_UNDEF within the list and then absolutely not defining
// the behavior of such elements in the face of operations such as
// insert, delete, min, max, and others
// is just shoddy behavior coming from the problem makers...
//
// "Definisi elemen terakhir yang terdefinisi" ah yes
// and then what about the ELEM_UNDEF, are those considered defined?
// do we act as if they do not exist and find the last element before that?
//
// What about insertion?
// Apparently overwriting undefined elements is straight up wrong
// yet that is not mentioned in the code comments.
//
// So is it meant to be a sentinel value that represents a gap
// or a sentinel value that represents not a gap but an invalid entity?
// One infers it may be filled in with new elements, the other cannot.
// Why conflate the term "terdefinisi" with both type invariants..?
//
// Call me pedantic, but type safety and rigor matters when we're talking about
// Abstract Data Types. More so in the year 2026 with how progrmaming languages
// and programming paradigms are now being constructed to prevent common
// programmer mistakes due to ambiguous or otherwise undefined behavior of the
// invariants being upheld.

#include "ListAnomali.h"
#include <stdint.h>
#include <stdio.h>

/* Indeks yang digunakan [IDX_MIN..MAX_CAPACITY - 1] */
/* Jika T adalah ListAnomali, */
/* Maka cara akses:
 * T.nEff untuk mengetahui banyaknya elemen saat ini
 * T.buffer untuk mengakses seluruh nilai elemen list
 * T.buffer[i] untuk mengakses elemen ke-i */
/* Definisi :
 * list kosong: T.nEff = 0
 * list penuh: T.nEff = MAX_CAPACITY
 * Definisi elemen pertama : T.buffer[i] dengan i=IDX_MIN
 * Definisi elemen terakhir yang terdefinisi: T.buffer[i] dengan i=(T.nEff -
 * 1)*/

/* ********** KONSTRUKTOR ********** */
/* Konstruktor : create list kosong */
void CreateListAnomali(ListAnomali *T)
/* I.S. T sembarang */
/* F.S. Terbentuk list T kosong dengan kapasitas MAX_CAPACITY */
{
    for (IdxType i = 0; i < MAX_CAPACITY; ++i) {
        T->buffer[i] = ELEM_UNDEF;
    }
    T->nEff = 0;
}

/* ********** SELEKTOR ********** */
/* *** Banyaknya elemen *** */
int countAnomaly(ListAnomali T)
/* Mengirimkan banyaknya anomali efektif list */
/* Mengirimkan nol jika list kosong */
{
    int actuallyEffective = 0;
    for (int i = 0; i < T.nEff; i++) {
        if (T.buffer[i] != ELEM_UNDEF)
            actuallyEffective++;
    }
    return actuallyEffective;
}

/* *** Daya tampung anomali list *** */
int maxNbAnomaly(ListAnomali T)
/* Mengirimkan maksimum elemen yang dapat ditampung oleh list (MAX_CAPACITY) */
{
    return MAX_CAPACITY;
}

/* ********** Test Indeks yang valid ********** */
boolean isIdxEff(ListAnomali T, IdxType i)
/* Prekondisi : List T sembarang (bisa kosong atau bisa terisi), i sembarang */
/* Mengirimkan true jika i adalah indeks yang terdefinisi utk list yaitu antara
   indeks pertama dan indeks nEff */
{
    return i >= 0 && i < T.nEff;
}

/* ********** TEST KOSONG/PENUH ********** */
/* *** Test list kosong *** */
boolean isEmpty(ListAnomali T)
/* Mengirimkan true jika list T kosong, mengirimkan false jika tidak */
{
    return T.nEff == 0;
}

/* *** Test list penuh *** */
boolean isFull(ListAnomali T)
/* Mengirimkan true jika list T penuh, mengirimkan false jika tidak */
{
    return T.nEff == MAX_CAPACITY;
}

/* ********** Selektor INDEKS ********** */
IdxType getFirstIdx(ListAnomali T)
/* Prekondisi : List T sembarang (bisa kosong atau bisa terisi) */
/* Mengirimkan indeks elemen pertama yaitu IDX_MIN */
/* Jika list kosong, return IDX_UNDEF */
{
    if (T.nEff == 0)
        return IDX_UNDEF;
    return IDX_MIN;
}

IdxType getLastIndex(ListAnomali T)
/* Prekondisi : List T sembarang (bisa kosong atau bisa terisi) */
/* Mengirimkan indeks elemen efektif terakhir */
/* Jika list kosong, return IDX_UNDEF */
{
    if (T.nEff == 0)
        return IDX_UNDEF;
    return T.nEff - 1;
}

/* *** Menghasilkan sebuah elemen *** */
ElType getAnomalyAtIdx(ListAnomali T, IdxType i)
/* Prekondisi : list T sembarang (bisa kosong atau bisa terisi), i mungkin tidak
   valid*/
/* Mengirimkan elemen list yang ke-i */
/* Jika list kosong atau indeks tidak valid, return ELEM_UNDEF */
{
    if (!isIdxEff(T, i))
        return ELEM_UNDEF;
    return T.buffer[i];
}

/* ********** INPUT/OUTPUT ********** */
void printAnomalies(ListAnomali T)
/* Prekondisi: T boleh kosong */
/* Menuliskan isi list dengan traversal */
/* Tampilkan list dalam kurung siku dalam bentuk
   [<Elemen-1>,<Elemen-2>,<Elemen-3>,..<Elemen-nEff>], seperti [1,2,3], dan
   diakhiri newline */
/* Perhatikan bahwa tidak ada spasi dalam output */
/* Jika T kosong : Hanya menulis "LIST KOSONG" dan diakhiri newline */
{
    if (isEmpty(T)) {
        printf("LIST KOSONG\n");
        return;
    }

    printf("[");
    for (IdxType i = 0; i < T.nEff; ++i) {
        if (i + 1 == T.nEff) {
            printf("%d]\n", T.buffer[i]);
        } else {
            printf("%d,", T.buffer[i]);
        }
    }
}

/* ********** Operasi Dasar ********** */
void setAt(ListAnomali *T, ElType v, IdxType i)
/* Prekondisi : list T terisi, indeks i bisa tidak valid */
/* Mengganti elemen T pada indeks i menjadi v */
{
    if (!isIdxEff(*T, i))
        return;
    T->buffer[i] = v;
}

void insertAt(ListAnomali *T, ElType v, IdxType i)
/* Prekondisi : list T sembarang (bisa kosong atau bisa terisi) dan TIDAK PENUH,
   indeks i bisa tidak valid */
/* Menyelipkan elemen v ke T di indeks i */
/* Semua elemen setelah indeks digeser ke kanan */
{
    // only use valid indices + nEff index
    if (i < 0 || i > T->nEff)
        return;

    // do not replace undefined element previously at i

    T->nEff++;
    for (IdxType j = i; j < T->nEff; j++) {
        ElType tmp = T->buffer[j];
        T->buffer[j] = v;
        v = tmp;
    }
}

void deleteAt(ListAnomali *T, IdxType i, ElType *v)
/* Prekondisi : list T sembarang (bisa kosong atau bisa terisi) dan indeks i
 * bisa tidak valid */
/* Menghapus ElType pada indeks i */
/* Semua elemen setelahnya DIGESER ke kiri */
/* Elemen yang dihapus disimpan pada v */
{
    if (!isIdxEff(*T, i))
        return;
    *v = T->buffer[i];

    T->nEff--;
    for (IdxType j = i; j < T->nEff; j++) {
        T->buffer[j] = T->buffer[j + 1];
    }
    T->buffer[T->nEff] = ELEM_UNDEF;
}

/* ********** Anomaly Operations ********** */
ElType highestAnomaly(ListAnomali T)
/* Prekondisi : list T tidak kosong */
/* Mengirimkan nilai anomali tertinggi di list */
{
    ElType max = INT32_MIN;
    for (IdxType i = 0; i < T.nEff; i++) {
        // NOTE: I do not know if ELEM_UNDEF should be ignored here
        if (T.buffer[i] == ELEM_UNDEF)
            continue;

        if (T.buffer[i] > max) {
            max = T.buffer[i];
        }
    }
    return max;
}

ElType lowestAnomaly(ListAnomali T)
/* Prekondisi : list T tidak kosong */
/* Mengirimkan nilai anomali terendah di list */
{
    ElType min = INT32_MAX;
    for (IdxType i = 0; i < T.nEff; i++) {
        // NOTE: I do not know if ELEM_UNDEF should be ignored here
        if (T.buffer[i] == ELEM_UNDEF)
            continue;

        if (T.buffer[i] < min) {
            min = T.buffer[i];
        }
    }
    return min;
}

void shiftRightByK(ListAnomali *T, int K)
/* Prekondisi : list T tidak kosong dan (last_idx + K) < max_anomaly_count */
/* Menggeser seluruh elemen ke kanan sebanyak K kali */
/* Gunakan ELEM_UNDEF sebagai elemen baru di kiri */
/* Contoh, untuk K = 2, maka [1,2,3] menjadi [ELEM_UNDEF,ELEM_UNDEF,1,2,3]*/
{
    // Vro who would want to do this to a list

    T->nEff += K;
    for (IdxType i = T->nEff - 1; i >= K; i--) {
        T->buffer[i] = T->buffer[i - K];
    }
    for (IdxType i = 0; i < K; i++) {
        T->buffer[i] = ELEM_UNDEF;
    }
}

void reverseList(ListAnomali *T)
/* Prekondisi : list T tidak kosong */
/* Membalikkan list T */
/* Contoh, untuk untuk list [1,2,3], maka menjadi [3,2,1] */
{
    for (IdxType i = 0; i < T->nEff / 2; i++) {
        ElType tmp = T->buffer[i];
        T->buffer[i] = T->buffer[T->nEff - 1 - i];
        T->buffer[T->nEff - 1 - i] = tmp;
    }
}

void extractExtremeAnomalies(ListAnomali *T_src, ListAnomali *T_dst)
/* Prekondisi : list T_src dan T_dst sembarang (bisa kosong atau bisa terisi) */
/* MEMINDAHKAN elemen anomali ekstrim dari T_src ke T_dst secara urut dari kiri
 * ke kanan */
/* Anomali ekstrem didefinisikan sebagai anomali dengan nilai <= -100 dan >=
 * 100*/
/* Contoh: */
/* untuk untuk list T_src [0, 100, -200], maka h:*/
/*     T_src akan berisi [0]  */
/*     T_dst akan berisi [100, -200]  */
/* Jika T_dst tidak kosong dan ada elemen yang bisa diekstrak : semua nilai
 * T_dst dihilangkan (List di overwrite) */
/* Jika T_dst tidak kosong dan tidak ada elemen yang bisa diekstrak : jangan
 * ubah T_dst */
{
    ListAnomali tmpdst;
    CreateListAnomali(&tmpdst);

    int found = 0;
    for (IdxType i = 0; i < T_src->nEff; i++) {
        ElType ano = T_src->buffer[i];

        // NOTE: I do not know if ELEM_UNDEF should be ignored here
        if (T_src->buffer[i] == ELEM_UNDEF)
            continue;

        if (ano <= -100 || ano >= 100) {
            found++;
            insertAt(&tmpdst, ano, 0);
            continue;
        }

        T_src->buffer[i - found] = T_src->buffer[i];
    }

    if (found > 0) {
        reverseList(&tmpdst);
        for (int i = 0; i < MAX_CAPACITY; i++) {
            T_dst->buffer[i] = tmpdst.buffer[i];
        }
        T_dst->nEff = tmpdst.nEff;

        for (IdxType i = T_src->nEff - found; i < T_src->nEff; i++) {
            T_src->buffer[i] = ELEM_UNDEF;
        }
        T_src->nEff -= found;
    }
}
