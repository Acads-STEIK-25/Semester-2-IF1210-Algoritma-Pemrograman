#include <stdio.h>
#include <stdlib.h>
#include "worldmap.h"

void CreateGraph(Graph *g) {
    FIRST(*g) = NIL;
}

AdrNode newGraphNode(int id) {
    AdrNode P = (AdrNode) malloc(sizeof(Node));
    if (P != NIL) {
        ID(P) = id;
        NPRED(P) = 0;
        TRAIL(P) = NIL;
        NEXTNODE(P) = NIL;
    }
    return P;
}

void deallocGraphNode(AdrNode p) {
    free(p);
}

AdrSuccNode newSuccNode(AdrNode dest, int weight) {
    AdrSuccNode P = (AdrSuccNode) malloc(sizeof(SuccNode));
    if (P != NIL) {
        DEST(P) = dest;
        WEIGHT(P) = weight;
        NEXTSUCC(P) = NIL;
    }
    return P;
}

void deallocSuccNode(AdrSuccNode p) {
    free(p);
}

AdrNode searchNode(Graph g, int id) {
    AdrNode P = FIRST(g);
    while (P != NIL) {
        if (ID(P) == id) return P;
        P = NEXTNODE(P);
    }
    return NIL;
}

AdrSuccNode searchEdge(Graph g, int idAsal, int idTujuan) {
    AdrNode P = searchNode(g, idAsal);
    if (P != NIL) {
        AdrSuccNode S = TRAIL(P);
        while (S != NIL) {
            if (ID(DEST(S)) == idTujuan) return S;
            S = NEXTSUCC(S);
        }
    }
    return NIL;
}