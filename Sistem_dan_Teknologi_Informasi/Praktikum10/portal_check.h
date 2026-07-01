/* File: portal_check.h */
/* Modul analisis dasar Graph Berarah dengan adjacency list */

#ifndef PORTAL_CHECK_H
#define PORTAL_CHECK_H

#include "boolean.h"
#include "graphadjlist.h"

int outDegree(Graph g, int x);
/* Mengembalikan banyaknya busur keluar dari simpul x */
/* Jika simpul x tidak ada pada graph, mengembalikan 0 */

int inDegree(Graph g, int x);
/* Mengembalikan banyaknya busur masuk ke simpul x */
/* Jika simpul x tidak ada pada graph, mengembalikan 0 */

boolean isAdjacent(Graph g, int x, int y);
/* Mengembalikan true jika terdapat busur dari x menuju y */

boolean isSource(Graph g, int x);
/* Mengembalikan true jika simpul x ada pada graph dan tidak memiliki busur masuk */

boolean isSink(Graph g, int x);
/* Mengembalikan true jika simpul x ada pada graph dan tidak memiliki busur keluar */

int countEdges(Graph g);
/* Mengembalikan banyaknya busur pada graph */

#endif