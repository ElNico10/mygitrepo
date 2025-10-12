#include <iostream>
#include <vector>
#include <map>
#include <random>
#include <chrono>
#include <algorithm>

#include "AVLMap.h"
#include "USCity.h"
#include "CSVParser.h"

int main(int argc, char** argv) {
    std::string csvfile = "uszips.csv";
    if (argc > 1) csvfile = argv[1];

    std::vector<std::string> header;
    std::vector<std::vector<std::string>> rows;
    if (!read_csv(csvfile, header, rows)) {
        std::cerr << "Failed to read CSV " << csvfile << std::endl;
        return 1;
    }

    //try to detect ZIP column (common names). case-insensitive compare
    int zip_idx = -1;
    for (size_t i = 0; i < header.size(); ++i) {
        std::string h = header[i];
        // lowercase
        for (auto &c : h) c = static_cast<char>(std::tolower(c));
        if (h == "zip" || h == "zip code" || h == "zipcode" || h == "zip_code" || h == "zip5" || h == "zip_code_tab" || h == "zip5") {
            zip_idx = static_cast<int>(i);
            break;
        }
    }
    if (zip_idx == -1) {
        //fallback to first column if detection failed
        zip_idx = 0;
    }

    AVLMap avl;
    std::map<int, USCity> smap;

    //collect zip keys for benchmarking
    std::vector<int> all_zips;
    all_zips.reserve(rows.size());

    for (auto &r : rows) {
        if ((int)r.size() <= zip_idx) continue;
        std::string zipstr = r[zip_idx];
        // trim whitespace
        while (!zipstr.empty() && isspace(zipstr.front())) zipstr.erase(zipstr.begin());
        while (!zipstr.empty() && isspace(zipstr.back())) zipstr.pop_back();
        if (zipstr.empty()) continue;

        //try parse integer zip; some csv use leading zeroes — parsing as int (loses leading zeros)
        int zip = 0;
        try {
            zip = std::stoi(zipstr);
        } catch (...) {
            continue;
        }

        USCity city;
        for (size_t i = 0; i < header.size() && i < r.size(); ++i) {
            city.set_column(header[i], r[i]);
        }

        avl.insert(zip, city);
        smap.emplace(zip, city);
        all_zips.push_back(zip);
    }

    std::cout << "Loaded entries: AVL=" << avl.size() << ", std::map=" << smap.size() << std::endl;
    if (avl.size() == 0) {
        std::cerr << "No entries loaded; check csv parsing and zip column detection." << std::endl;
        return 1;
    }

    //shuffle and pick test set
    std::mt19937 rng(static_cast<unsigned int>(std::chrono::high_resolution_clock::now().time_since_epoch().count()));
    std::shuffle(all_zips.begin(), all_zips.end(), rng);

    std::size_t lookups = 1000;
    if (all_zips.size() < lookups) lookups = all_zips.size();
    std::vector<int> test_keys(all_zips.begin(), all_zips.begin() + lookups);

    //warm-up - run a few finds to warm caches
    for (std::size_t i = 0; i < 50 && i < test_keys.size(); ++i) {
        avl.find(test_keys[i]);
        smap.find(test_keys[i]);
    }

    //benchmark avl
    auto t1 = std::chrono::high_resolution_clock::now();
    std::size_t found_avl = 0;
    for (int k : test_keys) {
        USCity* p = avl.find(k);
        if (p) ++found_avl;
    }
    auto t2 = std::chrono::high_resolution_clock::now();
    double avl_ms = std::chrono::duration<double, std::milli>(t2 - t1).count();

    //benchmark std::map
    auto t3 = std::chrono::high_resolution_clock::now();
    std::size_t found_map = 0;
    for (int k : test_keys) {
        auto it = smap.find(k);
        if (it != smap.end()) ++found_map;
    }
    auto t4 = std::chrono::high_resolution_clock::now();
    double map_ms = std::chrono::duration<double, std::milli>(t4 - t3).count();

    std::cout << "Performed " << lookups << " lookups.\n";
    std::cout << "AVL: found " << found_avl << " entries in " << avl_ms << " ms\n";
    std::cout << "std::map: found " << found_map << " entries in " << map_ms << " ms\n";

    //print a sample entry
    int sample = test_keys[0];
    std::cout << "\nSample ZIP used: " << sample << std::endl;
    USCity* pv = avl.find(sample);
    if (pv) {
        std::string s = pv->to_string();
        if (s.size() > 400) s = s.substr(0, 400) + "...";
        std::cout << "AVL sample data (truncated): " << s << std::endl;
    }
    auto it = smap.find(sample);
    if (it != smap.end()) {
        std::string s = it->second.to_string();
        if (s.size() > 400) s = s.substr(0, 400) + "...";
        std::cout << "std::map sample data (truncated): " << s << std::endl;
    }

    return 0;
}
