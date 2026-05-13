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

        if (c == '+' || c == '-' || c == '*' || c == '/' || c == '%') {
            char op1, op2;
            pop(&stack, &op2);
            pop(&stack, &op1);
            char res;
            switch (c) {
            case '+':
                res = op1 + op2;
                break;
            case '-':
                res = op1 - op2;
                break;
            case '*':
                res = op1 * op2;
                break;
            case '/':
                res = op1 / op2;
                break;
            case '%':
                res = op1 % op2;
                break;
            default:
                return 1;
            }
            push(&stack, res);
        } else if (c >= '0' && c <= '9') {
            push(&stack, c - '0');
        }
    }
    char result;
    pop(&stack, &result);
    printf("%d\n", result);
    return 0;
}
