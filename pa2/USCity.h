#ifndef USCITY_H
#define USCITY_H

#include <string>
#include <unordered_map>

struct USCity {
    //map column name -> cell value
    std::unordered_map<std::string, std::string> columns;

    USCity() = default;

    void set_column(const std::string& name, const std::string& value);
    std::string get(const std::string& name) const;

    //convenience accessors
    std::string city_name() const;
    std::string state() const;
    std::string to_string() const;
};

#endif