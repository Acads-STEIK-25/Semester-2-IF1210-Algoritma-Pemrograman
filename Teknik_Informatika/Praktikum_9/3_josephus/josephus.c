#include <stdio.h>

typedef long long ll;
typedef unsigned long long ull;

int main() {
	// NOTE: you are supposed to use the already implemented Queue Datastructure here 
	// but I wanted to try with and use a ring buffer queue instead. 
	// Both approaches should be fine as the number of enqueue operations from the problem
	// is guaranteed to not exceed the CAPACITY defined in the given Queue header.

    int n, k;
    scanf("%d %d", &n, &k);

    char yeeted[50];

    for (int i = 0; i < n; i++) {
        yeeted[i] = 0;
    }

    int ptr = 0;
    for (int cycle = 0; cycle < n - 1; cycle++) {
        for (int i = 0; i < k; i++) {
            while (yeeted[ptr]) {
                ptr = (ptr + 1) % n;
            }
            ptr = (ptr + 1) % n;
        }
        while (yeeted[ptr]) {
            ptr = (ptr + 1) % n;
        }
        yeeted[ptr] = 1;
        ptr = (ptr + 1) % n;
    }

    while (yeeted[ptr]) {
        ptr = (ptr + 1) % n;
    }
    printf("%d", ptr + 1);

    return 0;
}
