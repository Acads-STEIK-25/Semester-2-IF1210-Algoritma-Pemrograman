#include <stdio.h>

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    int mat[100][100];
    for (int ri = 0; ri < n; ri++) {
        for (int ci = 0; ci < m; ci++) {
            scanf("%d", &mat[ri][ci]);
        }
    }

	// sqsides[i][j] = side length of the largest square whose bottom right corner is at mat[i][j]
    int sqsides[100][100];
    int max = 0;
    int sawit = 0;

    for (int ri = 0; ri < n; ri++) {
        for (int ci = 0; ci < m; ci++) {
            int side = 0;
            if (mat[ri][ci] > 0) {
                side = 1;
                if (ri > 0 && ci > 0) {
					// side length of the largest square whose bottom right corner is this cell 
					// is just the minimum of the square side lengths from the 
					// cell above, 
					// cell to the left, 
					// and cell to the upper left diagonal,
					// + 1 (this square)
                    int up = sqsides[ri - 1][ci];
                    int left = sqsides[ri][ci - 1];
                    int diag = sqsides[ri - 1][ci - 1];
                    int min = diag;
                    if (left < min) {
                        min = left;
                    }
                    if (up < min) {
                        min = up;
                    }
                    side += min;
                }
            }

            if (side * side > max) {
                max = side * side;
            }

            if (side > 0) {
                sawit += side;
            }

            sqsides[ri][ci] = side;
        }
    }

    printf("MAX %d\n", max);
    printf("TOTAL %d\n", sawit);

    return 0;
}
