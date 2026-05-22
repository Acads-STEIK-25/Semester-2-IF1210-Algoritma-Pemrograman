#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <float.h>
#define rep(i, n) for(int i = 0; i < n; i++)
#define float double
#define ll long long

#include "cycle.h"
#include "listberkait.h"

Address A[1000002];

boolean HasCycle(List head){
    int idx = 0;
    List temp = head;
    if(temp == NULL) return false;
    while(temp->next != NULL){
        Address nei = temp->next;
        if(nei->info == NULL || nei->info >= idx || A[nei->info] != nei){
            nei->info = idx;
            A[idx] = nei;
            idx++;
            temp = temp->next;
            continue;
        } 
        return true;
    }
    return false;
}