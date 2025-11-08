#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <algorithm>
#include <numeric>
#include <cmath>

#include "Helpers.h"
#include "InsertionSort.h"
#include "QuickSort.h"
#include "ShellSort.h"

using namespace std;

int main()
{
    const int N = 10000;
    const int MAX_VAL = 100000;
    const int TRIALS = 10;

    srand(static_cast<unsigned>(time(nullptr)));

    vector<double> durations;

    //insertion sort benchmark
    for (int trial = 0; trial < TRIALS; ++trial)
    {
        vector<int> data = GenerateRandomData(N, MAX_VAL);

        auto start = chrono::high_resolution_clock::now();
        InsertionSort(data);
        auto end = chrono::high_resolution_clock::now();

        chrono::duration<double, milli> elapsed = end - start;
        durations.push_back(elapsed.count());

        cout << "Trial " << trial + 1 << " duration: " << elapsed.count() << " ms\n";
    }

    PrintStatistics(durations, "Insertion Sort");

    //insertion sort benchmark
    durations.clear();
    for (int trial = 0; trial < TRIALS; ++trial)
    {
        vector<int> data = GenerateRandomData(N, MAX_VAL);

        auto start = chrono::high_resolution_clock::now();
        QuickSort(data);
        auto end = chrono::high_resolution_clock::now();

        chrono::duration<double, milli> elapsed = end - start;
        durations.push_back(elapsed.count());

        cout << "Trial " << trial + 1 << " duration: " << elapsed.count() << " ms\n";
    }

    PrintStatistics(durations, "Quick Sort");

    //shellsort benchmark
    durations.clear();
    for (int trial = 0; trial < TRIALS; ++trial)
    {
        vector<int> data = GenerateRandomData(N, MAX_VAL);

        auto start = chrono::high_resolution_clock::now();
        ShellSort(data);
        auto end = chrono::high_resolution_clock::now();

        chrono::duration<double, milli> elapsed = end - start;
        durations.push_back(elapsed.count());

        cout << "Trial " << trial + 1 << " duration: " << elapsed.count() << " ms\n";
    }

    PrintStatistics(durations, "Shell Sort");

    return 0;
}
