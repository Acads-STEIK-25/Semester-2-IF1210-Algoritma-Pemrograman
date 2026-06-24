#include <stddef.h>
#include "graphadjlist.h"
#include "boolean.h"

/****************** KONSTRUKTOR ******************/
void CreateGraph(int x, Graph *g) {
    FIRST(*g) = newGraphNode(x);
}
/* I.S. Sembarang */
/* F.S. Terbentuk graph g dengan satu simpul ber-ID x */
/*      FIRST(*g) menunjuk ke simpul tersebut */

/****************** MANAJEMEN MEMORI LIST SIMPUL ******************/
AdrNode newGraphNode(int x) {
    AdrNode p = (AdrNode) malloc(sizeof(Node));
    if (p == NIL) return NIL;

    ID(p) = x;
    NPRED(p) = 0;
    TRAIL(p) = NIL;
    NEXT(p) = NIL;

    return p;
}
/* Mengembalikan address hasil alokasi simpul x */
/* Jika alokasi berhasil, maka ID(p)=x, NPRED(p)=0, TRAIL(p)=NIL, NEXT(p)=NIL */
/* Jika alokasi gagal, mengembalikan NIL */

void deallocGraphNode(AdrNode p) {
    free(p);
}
/* I.S. p terdefinisi */
/* F.S. p dikembalikan ke sistem */

/****************** MANAJEMEN MEMORI LIST SUCCESSOR ******************/
AdrSuccNode newSuccNode(AdrNode pn) {
    AdrSuccNode q = (AdrSuccNode) malloc(sizeof(SuccNode));
    if (q == NIL) return NIL;

    SUCC(q) = pn;
    NEXT(q)  = NIL;

    return q;
}
/* Mengembalikan address hasil alokasi successor node */
/* Jika alokasi berhasil, maka SUCC(p)=pn dan NEXT(p)=NIL */
/* Jika alokasi gagal, mengembalikan NIL */

void deallocSuccNode(AdrSuccNode p) {
    free(p);
}
/* I.S. p terdefinisi */
/* F.S. p dikembalikan ke sistem */

/****************** OPERASI GRAPH ******************/
AdrNode searchNode(Graph g, int x) {
    AdrNode p = FIRST(g);

    while (p != NIL && ID(p) < x) {
        p = NEXT(p);
    }

    if (p != NIL && ID(p) == x) return p;
    return NIL;
}
/* Mengembalikan address simpul dengan ID x jika ada pada graph g */
/* Mengembalikan NIL jika tidak ditemukan */

AdrSuccNode searchEdge(Graph g, int prec, int succ) {
    AdrNode pPrec = searchNode(g, prec);
    if (pPrec == NIL) return NIL;
 
    AdrNode pSucc = searchNode(g, succ);
    if (pSucc == NIL) return NIL;

    AdrSuccNode q = TRAIL(pPrec);
    while (q != NIL && ID(SUCC(q)) < succ) {
        q = NEXT(q);
    }

    if (q != NIL && ID(SUCC(q)) == succ) return q;
    return NIL;
}
/* Mengembalikan address trailer yang menyimpan busur <prec, succ> */
/* Mengembalikan NIL jika busur tidak ditemukan */

void insertNode(Graph *g, int x, AdrNode *pn) {
    AdrNode prev = NIL;
    AdrNode curr = FIRST(*g);

    while (curr != NIL && ID(curr) < x) {
        prev = curr;
        curr = NEXT(curr);
    }
 
    if (curr != NIL && ID(curr) == x) {
        *pn = curr;
        return;
    }

    AdrNode new = newGraphNode(x);
    if (new == NIL) {
        *pn = NIL;
        return;
    }
 
    NEXT(new) = curr;
 
    if (prev == NIL) {      
        FIRST(*g) = new;
    } else {
        NEXT(prev) = new;
    }
 
    *pn = new;
}
/* I.S. g terdefinisi */
/* F.S. Jika alokasi berhasil, simpul x ditambahkan pada leader list */
/*      secara terurut membesar berdasarkan ID, dan pn berisi address simpul x */
/*      Jika x sudah ada, g tidak berubah dan pn berisi address simpul tersebut */
/*      Jika alokasi gagal, g tetap dan pn berisi NIL */

void insertEdge(Graph *g, int prec, int succ) {
    AdrNode pPrec, pSucc;
    insertNode(g, prec, &pPrec);
    insertNode(g, succ, &pSucc);

    if (pPrec == NIL || pSucc == NIL) return;
 
    AdrSuccNode prevQ = NIL;
    AdrSuccNode currQ = TRAIL(pPrec);

    while (currQ != NIL && ID(SUCC(currQ)) < succ) {
        prevQ = currQ;
        currQ = NEXT(currQ);
    }

    if (currQ != NIL && ID(SUCC(currQ)) == succ) return;
 
    AdrSuccNode qBaru = newSuccNode(pSucc);
    if (qBaru == NIL) return;
 
    NEXT(qBaru) = currQ;
    if (prevQ == NIL) {
        TRAIL(pPrec) = qBaru;
    } else {
        NEXT(prevQ) = qBaru;
    }
 
    NPRED(pSucc)++;
}
/* I.S. g, prec, dan succ terdefinisi */
/* F.S. Jika belum ada busur <prec, succ>, busur tersebut ditambahkan ke g */
/*      Jika simpul prec/succ belum ada, simpul tersebut ditambahkan terlebih dahulu */
/*      Jika busur sudah ada, g tidak berubah */

void deleteNode(Graph *g, int x) {
    AdrNode target = searchNode(*g, x);
    if (target == NIL) return;
 
    AdrNode scan = FIRST(*g);
    while (scan != NIL) {
        if (scan != target) {
            AdrSuccNode prevQ = NIL;
            AdrSuccNode currQ = TRAIL(scan);

            while (currQ != NIL && SUCC(currQ) != target) {
                prevQ = currQ;
                currQ = NEXT(currQ);
            }

            if (currQ != NIL) {
                if (prevQ == NIL) {
                    TRAIL(scan) = NEXT(currQ);
                } else {
                    NEXT(prevQ) = NEXT(currQ);
                }
                NPRED(target)--;
                deallocSuccNode(currQ);
            }
        }
        scan = NEXT(scan);
    }

    AdrSuccNode currQ = TRAIL(target);
    while (currQ != NIL) {
        AdrSuccNode nextQ = NEXT(currQ);
        NPRED(SUCC(currQ))--;
        deallocSuccNode(currQ);
        currQ = nextQ;
    }
 
    if (FIRST(*g) == target) {
        FIRST(*g) = NEXT(target);
    } else {
        AdrNode prev = FIRST(*g);
        while (prev != NIL && NEXT(prev) != target) {
            prev = NEXT(prev);
        }
        
        if (prev != NIL) {
            NEXT(prev) = NEXT(target);
        }
    }
 
    deallocGraphNode(target);
}
/* I.S. g terdefinisi, simpul x ada pada g, dan jumlah simpul pada g lebih dari 1 */
/* F.S. Simpul x dan semua busur yang terhubung dengan x dihapus dari g */