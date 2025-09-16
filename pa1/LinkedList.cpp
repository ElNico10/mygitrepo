#include "LinkedList.hpp"
#include <cstdlib>
#include <ctime>

template <typename T>
LinkedList<T>::LinkedList() : head(nullptr), size(0) {}

template <typename T>
LinkedList<T>::~LinkedList() {
    clear();
}

template <typename T>
void LinkedList<T>::insert(const T& data) {
    Node<T>* newNode = new Node<T>(data);
    if (!head) {
        head = newNode;
    } else {
        Node<T>* current = head;
        while (current->next) {
            current = current->next;
        }
        current->next = newNode;
    }
    size++;
}

template <typename T>
bool LinkedList<T>::remove(const T& data) {
    if (!head) return false;
    
    if (head->data == data) {
        Node<T>* temp = head;
        head = head->next;
        delete temp;
        size--;
        return true;
    }
    
    Node<T>* current = head;
    while (current->next && !(current->next->data == data)) {
        current = current->next;
    }
    
    if (current->next) {
        Node<T>* temp = current->next;
        current->next = current->next->next;
        delete temp;
        size--;
        return true;
    }
    
    return false;
}

template <typename T>
bool LinkedList<T>::contains(const T& data) const {
    Node<T>* current = head;
    while (current) {
        if (current->data == data) {
            return true;
        }
        current = current->next;
    }
    return false;
}

template <typename T>
int LinkedList<T>::getSize() const {
    return size;
}

template <typename T>
Node<T>* LinkedList<T>::getHead() const {
    return head;
}

template <typename T>
T* LinkedList<T>::getRandom() const {
    if (size == 0) return nullptr;
    
    int index = rand() % size;
    Node<T>* current = head;
    for (int i = 0; i < index && current; i++) {
        current = current->next;
    }
    
    return current ? &(current->data) : nullptr;
}

template <typename T>
void LinkedList<T>::clear() {
    while (head) {
        Node<T>* temp = head;
        head = head->next;
        delete temp;
    }
    size = 0;
}

// Explicit template instantiation
template class LinkedList<Command>;