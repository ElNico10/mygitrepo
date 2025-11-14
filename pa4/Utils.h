#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>
using namespace std;

namespace Utils
{
    string Trim(const string &s);
    vector<string> Split(const string &s, char delimiter);
    vector<string> ParseCSVLine(const string &line);

    int ToIntSafe(const string &s);     // returns 0 if NA or invalid
    double ToDoubleSafe(const string &s); // returns 0.0 if NA or invalid

    int ParseRuntime(const string &runtimeStr); 
    // Takes strings like "142 min" or "NA", returns minutes or 0
}

#endif
