#include "PriorityQueue.h"
#include <algorithm>
#include <iostream>

void PriorityQueue::heapifyUp(int index) {
    while (index > 0 && heap[parent(index)].severity < heap[index].severity) {
        std::swap(heap[parent(index)], heap[index]);
        index = parent(index);
    }
}

void PriorityQueue::heapifyDown(int index) {
    int largest = index;
    int left = leftChild(index);
    int right = rightChild(index);
    
    if (left < static_cast<int>(heap.size()) && heap[left].severity > heap[largest].severity) {
        largest = left;
    }
    
    if (right < static_cast<int>(heap.size()) && heap[right].severity > heap[largest].severity) {
        largest = right;
    }
    
    if (largest != index) {
        std::swap(heap[index], heap[largest]);
        heapifyDown(largest);
    }
}

void PriorityQueue::insert(const Patient& patient) {
    heap.push_back(patient);
    heapifyUp(heap.size() - 1);
}

Patient PriorityQueue::extractMax() {
    if (heap.empty()) {
        throw std::runtime_error("Cannot extract from empty priority queue");
    }
    
    Patient maxPatient = heap[0];
    heap[0] = heap.back();
    heap.pop_back();
    
    if (!heap.empty()) {
        heapifyDown(0);
    }
    
    return maxPatient;
}

Patient PriorityQueue::peekMax() const {
    if (heap.empty()) {
        throw std::runtime_error("Cannot peek empty priority queue");
    }
    return heap[0];
}

bool PriorityQueue::isEmpty() const {
    return heap.empty();
}

size_t PriorityQueue::size() const {
    return heap.size();
}

void PriorityQueue::merge(PriorityQueue& other) {
    // Simple O(n) merge - insert all elements from other queue
    // Store the patients in a temporary vector since inserting will modify the heap
    std::vector<Patient> otherPatients = other.getPatients();
    
    for (const Patient& patient : otherPatients) {
        insert(patient);
    }
    
    // Clear the other queue by creating a new empty one
    other = PriorityQueue();
}