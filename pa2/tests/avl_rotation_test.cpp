#include <iostream>
#include <cassert>
#include <cmath>
#include "AVLMap.h"
#include "USCity.h"

//NOTE: due to vscode bugs i asked copilot to write a script to test rotations as vscode kept moving my breakpoints or hallucinating new ones randomly. this is NOT my work, just a test.

// Small helper to create a USCity with a single column
USCity make_city(const std::string& name) {
    USCity c;
    c.set_column("city", name);
    return c;
}

// We can't easily inspect internal structure because Node is private,
// but we can infer rotations by checking tree height after skewed inserts.

int main() {
    AVLMap m;

    // Insert ascending keys to force right-right heavy inserts
    // which should trigger left rotations and keep height ~log2(n)
    const int N = 15; // 15 nodes -> balanced height should be <= 5
    for (int i = 1; i <= N; ++i) {
        m.insert(i, make_city("City" + std::to_string(i)));
    }

    std::size_t s = m.size();
    std::cout << "Inserted " << s << " nodes\n";

    // Quick sanity checks
    assert(s == (std::size_t)N && "size mismatch after inserts");

    // Check a few find operations
    for (int k : {1, N/2, N}) {
        auto ptr = m.find(k);
        assert(ptr && "find failed for existing key");
        std::cout << "key=" << k << " -> " << ptr->city_name() << "\n";
    }

    int h = m.max_height();
    std::cout << "Tree max height = " << h << "\n";

    // crude bound: AVL trees have logarithmic height. For safety allow some slack:
    // require height <= 2 * log2(N)
    double bound = 2.0 * std::log2((double)N);
    std::cout << "Allowable height bound (2*log2(N)) = " << bound << "\n";
    assert((double)h <= bound && "tree height exceeds expected AVL bound; rotations may be broken");

    std::cout << "Tree height within expected bound. Rotations likely happening." << std::endl;

    std::cout << "Test completed OK." << std::endl;
    return 0;
}
