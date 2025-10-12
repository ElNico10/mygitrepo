#include "CSVParser.h"
#include <fstream>
#include <iostream>
#include <sstream>

//helper to split csv line into fields handling quotes and escaped quotes
static std::vector<std::string> split_csv_line(const std::string& line) {
    std::vector<std::string> fields;
    std::string cur;
    bool in_quotes = false;
    for (size_t i = 0; i < line.size(); ++i) {
        char c = line[i];
        if (c == '"') {
            if (in_quotes && i + 1 < line.size() && line[i + 1] == '"') {
                //escaped quote moment
                cur.push_back('"');
                ++i;
            } else {
                in_quotes = !in_quotes;
            }
        } else if (c == ',' && !in_quotes) {
            fields.push_back(cur);
            cur.clear();
        } else {
            cur.push_back(c);
        }
    }
    fields.push_back(cur);
    return fields;
}

bool read_csv(const std::string& filename, std::vector<std::string>& header, std::vector<std::vector<std::string>>& rows) {
    std::ifstream in(filename);
    if (!in) {
        std::cerr << "Could not open CSV file: " << filename << std::endl;
        return false;
    }
    std::string line;
    if (!std::getline(in, line)) {
        std::cerr << "CSV file empty: " << filename << std::endl;
        return false;
    }
    header = split_csv_line(line);

    while (std::getline(in, line)) {
        //skip empty lines
        if (line.empty()) continue;
        auto fields = split_csv_line(line);
        //pad short rows to header size. fancy ("csvs be like that sometimes" ~github copilot)
        if (fields.size() < header.size()) fields.resize(header.size(), "");
        rows.push_back(std::move(fields));
    }
    return true;
}
