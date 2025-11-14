#ifndef SORT_H
#define SORT_H

#include <vector>
using namespace std;

namespace Sort
{
    // -----------------------------------------------
    // MERGE SORT — fully templated comparator
    // -----------------------------------------------

    template <typename T, typename Compare>
    void Merge(vector<T> &arr, int left, int mid, int right, Compare comp)
    {
        int n1 = mid - left + 1;
        int n2 = right - mid;

        vector<T> L(n1);
        vector<T> R(n2);

        for (int i = 0; i < n1; i++)
            L[i] = arr[left + i];

        for (int j = 0; j < n2; j++)
            R[j] = arr[mid + 1 + j];

        int i = 0, j = 0, k = left;

        while (i < n1 && j < n2)
        {
            if (comp(L[i], R[j]))
                arr[k++] = L[i++];
            else
                arr[k++] = R[j++];
        }

        while (i < n1) arr[k++] = L[i++];
        while (j < n2) arr[k++] = R[j++];
    }

    template <typename T, typename Compare>
    void MergeSortHelper(vector<T> &arr, int left, int right, Compare comp)
    {
        if (left >= right)
            return;

        int mid = left + (right - left) / 2;
        MergeSortHelper(arr, left, mid, comp);
        MergeSortHelper(arr, mid + 1, right, comp);
        Merge(arr, left, mid, right, comp);
    }

    template <typename T, typename Compare>
    void MergeSort(vector<T> &arr, Compare comp)
    {
        if (arr.size() > 1)
            MergeSortHelper(arr, 0, arr.size() - 1, comp);
    }

    // -----------------------------------------------
    // QUICK SORT — fully templated comparator
    // -----------------------------------------------

    template <typename T, typename Compare>
    int Partition(vector<T> &arr, int low, int high, Compare comp)
    {
        T pivot = arr[high];
        int i = low - 1;

        for (int j = low; j <= high - 1; j++)
        {
            if (comp(arr[j], pivot))
            {
                i++;
                swap(arr[i], arr[j]);
            }
        }

        swap(arr[i + 1], arr[high]);
        return i + 1;
    }

    template <typename T, typename Compare>
    void QuickSortHelper(vector<T> &arr, int low, int high, Compare comp)
    {
        if (low < high) 
        {
            int pi = Partition(arr, low, high, comp);
            QuickSortHelper(arr, low, pi - 1, comp);
            QuickSortHelper(arr, pi + 1, high, comp);
        }
    }

    template <typename T, typename Compare>
    void QuickSort(vector<T> &arr, Compare comp)
    {
        if (arr.size() > 1)
            QuickSortHelper(arr, 0, arr.size() - 1, comp);
    }
}

#endif
