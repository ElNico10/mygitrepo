#ifndef SHELLSORT_H
#define SHELLSORT_H

#include <vector>

//Shellsort algorithm (default gap sequence)
void ShellSort(std::vector<int>& arr);

//alternate shellsort with custom gap sequence
void ShellSortWithGaps(std::vector<int>& arr, const std::vector<int>& gaps);

#endif
