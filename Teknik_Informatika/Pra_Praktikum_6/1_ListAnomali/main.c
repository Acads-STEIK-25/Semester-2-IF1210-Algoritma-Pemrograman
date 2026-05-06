#include <stdio.h>
#include "ListAnomali.h"

#define DEBUG_PRINT

#ifdef DEBUG_PRINT 

void print_arr_int(int *arr, int len) {
	for (int i = 0; i < len; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");
}
#define PRINT_ARR_INT(x, l) print_arr_int(x, l)

#else

void print_arr_int(int *arr, int len) {}
#define PRINT_ARR_INT(x, l)

#endif

typedef long long ll;
typedef unsigned long long ull;

#define ELEMS 12
int main() {
	printf("==== Initialization ====\n");

	ListAnomali l;
	CreateListAnomali(&l);
	for (int i = 0; i < ELEMS; i++) {
		if (i % 3 == 0) {
			insertAt(&l, i * 100, i);
		} else {
			insertAt(&l, i, i);
		}
	}
	printAnomalies(l);

	printf("==== Insertion ====\n");
	for (int i = ELEMS - 1; i >= 0; i--) {
		if (i % 3 == 0) {
			insertAt(&l, i * 100 + 50, i + 1);
		}
	}
	printAnomalies(l);

	printf("==== Deletion ====\n");
	for (int i = 0; i < ELEMS; i++) {
		if (i % 3 == 0) {
			int v;
			deleteAt(&l, i + 1, &v);
		}
	}
	printAnomalies(l);

	printf("==== Reversing ====\n");
	reverseList(&l);
	printAnomalies(l);
	reverseList(&l);
	printAnomalies(l);


	printf("==== Extracting ====\n");
	ListAnomali e;
	CreateListAnomali(&e);

	extractExtremeAnomalies(&l, &e);
	printAnomalies(l);
	printf("Len: %d\n", l.nEff);
	printAnomalies(e);
	printf("Len: %d\n", e.nEff);

	printf("==== Shift Right ====\n");
	for (int i = 0; i < 3; i++) {
		shiftRightByK(&l, i);
		printAnomalies(l);
	}


	return 0;
}
