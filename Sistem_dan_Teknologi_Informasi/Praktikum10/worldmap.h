/* ADT Graph dengan representasi Adjacency List */
/* Graph ini mempunyai weight (jarak) pada busur dan bersifat tidak berarah (undirected) */
#ifndef WORLDMAP_H
#define WORLDMAP_H

#include <stddef.h>
#include "boolean.h"

#define NIL NULL

typedef struct Node *AdrNode;
typedef struct SuccNode *AdrSuccNode;

/* Node merepresentasikan kota (Simpul) */
typedef struct Node {
    int id;                // ID Kota
    int nPred;             // Banyaknya busur/tetangga (Derajat kota)
    AdrSuccNode trail;     // List tetangga (Adjacency List)
    AdrNode next;          // Pointer ke simpul berikutnya
} Node;

/* SuccNode merepresentasikan jalan (edge) menuju kota tujuan */
typedef struct SuccNode {
    AdrNode dest;          // Pointer ke simpul tujuan
    int weight;            // Jarak/bobot
    AdrSuccNode next;      // Pointer ke jalan berikutnya
} SuccNode;

/* Graph menyimpan pointer ke simpul pertama */
typedef struct {
    AdrNode first;
} Graph;

/* Makro Akses */
#define FIRST(g)       ((g).first)
#define ID(p)          (p)->id
#define NPRED(p)       (p)->nPred
#define TRAIL(p)       (p)->trail
#define NEXTNODE(p)    (p)->next
#define DEST(q)        (q)->dest
#define WEIGHT(q)      (q)->weight
#define NEXTSUCC(q)    (q)->next

/* Membuat graph kosong */
/* I.S. Sembarang */
/* F.S. Terbentuk graph g kosong (FIRST(*g) = NIL) */
void CreateGraph(Graph *g);

/* Mengalokasikan memori untuk simpul kota baru */
/* Jika alokasi berhasil, mengembalikan alamat simpul dengan
   ID = id, nPred = 0, trail = NIL, dan next = NIL.
   Jika gagal, mengembalikan NIL. */
AdrNode newGraphNode(int id);

/* Mengembalikan memori simpul ke sistem */
/* I.S. p terdefinisi */
/* F.S. Memori yang ditunjuk oleh p didealokasi */
void deallocGraphNode(AdrNode p);

/* Mengalokasikan memori untuk jalan (edge) baru */
/* Jika alokasi berhasil, mengembalikan alamat edge dengan
   dest = dest, weight = weight, dan next = NIL.
   Jika gagal, mengembalikan NIL. */
AdrSuccNode newSuccNode(AdrNode dest, int weight);

/* Mengembalikan memori edge ke sistem */
/* I.S. p terdefinisi */
/* F.S. Memori yang ditunjuk oleh p didealokasi */
void deallocSuccNode(AdrSuccNode p);

/* Mencari simpul kota berdasarkan ID */
/* I.S. g dan id terdefinisi */
/* F.S. Mengembalikan alamat simpul jika kota dengan ID tersebut ada di graph.
   Jika tidak ditemukan, mengembalikan NIL. */
AdrNode searchNode(Graph g, int id);

/* Mencari apakah ada jalan langsung dari idAsal ke idTujuan */
/* I.S. g, idAsal, dan idTujuan terdefinisi */
/* F.S. Mengembalikan alamat SuccNode (jalan) jika terhubung secara langsung.
   Jika tidak ada jalan yang menghubungkan keduanya, mengembalikan NIL. */
AdrSuccNode searchEdge(Graph g, int idAsal, int idTujuan);

#endif