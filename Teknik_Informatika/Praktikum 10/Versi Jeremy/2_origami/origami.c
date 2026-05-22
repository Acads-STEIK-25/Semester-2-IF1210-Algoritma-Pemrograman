#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <float.h>
#include <stdbool.h>
#define rep(i, n) for(int i = 0; i < n; i++)
#define float double
#define ll long long

#include "listberkaitganda.h"

int max(int a, int b){
    if(a > b) return a;
    return b;
}

int min(int a, int b){
    if(a < b) return a;
    return b;
}

int A[2000003];
const int OFFSET = 1000000;

int main(){

    int n; scanf("%d", &n);
    if(n == 0){
        printf("[]\n");
        return 0;
    }
    List l;
    CreateList(&l);
    int idx0 = OFFSET, idx1 = 0;
    rep(i, n){
        int x; scanf("%d", &x);
        A[i+OFFSET] = x;
        idx1 = max(idx1, i+OFFSET);
    }
    int pivot; scanf("%d", &pivot);
    bool ok = false;
    int cnt = 0;
    rep(i, n){
        if(!ok && A[i+OFFSET] == pivot){
            ok = true;
            idx1 = i+OFFSET;
            continue;
        }
        if(ok){
            A[idx1-cnt-1] += A[i+OFFSET];
            cnt++;
            idx0 = min(idx0, idx1-cnt);
        }
    }
    for(int i = idx0; i <= idx1; i++){
        insertLast(&l, A[i]);
    }
    displayList(l);
    printf("\n");

    return 0;
}