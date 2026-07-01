#include <stdio.h>
#include "worldmap.h"

/* Menambahkan simpul kota ke graph */
/* I.S. g terdefinisi, id boleh ada atau tidak ada di graph */
/* F.S. Jika id belum ada di graph, simpul baru dengan ID tersebut
   ditambahkan sebagai elemen terakhir di list simpul.
   Jika id sudah ada atau alokasi gagal, graph tetap. */
void insertNode(Graph *g, int id){
   AdrNode p = searchNode(*g, id);
   AdrNode current = FIRST(*g);
   if (p == NIL){
      AdrNode newNode = newGraphNode(id);
      if (newNode != NIL){
         if (current == NIL){
            NEXTNODE(newNode) = current;
            current = newNode;
         }
         else {
            while (current != NIL){
               current = NEXTNODE(current);
               if (current == NIL){
                  NEXTNODE(newNode) = current;
                  current = newNode;
               }
            }
         }
      }
   }
}

/* Menambahkan jalan (edge) antar dua kota */
/* I.S. g, idAsal, idTujuan, dan weight terdefinisi. */
/* F.S. Jika idAsal dan idTujuan ada di graph, ditambahkan jalan baru 
   dengan jarak (weight) tertentu. Karena graph tak berarah (undirected), 
   jalan ditambahkan ke adjacency list idAsal dan idTujuan, serta nPred 
   keduanya bertambah 1. */
void insertEdge(Graph *g, int idAsal, int idTujuan, int weight);

/* Menghapus simpul kota dan semua jalan terkait */
/* I.S. g terdefinisi, id boleh ada atau tidak ada di graph */
/* F.S. Jika simpul dengan id tersebut ada, simpul tersebut dihapus.
   Seluruh jalan yang terhubung dengannya juga dihapus dari adjacency list
   kota-kota tetangganya, dan nilai nPred kota tetangga dikurangi 1. */
void deleteNode(Graph *g, int id){
   AdrNode prevNode = NIL;
   AdrNode currNode = FIRST(*g);

   while (currNode != NIL && ID(currNode) != id) {
      prevNode = currNode;
      currNode = NEXTNODE(currNode);
   }

   if (currNode != NIL) {
      AdrNode otherNode = FIRST(*g);
      while (otherNode != NIL) {
         if (otherNode != currNode) {
               AdrSuccNode prevE = NIL;
               AdrSuccNode currE = TRAIL(otherNode);
               
               while (currE != NIL) {
                  if (SUCC(currE) == currNode) {
                     if (prevE == NIL) {
                           TRAIL(otherNode) = NEXTSUCC(currE);
                     } else {
                           NEXTSUCC(prevE) = NEXTSUCC(currE);
                     }
                     AdrSuccNode edgeToDel = currE;
                     currE = NEXTNODE(currE);
                     deallocSuccNode(edgeToDel);
                     
                     break; 
                  } else {
                     prevE = currE;
                     currE = NEXTSUCC(currE);
                  }
               }
         }
         otherNode = NEXTNODE(otherNode);
      }

      AdrSuccNode edgeToDel = TRAIL(currNode);
      while (edgeToDel != NIL) {
         AdrNode targetNode = SUCC(edgeToDel);
         NPRED(targetNode)--; 
         
         AdrSuccNode nextEdge = NEXTNODE(edgeToDel);
         deallocSuccNode(edgeToDel);
         edgeToDel = nextEdge;
      }
      TRAIL(currNode) = NIL;

      if (prevNode == NIL) {
         FIRST(*g) = NEXTNODE(currNode);
      } else {
         NEXTNODE(prevNode) = NEXTNODENODE(currNode);
      }
      
      deallocGraphNode(currNode);
   }
}

/* Mencari kota asal yang memiliki jarak terpendek ke kota tujuan tertentu */
/* I.S. g dan idTujuan terdefinisi */
/* F.S. Mengembalikan alamat simpul kota yang bertetangga langsung dengan 
   idTujuan dan memiliki bobot jalan (weight) paling kecil/pendek.
   Jika idTujuan tidak memiliki tetangga atau graph kosong, kembalikan NIL. */
AdrNode findMinimum(Graph g, int idTujuan){
   AdrNode p = newGraphNode(idTujuan);
   return p;
}

/* Mencari kota pusat (Central City) dengan tetangga terbanyak */
/* I.S. g terdefinisi */
/* F.S. Mengembalikan alamat simpul kota yang memiliki jumlah tetangga 
   (nPred) paling banyak di seluruh graph. Jika ada lebih dari satu yang 
   maksimal, kembalikan yang ditemukan pertama kali. Jika graph kosong, NIL. */
AdrNode findCentralCity(Graph g){
   AdrNode p = FIRST(g);
   return p;
}