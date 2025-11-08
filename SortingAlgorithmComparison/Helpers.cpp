#include "Helpers.h"
#include <iostream>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <cstdlib>

using namespace std;

vector<int> GenerateRandomData(int N, int maxVal) {
    vector<int> data(N);
    for (int i = 0; i < N; ++i)
        data[i] = rand() % (maxVal + 1);
    return data;
}

void PrintStatistics(const vector<double>& durations, const string& label) {
    if (durations.empty()) return;

    double minTime = *min_element(durations.begin(), durations.end());
    double maxTime = *max_element(durations.begin(), durations.end());
    double avgTime = ComputeAverage(durations);
    double stdDev = ComputeStdDev(durations);

    cout << "\n=== Statistics for " << label << " ===\n";
    cout << "Min Time: " << minTime << " ms\n";
    cout << "Max Time: " << maxTime << " ms\n";
    cout << "Average Time: " << avgTime << " ms\n";
    cout << "Standard Deviation: " << stdDev << " ms\n";
    cout << "=====================================\n";
    cout << endl;
}

double ComputeAverage(const vector<double>& data) {
    if (data.empty()) return 0.0;
    double sum = accumulate(data.begin(), data.end(), 0.0);
    return sum / data.size();
}

double ComputeStdDev(const vector<double>& data) {
    if (data.empty()) return 0.0;
    double mean = ComputeAverage(data);
    double variance = 0.0;
    for (double x : data)
        variance += (x - mean) * (x - mean);
    return sqrt(variance / data.size());
}

void PrintVector(const vector<int>& data) {
    for (int num : data)
        cout << num << " ";
    cout << endl;
}
