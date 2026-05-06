#include "LogScanner.h"
#include <stdio.h>

typedef long long ll;
typedef unsigned long long ull;

void scanner(void) {
    printf("===== INITIALIZATION =====\n");
    LogScanner l;
    CreateLogScanner(&l, 2);
    for (int i = 0; i < 10; i++) {
        LogItem item = {i, i, (i * 2) % 3 + 1};
        TambahLog(&l, item);
    }
    CetakStatusList(l);

    printf("===== FILTERING =====\n");
    LogScanner filter;
    FilterHighSeverity(l, &filter);
    CetakStatusList(filter);

    printf("===== REMOVING =====\n");
    for (int i = 3; i >= 0; i--) {
        LogItem val;
        printf("Remove %d\n", i * 3);
        HapusLog(&l, i * 3, &val);
        CetakStatusList(l);
    }
}

int main() {
    scanner();
    return 0;
}
