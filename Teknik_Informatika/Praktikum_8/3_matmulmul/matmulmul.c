#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <float.h>
#define rep(i, n) for(int i = 0; i < n; i++)
#define float double
#define ll long long

const ll MOD = 1e9;

int max(int a, int b){
    if(a > b) return a;
        else return b;
}

int main(){

    int n;
    scanf("%d", &n);
    int size[n+1];
    int maxim = 0;
    rep(i, n+1){
        scanf("%d", &size[i]);
        maxim = max(maxim, size[i]);
    } 
    ll A[n][maxim+3][maxim+3];
    rep(i, n) rep(j, maxim+3) rep(k, maxim+3) A[i][j][k] = 0;
    rep(i, n){
        rep(j, size[i]) rep(k, size[i+1]) scanf("%lld", &A[i][j][k]);
    }
    ll TEMP[maxim+3][maxim+3];
    rep(cur, n-1){
        rep(j, maxim+3) rep(k, maxim+3) TEMP[j][k] = 0;
        rep(i, size[cur]) rep(j, size[cur+2]) rep(k, size[cur+1]){
            TEMP[i][j] += A[cur][i][k] * A[cur+1][k][j];
            TEMP[i][j] %= MOD;
        } 
        size[cur+1] = size[cur];
        rep(i, size[cur+1]) rep(j, size[cur+2]) A[cur+1][i][j] = TEMP[i][j];
    }
    rep(i, size[0]) rep(j, size[n]){
        if(j != size[n]-1) printf("%lld ", A[n-1][i][j]);
            else printf("%lld\n", A[n-1][i][j]);
    }

    return 0;
}