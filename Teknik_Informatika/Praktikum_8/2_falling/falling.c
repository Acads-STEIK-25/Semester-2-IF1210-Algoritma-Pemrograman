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
    int B[m][n];
    int idx = 0;
    rep(j, m){
        idx = 0;
        for(int i = n-1; i >= 0; i--){
            if(A[i][j] != 0){
                B[j][idx] = A[i][j];
                idx++;
            }
        }
        for(int k = idx; k < n; k++){
            B[j][k] = 0;
        }
    }
    // rep(i, m){
    //     rep(j, n){
    //         printf("%d ", B[i][j]);
    //     }
    //     printf("\n");
    // }
    for(int i = n-1; i >= 0; i--){
        rep(j, m){
            if(j != m-1) printf("%d ", B[j][i]);
                else printf("%d\n", B[j][i]);
        }
    }
    
    return 0;
}