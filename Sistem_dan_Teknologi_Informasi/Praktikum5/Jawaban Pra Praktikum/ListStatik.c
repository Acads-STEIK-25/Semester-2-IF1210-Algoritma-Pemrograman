#include <stdio.h>
#include "ListStatik.h"
#include "boolean.h"

/* ********** KONSTRUKTOR ********** */
/* Konstruktor : create tabel kosong */

/* I.S. T sembarang */
/* F.S. Terbentuk tabel T kosong dengan kapasitas MaxCapacity */
void MakeEmptyList (TabInt *T) {
    T->Neff = 0;
}

/* ********** SELEKTOR ********** */
/* *** Banyaknya elemen *** */

/* Mengirimkan banyaknya elemen efektif tabel */
/* Mengirimkan nol jika tabel kosong */
int Length (TabInt T) {
    return T.Neff;
}

/* *** Daya tampung container *** */

/* Mengirimkan maksimum elemen yang dapat ditampung oleh tabel */
int MaxNbEl (TabInt T) {
    return MaxCapacity;
}

/* *** Selektor INDEKS *** */

/* Prekondisi : Tabel T sembarang (bisa kosong atau bisa terisi) */
/* Mengirimkan indeks elemen pertama */
/* Jika list kosong, return -1 */
IdxType GetFirstIdx (TabInt T) {
    if (T.Neff == 0) return -1;
    return IdxMin;
}

/* Prekondisi : Tabel T sembarang (bisa kosong atau bisa terisi) */
/* Mengirimkan indeks elemen terakhir */
/* Jika list kosong, return -1 */
IdxType GetLastIdx (TabInt T) {
    if (T.Neff == 0) return -1;
    return T.Neff;
}

/* *** Menghasilkan sebuah elemen *** */

/* Prekondisi : Tabel T sembarang (bisa kosong atau bisa terisi), i antara FirstIdx(T)..LastIdx(T) */
/* Mengirimkan elemen tabel yang ke-i */
/* Jika list kosong, return ElUndef */
ElType GetElmtAt (TabInt T, IdxType i) {
    if (T.Neff == 0) return ElUndef;
    return T.TI[i];
}

/* *** Selektor SET : Mengubah nilai TABEL dan elemen tabel *** */
/* Untuk type private/limited private pada bahasa tertentu */

/* I.S. Tin terdefinisi, sembarang */
/* F.S. Tout berisi salinan Tin */
/* Assignment THsl -> Tin */
void SetTab (TabInt Tin, TabInt *Tout) { 
    Tout->Neff = Tin.Neff;
    for (int i = 1; i <= Tin.Neff; i++) {
        Tout->TI[i] = Tin.TI[i];
    }
}

/* Prekondisi : Tabel T sembarang (bisa kosong atau bisa terisi) */
/* F.S. Elemen T yang ke-i bernilai v */
/* Mengeset nilai elemen tabel yang ke-i sehingga bernilai v */
void SetEl (TabInt *T, IdxType i, ElType v) {
    T->TI[i] = v;
}

/* Prekondisi : Tabel T sembarang (bisa kosong atau bisa terisi) */
/* F.S. Nilai indeks efektif T bernilai N */
/* Mengeset nilai indeks elemen efektif sehingga bernilai N */
void SetNeff (TabInt *T, IdxType N) {
    T->Neff = N; 
}

/* ********** Test Indeks yang valid ********** */

/* Prekondisi : Tabel T sembarang (bisa kosong atau bisa terisi), i sembarang */
/* Mengirimkan true jika i adalah indeks yang valid untuk ukuran tabel yaitu antara indeks yang terdefinisi utk container*/
boolean IsIdxValid (TabInt T, IdxType i) {
    return (i >= IdxMin && i <= MaxCapacity);
}

/* Prekondisi : Tabel T sembarang (bisa kosong atau bisa terisi), i sembarang*/
/* Mengirimkan true jika i adalah indeks yang terdefinisi utk tabel yaitu antara indeks pertama dan indeks Neff */
boolean IsIdxEff (TabInt T, IdxType i) {
    return (i >= IdxMin && i <= T.Neff);
}

/* ********** TEST KOSONG/PENUH ********** */

/* *** Test tabel kosong *** */
/* Mengirimkan true jika tabel T kosong, mengirimkan false jika tidak */
boolean IsEmpty (TabInt T) {
    return (T.Neff == 0);
}

