#include "stack.h"

void CreateStack(Stack *s) { IDX_TOP(*s) = IDX_UNDEF; }

boolean isEmpty(Stack s) { return IDX_TOP(s) == IDX_UNDEF; }

boolean isFull(Stack s) { return IDX_TOP(s) == CAPACITY - 1; }

int length(Stack s) { return IDX_TOP(s) + 1; }

void push(Stack *s, ElType val) {
    IDX_TOP(*s)++;
    TOP(*s) = val;
}

void pop(Stack *s, ElType *val) {
    *val = TOP(*s);
    IDX_TOP(*s)--;
}
