#ifndef INVERSE_BST_H
#define INVERSE_BST_H

#include "bst.h"

/****************** FUNGSI INVERSE TREE ******************/
/* Mengubah struktur pohon sehingga inorder traversal menghasilkan urutan terbalik */
void inverseTree(BinTree *p);
/* I.S. p terdefinisi (bisa kosong atau tidak)
   F.S. Pohon di-inverse: setiap subtree kiri dan kanan ditukar
        Sehingga inorder traversal akan menghasilkan urutan dari besar ke kecil */

#endif