/* *** Test tabel penuh *** */
/* Mengirimkan true jika tabel T penuh, mengirimkan false jika tidak */
boolean IsFull (TabInt T) {
    return (T.Neff == MaxCapacity);
}

/* ********** BACA dan TULIS dengan INPUT/OUTPUT device ********** */

/* Proses : Menuliskan isi tabel dengan traversal */
/* I.S. T boleh kosong */
/* F.S. Jika T tidak kosong : elemen tabel ditulis berderet ke kanan */
/* Tampilkan tabel dalam bentuk [<Elemen-1>,<Elemen-2>,<Elemen-3>,..<Elemen-Neff>], seperti [1,2,3], dan diakhiri newline */
/* Jika T kosong : Hanya menulis "Tabel kosong" dan diakhiri newline */
void ShowAll (TabInt T) {
    if (IsEmpty(T)) printf("Tabel kosong\n");
    else {
        printf("[");
        for (int i = 1; i <= T.Neff; i++) {
            printf("%d", T.TI[i]);
            if (i != T.Neff) {
                printf(",");
            }
        }
        printf("]\n");
    }
}

/* ********** OPERATOR ARITMATIKA ********** */
/* *** Aritmatika tabel : Penjumlahan dan pengurangan */

/* Prekondisi : T1 dan T2 berukuran sama dan tidak kosong */
/* Mengirimkan T1 + T2 */
TabInt PlusTab (TabInt T1, TabInt T2) {
    TabInt TabResult;
    TabResult.Neff = T1.Neff;

    for (int i = 1; i <= T1.Neff; i++) {
        TabResult.TI[i] = T1.TI[i] + T2.TI[i];
    }

    return TabResult;
}

/* Prekondisi : T1 dan T2 berukuran sama dan tidak kosong */
/* Mengirimkan T1 - T2 */
TabInt MinusTab (TabInt T1, TabInt T2) {
    TabInt TabResult;
    TabResult.Neff = T1.Neff;

    for (int i = 1; i <= T1.Neff; i++) {
        TabResult.TI[i] = T1.TI[i] - T2.TI[i];
    }

    return TabResult;
}


/* ********** NILAI EKSTREM ********** */

/* Prekondisi : Tabel T tidak kosong */
/* Mengirimkan nilai maksimum tabel */
ElType ValMax (TabInt T) {
    ElType max = T.TI[1];

    for (int i = 2; i <= T.Neff; i++) {
        if (T.TI[i] > max) {
            max = T.TI[i];
        }
    }
    
    return max;
}

/* Prekondisi : Tabel T tidak kosong */
/* Mengirimkan nilai minimum tabel */
ElType ValMin (TabInt T) {
    ElType min = T.TI[1];

    for (int i = 2; i <= T.Neff; i++) {
        if (T.TI[i] < min) {
            min = T.TI[i];
        }
    }

    return min;
}


/* *** Mengirimkan indeks elemen bernilai ekstrem *** */
/* Prekondisi : Tabel T tidak kosong */
/* Mengirimkan indeks i dengan elemen ke-i adalah nilai maksimum pada tabel */
IdxType IdxMaxTab (TabInt T) {
    IdxType idx = 1; 

    for (int i = 2; i <= T.Neff; i++) {
        if (T.TI[i] > T.TI[idx]) {
            idx = i;
        }
    }

    return idx;
}

/* Prekondisi : Tabel tidak kosong */
/* Mengirimkan indeks i dengan elemen ke-i adalah nilai minimum pada tabel */
IdxType IdxMinTab (TabInt T) {
    IdxType idx = 1; 

    for (int i = 2; i <= T.Neff; i++) {
        if (T.TI[i] < T.TI[idx]) {
            idx = i;
        }
    }
    
    return idx;
}

/* ********** PENGGABUNGAN TABEL ********** */

/* Prekondisi : Tabel T1 dan T2 sembarang (bisa kosong atau bisa terisi) */
/* Mengirimkan hasil penggabungan dua buah tabel, T2 ditaruh di belakang T1 */
TabInt ConcatTable (TabInt T1, TabInt T2) {
    TabInt TabConcat; 
    TabConcat.Neff = T1.Neff + T2.Neff;

    for (int i = 1; i <= T1.Neff; i++) {
        TabConcat.TI[i] = T1.TI[i];
    }

    for (int i = 1; i <= T2.Neff; i++) {
        TabConcat.TI[T1.Neff + i] = T2.TI[i];
    }

    return TabConcat;
}