#include "Album.h"
#include <stdio.h>
#include <stdlib.h>

// typedef int ElType;
//
// typedef struct {
//     ElType *buffer;
//     int nEff;
//     int capacity;
// } Album;

// something
void CreateAlbum(Album *A, int capacity)
/* I.S. A sembarang, capacity > 0 */
/* F.S. Album A terbentuk */
{
	A->capacity = capacity;
	A->nEff = 0;
	A->buffer = malloc(capacity * sizeof(ElType));
}

void DeallocateAlbum(Album *A)
/* I.S. A terdefinisi */
/* F.S. Memori dibebaskan */
{
	free(A->buffer);
	A->capacity = 0;
	A->nEff = 0;
}

boolean IsEmpty(Album A)
/* Mengembalikan true jika nEff == 0 */
{
	return A.nEff == 0;
}

boolean IsFull(Album A)
/* Mengembalikan true jika nEff == capacity */
{
	return A.nEff == A.capacity;
}

void ExpandAlbum(Album *A, int num)
/* I.S. A terdefinisi, num > 0 */
/* F.S. Kapasitas bertambah sebanyak num. */
{
	A->capacity += num;

	ElType* newp = malloc(A->capacity * sizeof(ElType));

	for (int i = 0; i < A->nEff; i++) {
		newp[i] = A->buffer[i];
	}
	free(A->buffer);
	A->buffer = newp;
}

void SplitAndSwap(Album *A, int pivot)
/* Memotong album di indeks pivot, lalu menukar blok kiri dan kanan.
   Contoh: [1,2,3,4,5], pivot 1 (nilai 2) -> Potongan [1,2] dan [3,4,5]
   Hasil: [3,4,5,1,2]
   I.S. A terdefinisi, 0 <= pivot < nEff-1 */
{
	if (A->nEff == 0) return;

	Album p;
	CreateAlbum(&p, A->capacity);
	for (int i = pivot + 1; i < A->nEff; i++) {
		p.buffer[i - (pivot + 1)] = A->buffer[i];
	}
	for (int i = 0; i <= pivot; i++) {
		p.buffer[i + (A->nEff - pivot - 1)] = A->buffer[i];
	}

	for (int i = 0; i < A->nEff; i++) {
		A->buffer[i] = p.buffer[i];
	}
}

void InjectList(Album *A1, Album A2, int idx)
/* Menyisipkan seluruh isi Album A2 ke dalam Album A1 mulai posisi idx
   Kapasitas A1 harus otomatis bertambah jika tidak muat
   I.S. A1, A2 terdefinisi, 0 <= idx <= A1.nEff */
{
	if (A2.nEff == 0) return;

	int totallen = A1->nEff + A2.nEff;
	if (A1->capacity < totallen) {
		ExpandAlbum(A1, totallen - A1->capacity);
	}

	Album aux;
	CreateAlbum(&aux, A1->capacity);

	for (int i = 0; i < idx; i++) {
		aux.buffer[i] = A1->buffer[i];
	}
	for (int i = 0; i < A2.nEff; i++) {
		aux.buffer[idx + i] = A2.buffer[i];
	}
	for (int i = 0; i < A1->nEff - idx; i++) {
		aux.buffer[idx + A2.nEff + i] = A1->buffer[i + idx];
	}

	for (int i = 0; i < totallen; i++) {
		A1->buffer[i] = aux.buffer[i];
	}
	A1->nEff = totallen;
}

void PrintAlbum(Album A)
/* I.S. A terdefinisi */
/* F.S. Cetak isi buffer album ke layar (akhiri \n) */
/* Contoh: [1,2,3]
Maka outputnya adalah -> 123 */
{
	for (int i = 0; i < A.nEff; i++) {
		printf("%d", A.buffer[i]);
	}
	printf("\n");
}

