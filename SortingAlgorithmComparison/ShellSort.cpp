#include "ShellSort.h"

// Default implementation of Shell Sort using gap sequence: N/2, N/4, ..., 1
void ShellSort(std::vector<int>& arr) {
    int n = static_cast<int>(arr.size());
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; ++i) {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
                arr[j] = arr[j - gap];
            arr[j] = temp;
        }
    }
}

// Custom gap sequence (e.g., {701, 301, 132, 57, 23, 10, 4, 1})
void ShellSortWithGaps(std::vector<int>& arr, const std::vector<int>& gaps) {
    int n = static_cast<int>(arr.size());
    for (int gap : gaps) {
        for (int i = gap; i < n; ++i) {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
                arr[j] = arr[j - gap];
            arr[j] = temp;
        }
    }
}
