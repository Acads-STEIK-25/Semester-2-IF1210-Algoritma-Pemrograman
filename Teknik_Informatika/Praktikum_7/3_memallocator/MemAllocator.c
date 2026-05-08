#include "MemAllocator.h"
#include <stdlib.h>

// // Definisi elemen blok memori kosong
// typedef struct {
//     int address; // Alamat memori kosong
//     int size;    // Ukuran blok memori yang tersedia
// } MemBlock;
//
// // ListMem menyimpan blok-blok memori kosong
// typedef struct {
//     MemBlock *buffer;
//     int capacity;
//     int nEff;
// } ListMem;

// something
void CreateListMem(ListMem *l, int capacity)
/* I.S. l sembarang, capacity > 0 */
/* F.S. Terbentuk list l kosong dengan kapasitas capacity */
{
	l->nEff = 0;
	l->capacity = capacity;
	l->buffer = malloc(capacity * sizeof(MemBlock));
}

void DealokasiListMem(ListMem *l)
/* I.S. l terdefinisi */
/* F.S. List l dikembalikan ke sistem, l.capacity=0, l.nEff=0 */
{
	l->nEff = 0;
	l->capacity = 0;
	free(l->buffer);
}

void ShrinkToFit(ListMem *l)
/* Mengecilkan kapasitas list agar sama dengan nEff */
{
	l->capacity = l->nEff;
	MemBlock *newptr = malloc(l->capacity * sizeof(MemBlock));

	for (int i = 0; i < l->nEff; i++) {
		newptr[i] = l->buffer[i];
	}

	free(l->buffer);
	l->buffer = newptr;
}

/**** Operasi Alokasi Memori ****/

void FreeMemory(ListMem *l, int address, int size)
/* I.S. l terdefinisi, address dan size valid */
/* Menambahkan informasi blok memori kosong baru ke kanan list l.
   Otomatis meningkatkan kapasitas dua kali lipat jika penuh sebelum insert. */
{
	if (l->nEff == l->capacity) {
		l->capacity *= 2;
		MemBlock * newptr = malloc(l->capacity * sizeof(MemBlock));
		for (int i = 0; i < l->nEff; i++) {
			newptr[i] = l->buffer[i];
		}
		free(l->buffer);
		l->buffer = newptr;
	}

	MemBlock b = {address, size};
	l->buffer[l->nEff] = b;
	l->nEff++;
}

int AllocateMemory(ListMem *l, int reqSize)
/* I.S. l terdefinisi */
/* Mencoba mengalokasikan memori sebesar reqSize di satu blok memori.
   Pencarian blok memori dilakukan secara linier dari kiri list */
/* Jika blok dengan ukuran mencukupi ditemukan,
   alokasikan memori sebesar reqSize di blok tersebut,
   dan naikkan address di blok sebesar reqSize */
/* Jika ukuran blok habis (0) setelah dialokasikan,
   maka hapus blok dari list, dan geser semua blok di kanannya ke kiri list */
/* Kembalikan address memori yang didapat, atau ADDR_UNDEF jika alokasi gagal atau reqSize <= 0 */
{
	if (reqSize <= 0) return ADDR_UNDEF;

	for (int i = 0; i < l->nEff; i++) {
		MemBlock *b = &l->buffer[i];
		if (b->size < reqSize) continue;

		int addr = b->address;
		if (b->size > reqSize) {
			b->address += reqSize;
			b->size -= reqSize;
		} else {
			for (int j = i + 1; j < l->nEff; j++) {
				l->buffer[j - 1] = l->buffer[j];
			}
			l->nEff--;
		}
		return addr;
	}
	return ADDR_UNDEF;
}

void Defragment(ListMem *l)
/* I.S. l terdefinisi, blok memori didalamnya belum tentu urut berdasarkan address */
/* Menyatukan pecahan/fragmen informasi blok memori di address yang tersebar */
/* Proses defragmentasi:
    - Untuk setiap blok memori:
        - Jika blok memori persis bersebelahan dengan blok setelahnya,
          maka gabungkan kedua blok menjadi satu blok memori di list l.
    - Kompres list agar kapasitasnya sama dengan nEff.

   ILUSTRASI:
   Address: 1 2 3 4 5 6 7 8 9
   Blok:    x x x y y y - - -
   Karena blok x & y bersebelahan, maka disatukan menjadi:

   Address: 1 2 3 4 5 6 7 8 9
   Blok:    x x x x x x - - -

   Boleh membuat fungsi tambahan untuk membantu.
*/
{
	// Sort 
    if (l->nEff <= 1)
        return;

    for (int i = 0; i < l->nEff; i++) {
        for (int j = 0; j + i + 1 < l->nEff; j++) {
            if (l->buffer[j].address > l->buffer[j + 1].address) {
                MemBlock tmp = l->buffer[j];
                l->buffer[j] = l->buffer[j + 1];
                l->buffer[j + 1] = tmp;
            }
        }
    }

	// Merge 
	int prev = 0;
	for (int i = 1; i < l->nEff; i++) {
		MemBlock *pblock = &l->buffer[prev];
		MemBlock *cblock = &l->buffer[i];
		if (pblock->address + pblock->size == cblock->address) {
			// Merge
			pblock->size += cblock->size;
		} else {
			// Overwrite
			prev++;
			l->buffer[prev] = l->buffer[i];
		}
	}
	l->nEff = prev + 1;

	ShrinkToFit(l);
}
