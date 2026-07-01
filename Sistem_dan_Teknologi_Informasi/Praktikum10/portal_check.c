#include <portal_check.h>
#include <graphadjlist.h>
#include <boolean.h>

int outDegree(Graph g, int x){
    AdrNode nodeX = searchNode(g,x);
    if (nodeX == NIL) return 0;
    else{
        int count = 0;
        AdrSuccNode succNodeX = TRAIL(nodeX);
        while (succNodeX != NIL){
            count++;
            succNodeX = NEXT(succNodeX);
        }
        return count;
    }
}
/* Mengembalikan banyaknya busur keluar dari simpul x */
/* Jika simpul x tidak ada pada graph, mengembalikan 0 */

int inDegree(Graph g, int x){
    AdrNode nodeX = searchNode(g,x);
    if (nodeX == NIL) return 0;
    else return NPRED(nodeX);
}
/* Mengembalikan banyaknya busur masuk ke simpul x */
/* Jika simpul x tidak ada pada graph, mengembalikan 0 */

boolean isAdjacent(Graph g, int x, int y){
    AdrNode nodeX = searchNode(g,x);
    if (nodeX == NIL) return false;
    else{
        AdrSuccNode succNodeX = TRAIL(nodeX);
        while (succNodeX != NIL){
            if (ID(SUCC(succNodeX)) == y) return true;
            succNodeX = NEXT(succNodeX);
        }
        return false;
    }
}
/* Mengembalikan true jika terdapat busur dari x menuju y */    

boolean isSource(Graph g, int x){
    AdrNode nodeX = searchNode(g,x);
    if (nodeX == NIL) return false;
    else if (NPRED(nodeX) == 0) return true;
    else return false;
}
/* Mengembalikan true jika simpul x ada pada graph dan tidak memiliki busur masuk */

boolean isSink(Graph g, int x){
    AdrNode nodeX = searchNode(g,x);
    if (nodeX == NIL) return false;
    else{
        AdrSuccNode succNodeX = TRAIL(nodeX);
        if (succNodeX == NIL) return true;
        else return false;
    }
}
/* Mengembalikan true jika simpul x ada pada graph dan tidak memiliki busur keluar */

int countEdges(Graph g){
    int count = 0;
    AdrNode node = FIRST(g);
    while (node != NIL){
        AdrSuccNode succNode = TRAIL(node);
        while (succNode != NIL){
            count++;
            succNode = NEXT(succNode);
        }
        node = NEXT(node);
    }
    return count;
}
/* Mengembalikan banyaknya busur pada graph */