#include <stddef.h>
#include "graph_incidencelist.h"
#include "boolean.h"

/* Membuat graph baru yang menunjuk simpul dengan ID bernilai x */
/* I.S. Sembarang */
/* F.S. Terbentuk graph g dengan satu simpul ber-ID x */
/* FIRST(*g) menunjuk ke simpul tersebut */
void CreateGraph(int x, Graph *g) {
    AdrNode p = newGraphNode(x);
    FIRST(*g) = p;
}

/* Membuat dan mengembalikan alamat simpul utama (node) baru */
/* Jika alokasi gagal, kembalikan NIL */
/* I.S. : x terdefinisi */
/* F.S. : Dialokasikan simpul baru dengan nilai:
    - ID(p) = x,
    - NPRED(p) = 0,
    - TRAIL(p) = NIL,
    - NEXTNODE(p) = NIL
*/
AdrNode newGraphNode(int x) {
    AdrNode p = (AdrNode) malloc(sizeof(Node));
    if (p == NIL) return NIL;

    ID(p) = x; 
    NPRED(p) = 0;
    TRAIL(p) = NIL;
    NEXTNODE(p) = NIL;

    return p;
}

/* Dealokasi simpul utama p (node) */
/* I.S. p terdefinisi */
/* F.S. p dikembalikan ke sistem */
void deallocGraphNode(AdrNode p) {
    free(p);
}

/* Membuat dan mengembalikan alamat edge baru */
/* Jika alokasi gagal, kembalikan NIL */
/* I.S. : idEdge valid */
/* F.S. : Dialokasikan edge baru dengan nilai: 
    - IDEDGE(q) = idEdge,
    - NEXTSUCC(q) = NIL
*/
AdrSuccNode newSuccNode(int idEdge) {
    AdrSuccNode q = (AdrSuccNode) malloc(sizeof(SuccNode));
    if (q == NIL) return NIL;

    IDEDGE(q) = idEdge;
    NEXTSUCC(q) = NIL;

    return q; 
}

/* Dealokasi edge p (SuccNode) */
/* I.S. p terdefinisi */
/* F.S. p dikembalikan ke sistem */
void deallocSuccNode(AdrSuccNode p) {
    free(p);
}

/* Mencari simpul utama (node) dengan ID(p) == x dalam graph */
/* Jika tidak ditemukan alamatnya, kembalikan NIL */
/* I.S. g dan idNode terdefinisi */
/* F.S. Tidak mengubah g */
AdrNode searchNode(Graph g, int idNode) {
    AdrNode p = FIRST(g);

    while (p != NIL && ID(p) != idNode) {
        p = NEXTNODE(p);
    }
    
    return p;
}

/* Mencari apakah simpul dengan idNode memiliki busur dengan idEdge */
/* Jika tidak ditemukan alamatnya, kembalikan NIL */
/* I.S. g, idNode, idEdge terdefinisi */
/* F.S. Tidak mengubah g */
AdrSuccNode searchEdge(Graph g, int idNode, int idEdge) {
    AdrNode p = searchNode(g, idNode);
    if (p == NIL) return NIL;

    AdrSuccNode q = TRAIL(p);
    while (q != NIL && IDEDGE(q) != idEdge) {
        q = NEXTSUCC(q);
    }

    return q; 
}

/* Menambahkan simpul baru ke dalam graph */
/* I.S. g, x terdefinisi, x belum pada graph */
/* F.S. Jika alokasi berhasil, x menjadi simpul terakhir */
/* Jika x sudah ada, g tidak berubah */
/* Jika alokasi gagal, g tetap */
void insertNode(Graph *g, int x) {
    if (searchNode(*g, x) != NIL) return;

    AdrNode new = newGraphNode(x);
    if (new == NIL) return; 

    if (FIRST(*g) == NIL) {
        FIRST(*g) = new;
    } else {
        AdrNode p = FIRST(*g);
        while (NEXTNODE(p) != NIL) {
            p = NEXTNODE(p);
        }
        NEXTNODE(p) = new;
    }
}

