#include "stack.h"
#include <stdio.h>

typedef long long ll;
typedef unsigned long long ull;

int main() {
    char c;
    scanf("%c", &c);
    if (!(c == '(' || c == ')' || c == '[' || c == ']' || c == '{' ||
          c == '}')) {
        printf("Valid\n0\n");
        return 0;
    }

    int failed = 0;
    int pairs = 0;
    Stack stack;
    CreateStack(&stack);
    while (c == '(' || c == ')' || c == '[' || c == ']' || c == '{' ||
           c == '}') {
        if (c == '(' || c == '[' || c == '{') {
            push(&stack, c);
            scanf("%c", &c);
            continue;
        }

        if (isEmpty(stack)) {
            failed = 1;
            break;
        }

        char cs;
        pop(&stack, &cs);

        if ((c == ')' && cs != '(') || (c == ']' && cs != '[') ||
            (c == '}' && cs != '{')) {
            failed = 1;
            break;
        } else {
            pairs++;
        }

        scanf("%c", &c);
    }

    if (failed || !isEmpty(stack)) {
        printf("Invalid\n%d\n", pairs);
    } else {
        printf("Valid\n%d\n", pairs);
    }

    return 0;
}
