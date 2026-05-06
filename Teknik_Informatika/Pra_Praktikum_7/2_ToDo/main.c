#include "ToDo.h"
#include <stdio.h>

typedef long long ll;
typedef unsigned long long ull;

void todo(void) {
    ToDoList l;
    createList(&l, 2);
    for (int i = 0; i < 10; i++) {
        if (isFull(l)) {
            expandList(&l, l.nEff);
        }
        addNewTask(&l, "Kenji sekdev");
    }
    printf("Completed: %d, Total: %d\n", getNumOfCompletedTasks(l),
           getNumOfTasks(l));
    for (int i = 0; i < l.nEff; i++) {
        printf("[%d] %s %d\n", i, l.tasksList[i].name, l.tasksList[i].status);
    }
}

int main() {
    todo();
    return 0;
}
