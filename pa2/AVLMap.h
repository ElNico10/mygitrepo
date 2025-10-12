#ifndef AVLMAP_H
#define AVLMAP_H

#include <cstddef>//size_t
#include "USCity.h"

class AVLMap {
public:
    AVLMap();
    ~AVLMap();

    //non-copyable for simplicity
    AVLMap(const AVLMap&) = delete;
    AVLMap& operator=(const AVLMap&) = delete;

    //insert key -> value. If key exists, update value
    void insert(int key, const USCity& value);

    //find pointer to stored value, or nullptr if not found
    USCity* find(int key);
    const USCity* find(int key) const;

    //number of nodes
    std::size_t size() const;

    // debug helper: compute maximum tree height (1 for single node, 0 for empty)
    int max_height() const;

private:
    struct Node {
        int key;
        USCity value;
        Node* left;
        Node* right;
        int height;
        Node(int k, const USCity& v);
    };

    Node* root;
    std::size_t node_count;

    //helpers
    int height(Node* n) const;
    void update_height(Node* n);
    int balance_factor(Node* n) const;

    Node* rotate_right(Node* y);
    Node* rotate_left(Node* x);
    Node* rebalance(Node* n);

    Node* insert_node(Node* node, int key, const USCity& value, bool& inserted);

    Node* find_node(Node* node, int key) const;

    void delete_all(Node* n);

    // helper used by max_height()
    int compute_height(const Node* n) const;
};

#endif