/* Menambahkan edge baru ke dalam graph */
/* I.S. g, idNode1, idNode2, dan idEdge terdefinisi. Edge belum ada pada graph */
/* F.S. Menambahkan representasi edge ber-ID idEdge yang menghubungkan idNode1 dan idNode2.
/* Karena undirected, idEdge di-insert ke dalam TRAIL(idNode1) dan TRAIL(idNode2). */
/* Jika alokasi gagal, g tetap */
void insertEdge(Graph *g, int idNode1, int idNode2, int idEdge) {
    AdrNode p1 = searchNode(*g, idNode1);
    AdrNode p2 = searchNode(*g, idNode2);

    if (p1 == NIL || p2 == NIL) return;

    AdrSuccNode q1 = newSuccNode(idEdge);
    AdrSuccNode q2 = newSuccNode(idEdge);

    if (q1 == NIL || q2 == NIL) {
        if (q1 != NIL) deallocSuccNode(q1);
        if (q2 != NIL) deallocSuccNode(q2);
        return;
    }

    if (TRAIL(p1) == NIL) {
        TRAIL(p1) = q1;
    } else {
        AdrSuccNode t = TRAIL(p1);
        while (NEXTSUCC(t) != NIL) {
            t = NEXTSUCC(t);
        }
        NEXTSUCC(t) = q1;
    }
    NPRED(p1)++;

    if (TRAIL(p2) == NIL) {
        TRAIL(p2) = q2;
    } else {
        AdrSuccNode t = TRAIL(p2);
        while (NEXTSUCC(t) != NIL) {
            t = NEXTSUCC(t);
        }
        NEXTSUCC(t) = q2;
    }
    NPRED(p2)++;
}

/* Menghapus simpul dari graph serta seluruh edge terkait */
/* I.S. : g terdefinisi, x boleh ada atau tidak di g */
/* F.S. : Simpul x dan semua edge ke/dari x dihapus dari g. */
/*        Jika simpul yang dihapus adalah satu-satunya simpul di graph, */
/*        maka graph menjadi kosong (FIRST(*g) == NIL). */
/* Proses:
 * - Menghapus semua edge dari simpul selain x yang terhubung ke x.
 * - Menghapus semua edge dari x yang terhubung ke simpul lain.
 * - Menghapus simpul x dari list simpul.
*/
void deleteNode(Graph *g, int x) {
    AdrNode target = searchNode(*g, x);
    if (target == NIL) return;

    AdrSuccNode qEdge = TRAIL(target);
    while (qEdge != NIL) {
        int idEdge = IDEDGE(qEdge);

        AdrNode scan = FIRST(*g);
        while (scan != NIL) {
            if (scan != target) {
                AdrSuccNode prev = NIL;
                AdrSuccNode curr = TRAIL(scan);

                while (curr != NIL && IDEDGE(curr) != idEdge) {
                    prev = curr; 
                    curr = NEXTSUCC(curr);
                }
                
                if (curr != NIL) {
                    if (prev == NIL) {
                        TRAIL(scan) = NEXTSUCC(curr);
                    } else {
                        NEXTSUCC(prev) = NEXTSUCC(curr);
                    }
                    NPRED(scan)--;
                    deallocSuccNode(curr);
                }
            }
            scan = NEXTNODE(scan);
        }
        qEdge = NEXTSUCC(qEdge);
    }

    AdrSuccNode curr = TRAIL(target);
    while (curr != NIL) {
        AdrSuccNode next = NEXTSUCC(curr);
        deallocSuccNode(curr);
        curr = next;
    }

    if (FIRST(*g) == target) {
        FIRST(*g) = NEXTNODE(target);
    } else {
        AdrNode prev = FIRST(*g);
        while (prev != NIL && NEXTNODE(prev) != target) {
            prev = NEXTNODE(prev);
        }

        if (prev != NIL) {
            NEXTNODE(prev) = NEXTNODE(target);
        }
    }

    deallocGraphNode(target);
}