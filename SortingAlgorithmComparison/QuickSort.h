#ifndef QUICKSORT_H
#define QUICKSORT_H

#include <vector>

void QuickSort(std::vector<int>& arr);
void QuickSortRecursive(std::vector<int>& arr, int low, int high);
int Partition(std::vector<int>& arr, int low, int high);
void Swap(int& a, int& b);

#endif
