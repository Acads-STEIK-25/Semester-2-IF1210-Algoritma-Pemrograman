#ifndef LEVEL_H
#define LEVEL_H

#include "boolean.h"
#include <stdlib.h>

#define MAX_HEIGHT 25
#define EXPAND_LEN 10

typedef struct {
    int height; // Ketinggian dimulai dari 0 - MAX_HEIGHT
    boolean isTrap;
} Block;

typedef struct {
    Block *listOfBlocks;
    int capacity;
    int nEff;
} Level;

void CreateLevel(Level *L, int capacity);
/* I.S. L sembarang, capacity > 0 */
/* F.S. Terbentuk Level L kosong dengan kapasitas capacity */

void DealocateLevel(Level *L);
/* I.S. L terdefinisi */
/* F.S. L.listOfBlocks dikembalikan ke sistem, L.capacity = 0, L.nEff = 0 */

boolean IsEmpty(Level L);
/* Mengirimkan true jika level kosong, false jika tidak */

boolean IsFull(Level L);
/* Mengirimkan true jika level penuh, false jika tidak */

void ExpandLevel(Level *L, int num);
/* Proses: Menambahkan capacity L sebanyak num */
/* I.S. L sudah terdefinisi, num > 0 */
/* F.S. Ukuran capacity bertambah sebanyak num */

void AddBlock(Level *L, int height, boolean isTrap);
/* Proses: Menambahkan block baru di akhir level. Jika list penuh, expand kapasitasnya sebesar EXPAND_LEN sebelum diisi. */
/* I.S. L terdefinisi, height >= 0 */
/* F.S. Block baru ditambahkan sebagai elemen terakhir L */
/* Pastikan block valid. Jika block tidak valid, block tidak ditambahkan */

void RemoveLastBlock(Level *L);
/* Proses: Menghapus block terakhir pada level */
/* I.S. L terdefinisi */
/* F.S. Block di akhir L hilang */

boolean IsJumpValid(Level L, int currentIdx, int targetIdx);
/* Mengirimkan true jika pemain bisa mencapai targetIdx dari currentIdx ke dengan maupun tanpa lompatan
   Syarat lompatan:
   1. targetIdx harus berada di depan currentIdx
   2. Jarak horizontal maksimal 2 (bersebelahan, atau lompat lewati 1 celah)
   3. Jarak vertikal naik: maksimal 1
   4. Jarak vertikal turun: maksimal 3
   5. Tipe block di targetIndex BUKAN Trap.
   Mengirimkan false jika salah satu syarat tidak terpenuhi */

boolean IsLevelBeatable(Level L);
/* Mengembalikan true jika pemain bisa mencapai block terakhir dari block pertama tanpa melanggar aturan lompatan
   Note: Block pertama dipastikan bukan Trap */

void PrintLevel(Level L);
/* I.S. L terdefinisi */
/* F.S. Menampilkan informasi level ke layar

   Contoh Format:
   Height = 1: [B][][][]
   Height = 0: [][B][T][B]

   Penjelasan contoh: 
   B adalah Block, T adalah Trap. 
   [B] mendefinisikan keberadaan Block Normal pada indeks ke-0 listOfBlocks yang memiliki ketinggian = 1 ([B] pertama pada contoh)
   [T] mendefinisikan keberadaan Trap pada indeks ke-2 listOfBlocks yang memiliki ketinggian = 0

   Perhatikan bahwa list ini dua dimensi. Maka, tidak ada kemungkinan posisi yang sama bisa diisi
   dengan dua atau lebih Block pada ketinggian yang berbeda
   SKIP ketinggian yang TIDAK memiliki Block apapun, mulai cetak dari ketinggian terbesar
*/

#endif
