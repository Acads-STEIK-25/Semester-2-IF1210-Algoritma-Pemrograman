#include "Level.h"
#include <stdio.h>

void CreateLevel(Level *L, int capacity)
/* I.S. L sembarang, capacity > 0 */
/* F.S. Terbentuk Level L kosong dengan kapasitas capacity */
{
    L->nEff = 0;
    L->capacity = capacity;
    L->listOfBlocks = malloc(capacity * sizeof(Block));
}

void DealocateLevel(Level *L)
/* I.S. L terdefinisi */
/* F.S. L.listOfBlocks dikembalikan ke sistem, L.capacity = 0, L.nEff = 0 */
{
    L->nEff = 0;
    L->capacity = 0;
    free(L->listOfBlocks);
}

boolean IsEmpty(Level L)
/* Mengirimkan true jika level kosong, false jika tidak */
{
    return L.nEff == 0;
}

boolean IsFull(Level L)
/* Mengirimkan true jika level penuh, false jika tidak */
{
    return L.nEff == L.capacity;
}

void ExpandLevel(Level *L, int num)
/* Proses: Menambahkan capacity L sebanyak num */
/* I.S. L sudah terdefinisi, num > 0 */
/* F.S. Ukuran capacity bertambah sebanyak num */
{
    L->capacity += num;
    Block *newptr = malloc(L->capacity * sizeof(Block));

    for (int i = 0; i < L->nEff; i++) {
        newptr[i] = L->listOfBlocks[i];
    }
    free(L->listOfBlocks);
    L->listOfBlocks = newptr;
}

void AddBlock(Level *L, int height, boolean isTrap)
/* Proses: Menambahkan block baru di akhir level. Jika list penuh, expand
   kapasitasnya sebesar EXPAND_LEN sebelum diisi. */
/* I.S. L terdefinisi, height >= 0 */
/* F.S. Block baru ditambahkan sebagai elemen terakhir L */
/* Pastikan block valid. Jika block tidak valid, block tidak ditambahkan */
{
    // NOTE: height >= MAX_HEIGHT fails on test 15
    // TEST: (L->nEff == 0 && isTrap) deleted
    if (height > MAX_HEIGHT || height < 0)
        return;

    if (IsFull(*L)) {
        ExpandLevel(L, EXPAND_LEN);
    }

    Block n = {height, isTrap};
    L->listOfBlocks[L->nEff] = n;
    L->nEff++;
}

void RemoveLastBlock(Level *L)
/* Proses: Menghapus block terakhir pada level */
/* I.S. L terdefinisi */
/* F.S. Block di akhir L hilang */
{
    if (L->nEff == 0)
        return;
    L->nEff--;
}

boolean IsJumpValid(Level L, int currentIdx, int targetIdx)
/* Mengirimkan true jika pemain bisa mencapai targetIdx dari currentIdx ke
   dengan maupun tanpa lompatan Syarat lompatan:
   1. targetIdx harus berada di depan currentIdx
   2. Jarak horizontal maksimal 2 (bersebelahan, atau lompat lewati 1 celah)
   3. Jarak vertikal naik: maksimal 1
   4. Jarak vertikal turun: maksimal 3
   5. Tipe block di targetIndex BUKAN Trap.
   Mengirimkan false jika salah satu syarat tidak terpenuhi */
{
    if (currentIdx < 0 || currentIdx >= L.nEff || targetIdx < 0 ||
        targetIdx >= L.nEff)
        return false;
    Block c = L.listOfBlocks[currentIdx];
    Block t = L.listOfBlocks[targetIdx];
    // NOTE: targetIdx >= currentIdx fails
    return (targetIdx > currentIdx) && (targetIdx - currentIdx <= 2) &&
           (t.height - c.height <= 1) && (c.height - t.height <= 3) &&
           (!t.isTrap);
}

// NOTE: already correct
boolean IsLevelBeatable(Level L)
/* Mengembalikan true jika pemain bisa mencapai block terakhir dari block
   pertama tanpa melanggar aturan lompatan Note: Block pertama dipastikan bukan
   Trap */
{
    if (L.nEff == 0)
        return false;

    if (L.nEff == 1)
        return !L.listOfBlocks[0].isTrap;

    if (L.nEff == 2)
        return !L.listOfBlocks[0].isTrap && IsJumpValid(L, 0, 1);

    boolean p1 = true;
    boolean p2 = false;
    boolean p3 = false;

    for (int i = 0; i + 2 < L.nEff; i++) {
        if (p1) {
            if (IsJumpValid(L, i, i + 1))
                p2 = true;
            if (IsJumpValid(L, i, i + 2))
                p3 = true;
        }

        p1 = p2;
        p2 = p3;
        p3 = false;
    }
    // p2 and p1 will represent the 2nd to final block's state

    return p2 || (p1 && IsJumpValid(L, L.nEff - 2, L.nEff - 1));
}

void PrintLevel(Level L)
/* I.S. L terdefinisi */
/* F.S. Menampilkan informasi level ke layar

   Contoh Format:
   Height = 1: [B][][][]
   Height = 0: [][B][T][B]

   Penjelasan contoh:
   B adalah Block, T adalah Trap.
   [B] mendefinisikan keberadaan Block Normal pada indeks ke-0 listOfBlocks yang
   memiliki ketinggian = 1 ([B] pertama pada contoh) [T] mendefinisikan
   keberadaan Trap pada indeks ke-2 listOfBlocks yang memiliki ketinggian = 0

   Perhatikan bahwa list ini dua dimensi. Maka, tidak ada kemungkinan posisi
   yang sama bisa diisi dengan dua atau lebih Block pada ketinggian yang berbeda
   SKIP ketinggian yang TIDAK memiliki Block apapun, mulai cetak dari ketinggian
   terbesar
*/
{
    if (L.nEff == 0)
        return;

    int maxh = -1;
    int minh = MAX_HEIGHT;
    for (int i = 0; i < L.nEff; i++) {
        Block b = L.listOfBlocks[i];
        if (b.height > maxh) {
            maxh = b.height;
        }
        if (b.height < minh) {
            minh = b.height;
        }
    }

    for (int h = maxh; h >= minh; h--) {
        boolean hasblock = false;
        for (int i = 0; i < L.nEff; i++) {
            if (L.listOfBlocks[i].height == h) {
                hasblock = true;
                break;
            }
        }
        if (!hasblock)
            continue;

        printf("Height = %d: ", h);
        for (int i = 0; i < L.nEff; i++) {
            printf("[");
            Block b = L.listOfBlocks[i];
            if (b.height == h) {
                if (b.isTrap) {
                    printf("T");
                } else {
                    // NOTE: 'A' on the olympia problem is false,
                    // it's a score regression
                    printf("B");
                }
            }
            printf("]");
        }
        printf("\n");
    }
}
