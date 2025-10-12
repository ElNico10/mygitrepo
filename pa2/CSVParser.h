#ifndef CSVPARSER_H
#define CSVPARSER_H

#include <string>
#include <vector>

//on success fills header (vector of column names) and rows (vector of rows. each row is vector<string> fields) and returns true
//also handles quoted fields and escaped quotes ("")
//basically just an aio reader lol
bool read_csv(const std::string& filename, std::vector<std::string>& header, std::vector<std::vector<std::string>>& rows);

#endif
