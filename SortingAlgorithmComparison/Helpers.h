#ifndef HELPERS_H
#define HELPERS_H

#include <vector>
#include <string>

std::vector<int> GenerateRandomData(int N, int maxVal);
void PrintStatistics(const std::vector<double>& durations, const std::string& label);
double ComputeAverage(const std::vector<double>& data);
double ComputeStdDev(const std::vector<double>& data);
void PrintVector(const std::vector<int>& data);

#endif
