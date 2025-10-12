#include "AVLMap.h"
#include <algorithm>

//theres a lack of comments because i feel like the code is so self explanatory github copilot is literally autocorrecting this entire comment for me
//it just knows what im trying to say (i hit tab there!) :)

//Nodes!
AVLMap::Node::Node(int k, const USCity& v) : key(k), value(v), left(nullptr), right(nullptr), height(1) { }

AVLMap::AVLMap() : root(nullptr), node_count(0) { }

AVLMap::~AVLMap() {
    delete_all(root);
}

//helpers
int AVLMap::height(Node* n) const {
    return n ? n->height : 0;
}

void AVLMap::update_height(Node* n) {
    if (n) n->height = 1 + std::max(height(n->left), height(n->right));
}

int AVLMap::balance_factor(Node* n) const {
    return n ? (height(n->left) - height(n->right)) : 0;
}

AVLMap::Node* AVLMap::rotate_right(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    //rotation
    x->right = y;
    y->left = T2;
    update_height(y);
    update_height(x);

    return x;
}

AVLMap::Node* AVLMap::rotate_left(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;
    update_height(x);
    update_height(y);

    return y;
}

AVLMap::Node* AVLMap::rebalance(Node* n) {
    update_height(n);
    int bf = balance_factor(n);

    //left heavy
    if (bf > 1) {
        if (balance_factor(n->left) < 0) {
            n->left = rotate_left(n->left);
        }
        return rotate_right(n);
    }
    //right heavy
    if (bf < -1) {
        if (balance_factor(n->right) > 0) {
            n->right = rotate_right(n->right);
        }
        return rotate_left(n);
    }
    return n;
}

AVLMap::Node* AVLMap::insert_node(Node* node, int key, const USCity& value, bool& inserted) {
    if (!node) {
        inserted = true;
        ++node_count;
        return new Node(key, value);
    }

    if (key < node->key) {
        node->left = insert_node(node->left, key, value, inserted);
    } else if (key > node->key) {
        node->right = insert_node(node->right, key, value, inserted);
    } else {
        //update existing
        node->value = value;
        inserted = false;
        return node;
    }

    return rebalance(node);
}

void AVLMap::insert(int key, const USCity& value) {
    bool inserted = false;
    root = insert_node(root, key, value, inserted);
}

AVLMap::Node* AVLMap::find_node(Node* node, int key) const {
    while (node) {
        if (key < node->key) node = node->left;
        else if (key > node->key) node = node->right;
        else return node;
    }
    return nullptr;
}

USCity* AVLMap::find(int key) {
    Node* n = find_node(root, key);
    return n ? &(n->value) : nullptr;
}

const USCity* AVLMap::find(int key) const {
    Node* n = find_node(root, key);
    return n ? &(n->value) : nullptr;
}

std::size_t AVLMap::size() const {
    return node_count;
}

void AVLMap::delete_all(Node* n) {
    if (!n) return;
    delete_all(n->left);
    delete_all(n->right);
    delete n;
}

//debug helper: compute maximum height of tree
int AVLMap::compute_height(const Node* n) const {
    if (!n) return 0;
    int hl = compute_height(n->left);
    int hr = compute_height(n->right);
    return 1 + (hl > hr ? hl : hr);
}

int AVLMap::max_height() const {
    return compute_height(root);
}
