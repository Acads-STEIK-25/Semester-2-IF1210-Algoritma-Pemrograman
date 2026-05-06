#include <stdio.h>

typedef long long ll;
typedef unsigned long long ull;

#define MAX_COLS 20
#define MAX_ROWS 20

int main() {
	int n, m;
	scanf("%d %d", &n, &m);

	int mat[MAX_ROWS][MAX_COLS];

	for (int r = 0; r < n; r++) {
		for (int c = 0; c < m; c++) {
			scanf(" %d", &mat[r][c]);
		}
	}

	for (int r = 0; r < m; r++) {
		for (int c = 0; c < n; c++) {
			int ci = r;
			int ri = n - 1 - c;
			if (c + 1 == n) {
				printf("%d\n", mat[ri][ci]);
			} else {
				printf("%d ", mat[ri][ci]);
			}
		}
	}

	return 0;
}
