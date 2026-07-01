// NIM     : 18225091
// NAMA    : Muhammad Orkhan
// Tanggal : 15 Mei 2026

#include "bintree_traversal.h"
#include <stdlib.h>
#include <stdio.h>

void printPreOrder(BinTree p) {
    if (!isTreeEmpty(p)) {
        printf("%d ", ROOT(p).key);
        printPreOrder(LEFT(p));
        printPreOrder(RIGHT(p));
    }
}

void printInOrder(BinTree p) {
    if (!isTreeEmpty(p)) {
        printInOrder(LEFT(p));
        printf("%d ", ROOT(p).key);
        printInOrder(RIGHT(p));
    }
}

void printPostOrder(BinTree p) {
    if (!isTreeEmpty(p)) {
        printPostOrder(LEFT(p));
        printPostOrder(RIGHT(p));
        printf("%d ", ROOT(p).key);
    }
}

NodeList* newNodeListElement(ElType val) {
    NodeList* newNode = (NodeList*)malloc(sizeof(NodeList));
    if (newNode != NULL) {
        Info(newNode) = val;
        Next(newNode) = NULL;
    }
    return newNode;
}

NodeList* concat(NodeList* l1, NodeList* l2) {
    if (l1 == NULL) {
        return l2;
    }
    
    NodeList* temp = l1;
    while (Next(temp) != NULL) {
        temp = Next(temp);
    }
    Next(temp) = l2;
    
    return l1;
}

NodeList* makeListPreOrder(BinTree p) {
    if (isTreeEmpty(p)) {
        return NULL;
    }
    
    NodeList* root = newNodeListElement(ROOT(p));
    if (root == NULL) {
        return NULL;
    }
    
    NodeList* leftList = makeListPreOrder(LEFT(p));
    NodeList* rightList = makeListPreOrder(RIGHT(p));
    
    root = concat(root, leftList);
    root = concat(root, rightList);
    
    return root;
}

NodeList* makeListInOrder(BinTree p) {
    if (isTreeEmpty(p)) {
        return NULL;
    }
    
    NodeList* leftList = makeListInOrder(LEFT(p));
    NodeList* root = newNodeListElement(ROOT(p));
    
    if (root == NULL) {
        return NULL;
    }
    
    NodeList* rightList = makeListInOrder(RIGHT(p));
    
    leftList = concat(leftList, root);
    leftList = concat(leftList, rightList);
    
    return leftList;
}

NodeList* makeListPostOrder(BinTree p) {
    if (isTreeEmpty(p)) {
        return NULL;
    }
    
    NodeList* leftList = makeListPostOrder(LEFT(p));
    NodeList* rightList = makeListPostOrder(RIGHT(p));
    NodeList* root = newNodeListElement(ROOT(p));
    
    if (root == NULL) {
        return NULL;
    }
    
    leftList = concat(leftList, rightList);
    leftList = concat(leftList, root);
    
    return leftList;
}

void printNodeList(NodeList* l) {
    NodeList* temp = l;
    while (temp != NULL) {
        printf("[%d] -> ", Info(temp).key);
        temp = Next(temp);
    }
    printf("FINISH\n");
}
