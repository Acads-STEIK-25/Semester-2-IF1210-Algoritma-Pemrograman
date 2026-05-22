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

#include "listsirkuler.h"

void swap(int* a, int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

int sum[11];

int getMaximalSum(List* portals, int N){
    int n = N;
    rep(i, n) sum[i] = sumList(portals[i]);
    rep(i, n) rep(j, n-i-1) if(sum[j] < sum[j+1]) swap(&sum[j], &sum[j+1]);
    int ret = sum[0];
    rep(i, n-1){
        ret += sum[i+1];
        ret *= 2;
    }
    return ret;
}