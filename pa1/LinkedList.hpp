#pragma once
#define LINKEDLIST_H

#include "Command.hpp"

template <typename T>
class Node {
public:
    T data;
    Node<T>* next;
    
    Node(const T& data) : data(data), next(nullptr) {}
};

template <typename T>
class LinkedList {
private:
    Node<T>* head;
    int size;

public:
    LinkedList();
    ~LinkedList();
    
    void insert(const T& data);
    bool remove(const T& data);
    bool contains(const T& data) const;
    int getSize() const;
    Node<T>* getHead() const;
    
    // Additional utility methods
    T* getRandom() const;
    void clear();
};