// sortowania.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <time.h>
#include "sort.h"
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>

#define Size 20000
#define MaxNumber 1000
#define CNTRL 20		//drukowanie wynikow kontrolnych

using namespace std;

void cpTab(int** tab1, int* tab2);   // (1) do czego      (2) co 
int createTab(int** pTab, int size);
void filltab(int** pTab, int nSize);

typedef void (*pGT)(int*, int);


int main()
{
	int* originalTab = NULL;
	int* copyTab = NULL;

	if (!createTab(&originalTab, Size) || !createTab(&copyTab, Size))
		return 1;

	srand((unsigned int)time(NULL)); // liczby 'losowe' na potrzebe testow

	pGT sort[] = { insertionSort,selectionSort,bubbleSort,mixedSort,heapSort,doMergeSort,doQuickSort,mergeSort2 };
	char* names[] = { "insertionSort","selectionSort","bubbleSort","mixedSort","heapSort","mergeSort","quickSort","mergeSort2" };

	int size = sizeof(sort) / sizeof(pGT);

	time_t start;
	time_t end; 
	pGT* ptr = sort;
	double time;
	

	filltab(&originalTab, Size);					

	for (int i = 0; i < size; i++) {
		cpTab(&copyTab, originalTab);		
		start = clock();
		(*ptr++)(copyTab, Size);
		end = clock();
		time = (double)(end - start) / CLOCKS_PER_SEC;

#ifdef CNTRL
		int* pointer = copyTab;
		for (int i = 0; i < CNTRL; i++) {
			printf("%d ", *pointer++);
		}
		printf("\n");
#endif //CNTRL

		printf("sortowanie %s: %i elementow w: %.4f sekund\n\n", names[i], Size, time);
	}

	free(originalTab);
	free(copyTab);

	return 0;
}

void filltab(int** pTab, int nSize) {
	for (int i = 0; i < nSize; i++) {
		(*pTab)[i] = rand() % MaxNumber;
	}
}

void cpTab(int** tab1, int* tab2) {
	memcpy(*tab1, tab2, sizeof(int)*Size);
}