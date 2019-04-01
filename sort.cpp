#include <iostream>
#include "sort.h"

int cpy(int* pTab, int* pTab2, int* i, int* j, int nSize);
void cpySerie(int* pTab, int* pTab2, int* i, int* j, int nSize);
void Update(int* pTab, int l, int p);
void merge(int* t, int* tab, int n, int l, int m, int p);



int createTab(int** pTab, int size) {
	*pTab = (int*)calloc(size, sizeof(int));
	if (!pTab) {
		perror("nie udalo sie zaalokowac pamieci\n");
		return 0;
	}
	return 1;
}



void insertionSort(int* tab, int size) {
	for (int i = 1; i < size; i++) {
		int klucz = tab[i];
		int j = i - 1;
		while (j >= 0 && tab[j] > klucz) {
			tab[j + 1] = tab[j];
			j--;
		}
		tab[j + 1] = klucz;
	}
}


void selectionSort(int* tab, int size) {
	for (int i = 0; i < size-1; i++) {
		int min = tab[i];
		int index = i;
		for (int j = i+1; j < size; j++) {
			if (tab[j] < min) {
				index = j;
				min = tab[j];
			}
		}
		tab[index] = tab[i];
		tab[i] = min;
	}
}


void bubbleSort(int* tab, int size) {
	for (int i = 0; i < size; i++) {
		for (int j = size; j > i; j--) {
			if (tab[j] < tab[j-1]) {
				int temp = tab[j-1];
				tab[j-1] = tab[j];
				tab[j] = temp;
			}
		}
	}
}

void mixedSort(int* pTab, int nSize){
	int k = nSize - 1;
	int l = 1;
	int p = nSize - 1;

	do{
		for (int i = p; i >= l; i--){
			if (pTab[i - 1] > pTab[i]){
				int tmp = pTab[i - 1];
				pTab[i - 1] = pTab[i];
				pTab[i] = tmp;
				k = i;
			}
		}

		l = k + 1;

		for (int i = l; i <= p; i++){
			if (pTab[i - 1] > pTab[i]){
				int tmp = pTab[i - 1];
				pTab[i - 1] = pTab[i];
				pTab[i] = tmp;
				k = i;
			}
		}
		p = k - 1;
	} while (l <= p);
}

void Update(int* pTab, int l, int p){

	if (l == p) return;

	int i = l;
	int j = 2 * i + 1;
	int tmp = pTab[i];

	while (j <= p){
		if (j < p)
			if (pTab[j] < pTab[j + 1]) j++;

		if (tmp >= pTab[j]) break;

		pTab[i] = pTab[j];
		i = j;
		j = 2 * i + 1;
	}

	pTab[i] = tmp;
}

void heapSort(int* pTab, int nSize){

	int p = nSize - 1;
	int l;

	for (l = nSize / 2; l >= 0; l--)
		Update(pTab, l, p);
	

	for (p = nSize - 1; p > 0; p--){
		int tmp = pTab[0];
		pTab[0] = pTab[p];
		pTab[p] = tmp;

		Update(pTab, 0, p - 1);
	}
}

void quickSort(int* pTab, int l, int p){

	int i = l;
	int j = p;
	int x = pTab[(l + p) / 2];

	while (i < j){
		while (pTab[i] < x) i++;
		while (pTab[j] > x) j--;

		if (i <= j){
			int tmp = pTab[i];
			pTab[i] = pTab[j];
			pTab[j] = tmp;

			i++;
			j--;
		}
	}

	if (l < j) quickSort(pTab, l, j);
	if (i < p) quickSort(pTab, i, p);
}

void doQuickSort(int* pTab, int nSize){
	int l = 0;
	int p = nSize - 1;
	quickSort(pTab, l, p);
}

void merge(int* t, int* tab, int n, int l, int m, int p){
	memcpy(tab, t, sizeof(int) * n);

	int i = l;
	int j = m + 1;
	int q = l;

	while ((i <= m) && (j <= p)){
		if (tab[i] < tab[j]) t[q++] = tab[i++];
		else t[q++] = tab[j++];
	}

	while (i <= m) 
		t[q++] = tab[i++];
}

void mergeSort(int* t, int* tab, int n, int l, int p){
	if (l < p){
		int m = (l + p) / 2;
		mergeSort(t, tab, n, l, m);//lewa podtablica
		mergeSort(t, tab, n, m + 1, p);//prawa podtablica
		merge(t, tab, n, l, m, p);//sortujemy podtablice
	}
}

void doMergeSort(int* pTab, int nSize){
	int* Tab = NULL;
	int l = 0;
	int p = nSize - 1;

	createTab(&Tab, nSize);

	mergeSort(pTab, Tab, nSize, l, p);
}

void mergeSort2(int* pTab, int nSize){//sortowanie z wykladu

	int* pTab1 = NULL;
	int* pTab2 = NULL;

	createTab(&pTab1, nSize);
	createTab(&pTab2, nSize);

	int n;

	do{
		int i = 0;//pTab
		int j = 0;//pTab1
		int k = 0;//pTab2

		while (i < nSize){//rozdzielamy tablice na dwie tablice
		
			while ((i < nSize - 1) && (pTab[i] <= pTab[i + 1]))
				pTab1[j++] = pTab[i++];

			if (i<nSize) pTab1[j++] = pTab[i++];

			while ((i < nSize - 1) && (pTab[i] <= pTab[i + 1]))
				pTab2[k++] = pTab[i++];

			if (i<nSize) pTab2[k++] = pTab[i++];
		}

		int k1 = j;
		int k2 = k;
		n = 0;
		i = j = k = 0;

		while ((i < k1) && (j < k2)){
			int end = 0;

			while (!end){
				if (pTab1[j] <= pTab2[k]){
					end = cpy(pTab, pTab1, &i, &j, k1);

					if (end)
						cpySerie(pTab, pTab2, &i, &k, k2);
				}
				else{
					end = cpy(pTab, pTab2, &i, &k, k2);

					if (end)
						cpySerie(pTab, pTab1, &i, &j, k1);
				}
			}

			n++;
		}

		while (j < k1){
			cpySerie(pTab, pTab1, &i, &j, k1);
			n++;
		}

		//while (k < k2){
			//cpySerie(pTab, pTab2, &i, &k, k2);
			//n++;
		//}

	} while (n > 1);

	free(pTab1);
	free(pTab2);
}

void cpySerie(int* pTab, int* pTab2, int* i, int* j, int nSize){
	int end = 1;

	do{
		end = cpy(pTab, pTab2, i, j, nSize);

	} while (!end);
}

int cpy(int* pTab, int* pTab2, int* i, int* j, int nSize){
	pTab[(*i)++] = pTab2[(*j)++];

	if (*j == nSize) 
		return 1;

	return (pTab2[*j - 1]) > (pTab2[*j]);
}
