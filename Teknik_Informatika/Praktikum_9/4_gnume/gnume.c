#include "queue.h"
#include <stdio.h>

typedef long long ll;
typedef unsigned long long ull;

int main() {
    int n;
    scanf("%d", &n);

    int underlings[200];
    int hierarch[200][200];
    for (int ni = 0; ni < n; ni++) {
        underlings[ni] = 0;
    }
    for (int ni = 0; ni < n; ni++) {
        scanf("%d", &underlings[ni]);
        for (int mi = 0; mi < underlings[ni]; mi++) {
            int miv;
            scanf("%d", &miv);
            hierarch[ni][mi] = miv - 1; // zero indexed
        }
    }

    Queue q;
    CreateQueue(&q);

    enqueue(&q, 0);
    while (!isEmpty(q)) {
        int ni;
        dequeue(&q, &ni);
        if (ni == 0) {
            printf("1");
        } else {
            printf(" %d", ni + 1);
        }

        for (int mi = 0; mi < underlings[ni]; mi++) {
            enqueue(&q, hierarch[ni][mi]);
        }
    }

    return 0;
}
