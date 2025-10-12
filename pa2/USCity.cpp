#include "USCity.h"
#include <sstream>

void USCity::set_column(const std::string& name, const std::string& value) {
    columns[name] = value;
}

std::string USCity::get(const std::string& name) const {
    auto it = columns.find(name);
    if (it == columns.end()) return std::string();
    return it->second;
}

std::string USCity::city_name() const {
    //common column names
    if (columns.count("city")) return columns.at("city");
    if (columns.count("city_canonical")) return columns.at("city_canonical");
    if (columns.count("city_alias")) return columns.at("city_alias");
    return std::string();
}

std::string USCity::state() const {
    if (columns.count("state_id")) return columns.at("state_id");
    if (columns.count("state")) return columns.at("state");
    return std::string();
}

std::string USCity::to_string() const {
    std::ostringstream oss;
    bool first = true;
    for (auto &p : columns) {
        if (!first) oss << "; ";
        first = false;
        oss << p.first << "=" << p.second;
    }
    return oss.str();
}
