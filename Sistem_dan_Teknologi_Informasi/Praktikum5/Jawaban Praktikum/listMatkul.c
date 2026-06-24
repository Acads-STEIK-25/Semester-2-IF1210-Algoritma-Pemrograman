#include "listMatkul.h"
#include <stdio.h>

void MakeEmpty(ListMatkul* L) {
    (*L).Neff = 0;
}

int NbElmt(ListMatkul L) {
    return L.Neff;
}

int MaxNbEl(ListMatkul L) {
    return MAX_CAPACITY;
}

IdxType GetFirstIdx(ListMatkul L) {
    return 0;
}

IdxType GetLastIdx(ListMatkul L) {
    return L.Neff - 1;
}

ElType GetElmt(ListMatkul L, IdxType i) {
    return L.contents[i];
}

void SetTab(ListMatkul Lin, ListMatkul* Lout) {
    (*Lout).Neff = Lin.Neff;
    for (int i = 0; i < Lin.Neff; i++) {
        (*Lout).contents[i] = Lin.contents[i];
    }
}

void SetEl(ListMatkul* L, IdxType i, ElType v) {
    (*L).contents[i] = v;
    if ((*L).Neff < i + 1) {
        (*L).Neff = i + 1;
    }
}

void SetNeff(ListMatkul* L, IdxType N) {
    (*L).Neff = N;
}

boolean IsIdxValid(ListMatkul L, IdxType i) {
    return i >= GetFirstIdx(L) && i < MAX_CAPACITY;
}

boolean IsIdxEff(ListMatkul L, IdxType i) {
    return i >= GetFirstIdx(L) && i <= GetLastIdx(L);
}

boolean IsEmpty(ListMatkul L) {
    return L.Neff == 0;
}

boolean IsFull(ListMatkul L) {
    return L.Neff == MAX_CAPACITY;
}

void PrintIsi(ListMatkul L) {
    if (IsEmpty(L)) {
        printf("List kosong\n");
        return;
    }
    for (int i = 0; i < L.Neff; i++) {
        printf("%s(%d) - %d: %c\n",
            L.contents[i].kode,
            L.contents[i].sks,
            L.contents[i].semester,
            L.contents[i].nilai);
    }
}

ElType MakeMatkul(char* kode, int sks, int semester, char nilai) {
    ElType mk;
    mk.kode = kode;
    mk.sks = sks;
    mk.semester = semester;
    mk.nilai = nilai;
    return mk;
}

static int nilaiToAngka(char nilai) {
    switch (nilai) {
        case 'A': return 4;
        case 'B': return 3;
        case 'C': return 2;
        case 'D': return 1;
        default:  return 0; /* E */
    }
}

int SumNilai(ListMatkul L, int semester) {
    int sum = 0;
    for (int i = 0; i < L.Neff; i++) {
        if (L.contents[i].semester == semester) {
            sum += nilaiToAngka(L.contents[i].nilai) * L.contents[i].sks;
        }
    }
    return sum;
}

int CountMatkul(ListMatkul L, int semester) {
    int count = 0;
    for (int i = 0; i < L.Neff; i++) {
        if (L.contents[i].semester == semester) count++;
    }
    return count;
}

int CountSKS(ListMatkul L, int semester) {
    int total = 0;
    for (int i = 0; i < L.Neff; i++) {
        if (L.contents[i].semester == semester) {
            total += L.contents[i].sks;
        }
    }
    return total;
}

int CountTotalSKS(ListMatkul L) {
    int total = 0;
    for (int i = 0; i < L.Neff; i++) {
        total += L.contents[i].sks;
    }
    return total;
}

int MaxSemester(ListMatkul L) {
    int max = 0;
    for (int i = 0; i < L.Neff; i++) {
        if (L.contents[i].semester > max) {
            max = L.contents[i].semester;
        }
    }
    return max;
}

float HitungIP(ListMatkul L, int semester) {
    int totalSKS = CountSKS(L, semester);
    if (totalSKS == 0) return 0.0f;
    return (float)SumNilai(L, semester) / totalSKS;
}

float HitungIPK(ListMatkul L) {
    int maxSem = MaxSemester(L);
    float totalIP = 0.0f;
    for (int sem = 1; sem <= maxSem; sem++) {
        totalIP += HitungIP(L, sem);
    }
    return totalIP / maxSem;
}

int CountMatkulLuar(ListMatkul L, char* kodeJur) {
    int count = 0;
    for (int i = 0; i < L.Neff; i++) {
        char* k = L.contents[i].kode;
        
        if (k[0] != kodeJur[0] || k[1] != kodeJur[1]) {
            count++;
        }
    }
    return count;
}

void DisplaySIX(ListMatkul L) {
    int lastSem = MaxSemester(L);
    printf("IPK: %.2f\n", HitungIPK(L));
    printf("IP: %.2f\n", HitungIP(L, lastSem));
    printf("SKS: Sudah Diambil %d SKS\n", CountTotalSKS(L));
    printf("Daftar Kuliah Semester %d:\n", lastSem);
    for (int i = 0; i < L.Neff; i++) {
        if (L.contents[i].semester == lastSem) {
            printf("%s(%d) - %d: %c\n",
                L.contents[i].kode,
                L.contents[i].sks,
                L.contents[i].semester,
                L.contents[i].nilai);
        }
    }
}