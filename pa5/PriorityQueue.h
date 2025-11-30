#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include <vector>
#include <string>

struct Patient {
    std::string name;
    int severity;
    std::string originalCity;
    
    Patient(const std::string& n, int s, const std::string& city) 
        : name(n), severity(s), originalCity(city) {}
};

class PriorityQueue {
private:
    std::vector<Patient> heap;

    void heapifyUp(int index);
    void heapifyDown(int index);
    int parent(int index) { return (index - 1) / 2; }
    int leftChild(int index) { return 2 * index + 1; }
    int rightChild(int index) { return 2 * index + 2; }

public:
    void insert(const Patient& patient);
    Patient extractMax();
    Patient peekMax() const;
    bool isEmpty() const;
    size_t size() const;
    void merge(PriorityQueue& other);
    const std::vector<Patient>& getPatients() const { return heap; }
};

#endif