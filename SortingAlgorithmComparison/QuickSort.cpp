#include "QuickSort.h"

void QuickSort(std::vector<int>& arr) {
    if (arr.empty()) return;
    QuickSortRecursive(arr, 0, static_cast<int>(arr.size()) - 1);
}

void QuickSortRecursive(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        int pivotIndex = Partition(arr, low, high);
        QuickSortRecursive(arr, low, pivotIndex - 1);
        QuickSortRecursive(arr, pivotIndex + 1, high);
    }
}

int Partition(std::vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; ++j) {
        if (arr[j] <= pivot) {
            ++i;
            Swap(arr[i], arr[j]);
        }
    }
    Swap(arr[i + 1], arr[high]);
    return i + 1;
}

void Swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}
