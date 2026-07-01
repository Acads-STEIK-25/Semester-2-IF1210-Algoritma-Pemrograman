#include "graph_incidencelist.h"
#include <stdio.h>

/* Menghapus busur secara spesifik dari graph berdasarkan ID busur */
/* I.S. : g terdefinisi, idEdge terdefinisi (boleh ada atau tidak ada di g) */
/* F.S. : Jika idEdge ditemukan, representasi busur tersebut dihapus dari list 
        busur (trail) pada semua simpul yang terhubung.
        NPRED dari simpul-simpul yang bersangkutan dikurangi 1.
        Memori SuccNode yang menyimpan idEdge didealokasi.
        Jika idEdge tidak ditemukan di dalam graph, g tidak berubah. */
void deleteEdge(Graph *g, int idEdge){
    AdrNode p = FIRST(*g);
    while (p != NIL) {
        AdrSuccNode prevE = NIL;
        AdrSuccNode currE = TRAIL(p);
        boolean found = false;

        while (currE != NIL) {
            if (IDEDGE(currE) == idEdge) {
                found = true;
                break;
            }
            prevE = currE;
            currE = NEXTSUCC(currE);
        }

        if (found) {
            if (prevE == NIL) {
                TRAIL(p) = NEXTSUCC(currE);
            } else {
                NEXTSUCC(prevE) = NEXTSUCC(currE);
            }
            deallocSuccNode(currE);
            NPRED(p)--;
        }

        p = NEXTNODE(p);
    }
}

/* Membuat salinan identik  dari graph g1 ke graph g2 */
/* I.S. : g1 terdefinisi (bisa kosong), g2 sembarang */
/* F.S. : g2 dialokasikan di alamat memori yang baru dan berisi salinan 
        identik dari struktur simpul dan busur milik g1.
        Perubahan pada g2 di masa depan tidak akan memengaruhi g1.
        Jika g1 kosong, g2 juga menjadi graph kosong (FIRST(*g2) == NIL). */
void copyGraph(Graph g1, Graph *g2){
    FIRST(*g2) = NIL; 

    if (FIRST(g1) != NIL) {
        AdrNode p1 = FIRST(g1);
        AdrNode *lastNode2 = &FIRST(*g2);

        while (p1 != NIL) {
            AdrNode p2 = newGraphNode(ID(p1)); 
            NPRED(p2) = NPRED(p1);
            TRAIL(p2) = NIL;
            NEXTNODE(p2) = NIL;

            *lastNode2 = p2;
            lastNode2 = &NEXTNODE(p2);

            AdrSuccNode e1 = TRAIL(p1);
            AdrSuccNode *lastEdge2 = &TRAIL(p2);

            while (e1 != NIL) {
                AdrSuccNode e2 = newSuccNode(IDEDGE(e1));
                NEXTSUCC(e2) = NIL;
                
                *lastEdge2 = e2;
                lastEdge2 = &NEXTSUCC(e2);

                e1 = NEXTSUCC(e1);
            }
            p1 = NEXTNODE(p1);
        }
    }
}