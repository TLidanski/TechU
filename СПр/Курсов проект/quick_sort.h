#ifndef QUICK_SORT_H
#define QUICK_SORT_H

int partition(int arr[], int firstEle, int lastEle);
void quickSort(int arr[], int firstEle, int lastEle);
void* quickSortWrapper(void *args);

#endif