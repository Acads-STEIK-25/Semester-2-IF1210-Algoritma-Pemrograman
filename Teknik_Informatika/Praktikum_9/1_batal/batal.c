#include "stack.h"
#include <stdio.h>

typedef long long ll;
typedef unsigned long long ull;

int main() {
    Stack stack;
    CreateStack(&stack);

    char c;
    while (scanf("%c", &c) == 1) {
        if (c == '\n' || c == '\0') {
            break;
        }

        if (isEmpty(stack)) {
            push(&stack, c);
        } else {
            char cp;
            pop(&stack, &cp);
            if (cp == c) {
                continue;
            } else {
                push(&stack, cp);
                push(&stack, c);
            }
        }
    }

    if (isEmpty(stack)) {
        printf("Kosong\n");
        return 0;
    }

    Stack rev_stack;
    CreateStack(&rev_stack);
    while (!isEmpty(stack)) {
        pop(&stack, &c);
        push(&rev_stack, c);
    }
    while (!isEmpty(rev_stack)) {
        pop(&rev_stack, &c);
        printf("%c", c);
    }
    printf("\n");
    return 0;
}
