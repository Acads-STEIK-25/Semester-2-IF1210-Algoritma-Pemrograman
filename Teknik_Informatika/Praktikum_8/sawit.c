// Jika anda bruteforce saja, solusi anda akan mendapat verdict Time Limit Exceeded (TLE).
// Optimisasinya menggunakan prefix_sum 2 dimensi, pelajari di link berikut:
// https://www.geeksforgeeks.org/dsa/prefix-sum-2d-array/

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

    int n, m;
    scanf("%d %d", &n, &m);
    int A[n][m];
    rep(i, n) rep(j, m) scanf("%d", &A[i][j]);
    int prefix_sum[n + 1][m + 1];
    rep(i, n + 1) rep(j, m + 1) prefix_sum[i][j] = 0;
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            prefix_sum[i][j] = prefix_sum[i - 1][j] + prefix_sum[i][j - 1] - prefix_sum[i - 1][j - 1] + A[i - 1][j - 1];
        }
    }
    int maxim = 0;
    int cnt = 0;
    int MAX_K = max(n, m);
    for(int i = 1; i <= MAX_K; i++){
        for(int cur_x = 0; cur_x < n; cur_x++){
            for(int cur_y = 0; cur_y < m; cur_y++){
                if(cur_x + i - 1 >= n) break;
                if(cur_y + i - 1 >= m) break;
                int sum = 0;
                sum = prefix_sum[cur_x + i][cur_y + i] - prefix_sum[cur_x][cur_y + i] - prefix_sum[cur_x + i][cur_y] + prefix_sum[cur_x][cur_y];
                if(sum == i*i){
                    maxim = max(maxim, i*i);
                    cnt++;
                }
            }
        }
    }
    printf("MAX %d\nTOTAL %d\n", maxim, cnt);

    return 0;
}
