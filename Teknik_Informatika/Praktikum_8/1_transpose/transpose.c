#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <float.h>
#define rep(i, n) for(int i = 0; i < n; i++)
#define float double

int main(){

    int n, m;
    scanf("%d %d", &n, &m);
    int A[n][m];
    rep(i, n) rep(j, m) scanf("%d", &A[i][j]);
    rep(j, m) rep(i, n){
        if(i != n-1) printf("%d ", A[i][j]);
        else printf("%d\n", A[i][j]);
    }
    
    return 0;
}