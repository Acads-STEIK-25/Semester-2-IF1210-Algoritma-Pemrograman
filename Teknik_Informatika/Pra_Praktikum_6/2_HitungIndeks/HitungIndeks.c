#include "HitungIndeks.h"
#include <stdio.h>
#include <string.h>

void BuatTranskrip(Transkrip *T)
/* Membuat transkrip kosong
 I.S. T sembarang
 F.S. Terbentuk transkrip T kosong */
{
    T->NEff = 0;
    for (int i = 0; i < MAX_NUM_MATKUL; i++) {
        T->Indeks[i] = 0;
        T->Nilai[i] = 0;
        T->Kehadiran[i] = 0;
        strncpy(T->NamaMatkul[i], "", MAX_NAME_LEN);
        T->SKS[i] = 0;
    }
}

int AmbilJumlahMatkul(Transkrip T)
/* Mengembalikan banyaknya mata kuliah pada transkrip */
{
    return T.NEff;
}

void AmbilMatkul(Transkrip *T, char *nama, float nilai, int sks, int kehadiran)
/* Menambahkan matkul pada transkrip jika masih ada kapasitas mata kuliah pada
   transkrip dan data mata kuliah valid. Nilai dan kehadiran berada pada range
   0-100, sks berada pada range 1-4, dan nama tidak boleh kosong. */
{
    if (T->NEff >= MAX_NUM_MATKUL)
        return;

    if (nilai < 0.0 || nilai > 100.0 || sks < 1 || sks > 4 || kehadiran < 0 ||
        kehadiran > 100 || strlen(nama) >= MAX_NAME_LEN || strlen(nama) == 0)
        return;

    int i = T->NEff;
    T->Nilai[i] = nilai;
    strncpy(T->NamaMatkul[i], nama, MAX_NAME_LEN);
    T->SKS[i] = sks;
    T->Kehadiran[i] = kehadiran;

    T->NEff++;
}

float HitungNilai(Transkrip T, int i)
/* Mengembalikan nilai mata kuliah pada indeks ke-i yang sudah memperhitungkan
 nilai mentah sebesar 95% dan nilai kehadiran sebesar 5%. Jika mata kuliah tidak
 ditemukan pada transkrip, kembalikan -1 */
{
    if (i < 0 || i >= T.NEff)
        return -1.0;
    return T.Nilai[i] * 0.95 + T.Kehadiran[i] * 0.05;
}

char HitungIndeks(Transkrip T, int i)
/* Mengembalikan nilai mata kuliah pada indeks ke-i yang sudah diterjemahkan ke
dalam indeks Dengan ketentuan indeks sebagai berikut: A: 100.0 >= nilai >= 80.0
    B: nilai >= 70.0
    C: nilai >= 60.0
    D: nilai >= 50.0
    E: 0 =< nilai < 50.0
Jika mata kuliah tidak ditemukan pada transkrip atau nilainya tidak valid,
kembalikan '-' */
{
    float n = HitungNilai(T, i);
    if (n < 0.0 || n > 100.0) {
        return '-';
    } else if (n >= 80.0) {
        return 'A';
    } else if (n >= 70.0) {
        return 'B';
    } else if (n >= 60.0) {
        return 'C';
    } else if (n >= 50.0) {
        return 'D';
    } else {
        return 'E';
    }
}

void SimpanIndeks(Transkrip *T)
/* Memasukkan data indeks tiap matkul pada transkrip */
{
    for (int i = 0; i < T->NEff; i++) {
        char idx = HitungIndeks(*T, i);
        T->Indeks[i] = idx;
    }
}

char HitungIndeksTotal(Transkrip T)
/* Mengembalikan indeks keseluruhan mata kuliah berdasarkan transkrip.
   Fungsi ini akan memanggil SimpanIndeks secara internal sebelum menghitung.
    1. Konversi indeks tiap matkul ke poin, jika ada indeks yang tidak valid,
maka poinnya dianggap 0.0 A = 4.0, B = 3.0, C = 2.0, D = 1.0, E = 0.0
    2. Hitung rata-rata:
        (Total (SKS * poin)) / Total SKS
    3. Tentukan indeks total berdasarkan range IP berikut:
        A: 3.5 <= IP <= 4.0
        B: 2.5 <= IP < 3.5
        C: 1.5 <= IP < 2.5
        D: 0.5 <= IP < 1.5
        E: 0.0 <= IP < 0.5
Jika tidak ada mata kuliah pada transkrip atau hasil tidak valid, kembalikan '-'
*/
{
    if (T.NEff == 0)
        return '-';
    SimpanIndeks(&T);

    float totalpoints = 0.0;
    int totalsks = 0;
    for (int i = 0; i < T.NEff; i++) {
        char idx = T.Indeks[i];
        totalsks += T.SKS[i];

        float points = T.SKS[i];

        if (idx == 'A')
            points *= 4.0;
        else if (idx == 'B')
            points *= 3.0;
        else if (idx == 'C')
            points *= 2.0;
        else if (idx == 'D')
            points *= 1.0;
        else
            points *= 0.0;

        totalpoints += points;
    }

    float totalidx = totalpoints / totalsks;
    if (totalidx > 4.0 || totalidx < 0.0)
        return '-';
    else if (totalidx >= 3.5)
        return 'A';
    else if (totalidx >= 2.5)
        return 'B';
    else if (totalidx >= 1.5)
        return 'C';
    else if (totalidx >= 0.5)
        return 'D';
    else
        return 'E';
}

bool CekKelulusan(Transkrip T)
/* Mengembalikan nilai true jika pemilik transkrip ini lulus (indeks total >= C)
 */
{
    char idx = HitungIndeksTotal(T);
    return (idx == 'A') || (idx == 'B') || (idx == 'C');
}

void CetakTranskrip(Transkrip T)
/* Mencetak data transkrip dengan format (akhiri dengan newline):
    Mata Kuliah: <Nama Mata Kuliah ke-1>
    Nilai: <Nilai Mata Kuliah ke-1>
    Indeks: <Indeks Mata Kuliah ke-1>

    Mata Kuliah: <Nama Mata Kuliah ke-2>
    Nilai: <Nilai Mata Kuliah ke-2>
    Indeks: <Indeks Mata Kuliah ke-2>

    ...

    Mata Kuliah: <Nama Mata Kuliah ke-N>
    Nilai: <Nilai Mata Kuliah ke-N>
    Indeks: <Indeks Mata Kuliah ke-N>

    Indeks Akhir: <Indeks Akhir pada Transkrip>
    Status Kelulusan: <"LULUS" / "TIDAK LULUS">
Perhatikan bahwa nilai disini adalah nilai yang MEMPERHITUNGKAN KEHADIRAN dan
ambil dua angka dibelakang koma. Jika transkrip tidak memiliki mata kuliah,
cetak "Transkrip masih kosong" */
{
    if (T.NEff == 0) {
        printf("Transkrip masih kosong\n");
        return;
    }

    SimpanIndeks(&T);
    char finalidx = HitungIndeksTotal(T);
    bool lulus = CekKelulusan(T);
    for (int i = 0; i < T.NEff; i++) {
        printf("Mata Kuliah: %s\n", T.NamaMatkul[i]);
        printf("Nilai: %.2f\n", HitungNilai(T, i));
        printf("Indeks: %c\n", T.Indeks[i]);
        printf("\n");
    }
    printf("Indeks Akhir: %c\n", finalidx);
    printf("Status Kelulusan: ");
    if (lulus) {
        printf("LULUS\n");
    } else {
        printf("TIDAK LULUS\n");
    }
}
