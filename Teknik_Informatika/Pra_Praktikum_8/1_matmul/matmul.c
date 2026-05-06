#include <stdio.h>

typedef long long ll;
typedef unsigned long long ull;

#define MAX_COLS 20
#define MAX_ROWS 20

int main() {
	int n, k, p;
	scanf("%d %d %d", &n, &k, &p);

	int mat1[MAX_ROWS][MAX_COLS];
	int mat2[MAX_ROWS][MAX_COLS];

	for (int r = 0; r < n; r++) {
		for (int c = 0; c < k; c++) {
			scanf(" %d", &mat1[r][c]);
		}
	}

	for (int r = 0; r < k; r++) {
		for (int c = 0; c < p; c++) {
			scanf(" %d", &mat2[r][c]);
		}
	}

	for (int r = 0; r < n; r++) {
		for (int c = 0; c < p; c++) {
			int sum = 0;
			for (int i = 0; i < k; i++) {
				sum += mat1[r][i] * mat2[i][c];
			}
			if (c + 1 == p) {
				printf("%d\n", sum);
			} else {
				printf("%d ", sum);
			}
		}
	}

	return 0;
}
