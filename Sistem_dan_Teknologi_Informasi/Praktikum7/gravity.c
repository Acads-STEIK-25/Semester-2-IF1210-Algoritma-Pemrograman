#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

#define boolean unsigned char
#define true 1
#define false 0

int main() {
    int n;  
    scanf("%d", &n);

    int anomali[10000];
    for (int i = 0; i < n; i++) {
        scanf("%d", &anomali[i]);
    }
    Stack s;
    CreateStack(&s);


    for (int i = 0; i < n; i++) {
        int now = anomali[i];
        boolean survived = true;

        if (now < 0) {
            while (!isEmpty(s) && TOP(s) > 0) {
                int top_val = TOP(s);
                int now_abs = -now;

                if (top_val < now_abs) {

                    int val;
                    pop(&s, &val);

                } else if (top_val == now_abs) {

                    int val;
                    pop(&s, &val);
                    survived = false;
                    break;
                } else {

                    survived = false;
                    break;
                }
            }
        }

        if (survived) {
            push(&s, now);
        }
    }

    if (isEmpty(s)) {
        printf("Celah telah tertutup\n");
    } else {
        int hasil[CAPACITY];
        int jumlah = 0;
        int val;
        while (!isEmpty(s)) {
            pop(&s, &val);
            hasil[jumlah++] = val;
        }
        for (int i = jumlah - 1; i >= 0; i--) {
            printf("%d", hasil[i]);
            if (i > 0) printf(" ");
        }
        printf("\n");
    }

    return 0;
}