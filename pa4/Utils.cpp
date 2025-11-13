#include "Utils.h"
#include <algorithm>
#include <cctype>
#include <sstream>

namespace Utils
{
    string Trim(const string &s)
    {
        if (s.empty()) return s;
        size_t start = 0;
        size_t end = s.size() - 1;

        while (start < s.size() && isspace(s[start]))
            start++;

        while (end > start && isspace(s[end]))
            end--;

        return s.substr(start, end - start + 1);
    }

    vector<string> Split(const string &s, char delimiter)
    {
        vector<string> parts;
        string temp;
        stringstream ss(s);

        while (getline(ss, temp, delimiter))
        {
            string cleaned = Trim(temp);
            if (!cleaned.empty())
                parts.push_back(cleaned);
        }

        return parts;
    }

    int ToIntSafe(const string &s)
    {
        try
        {
            if (s == "NA" || s == "" || s == "null")
                return 0;
            return stoi(s);
        }
        catch (...)
        {
            return 0;
        }
    }

    double ToDoubleSafe(const string &s)
    {
        try
        {
            if (s == "NA" || s == "" || s == "null")
                return 0.0;
            return stod(s);
        }
        catch (...)
        {
            return 0.0;
        }
    }

    int ParseRuntime(const string &runtimeStr)
    {
        if (runtimeStr == "NA" || runtimeStr == "" || runtimeStr == "null")
            return 0;

        // Expect formats like "142 min", "60 min", etc.
        string numberPart;
        for (char c : runtimeStr)
        {
            if (isdigit(c))
                numberPart.push_back(c);
        }

        if (numberPart.empty())
            return 0;

        return ToIntSafe(numberPart);
    }
}
