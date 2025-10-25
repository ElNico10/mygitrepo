#include "HeapPriorityQueue.h"
#include <iostream>

HeapPriorityQueue::HeapPriorityQueue() {
    size = 0;
}

HeapPriorityQueue::~HeapPriorityQueue() {
    // No dynamic memory to clean up
}

//copy constructor
HeapPriorityQueue::HeapPriorityQueue(const HeapPriorityQueue& other) {
    size = other.size;
    for (int i = 0; i < size; i++) {
        heap[i] = other.heap[i];
    }
}

//copy assignment operator
HeapPriorityQueue& HeapPriorityQueue::operator=(const HeapPriorityQueue& other) {
    if (this != &other) {
        size = other.size;
        for (int i = 0; i < size; i++) {
            heap[i] = other.heap[i];
        }
    }
    return *this;
}

void HeapPriorityQueue::enqueue(const string& str, int priority) {
    if (size >= MAX_SIZE) {
        std::cout << "Queue is full. Cannot enqueue more jobs.\n";
        return;
    }
    
    //insert new job at end
    heap[size] = PrinterJob(str, priority);
    size++;
    
    //maintain heap order
    percolateUp(size - 1);
}

void HeapPriorityQueue::printJobs() {
    if (size == 0) {
        std::cout << "No jobs in the queue.\n";
        return;
    }

    std::cout << "Printing jobs in priority order:\n";
    
    //create temporary copy to preserve original heap
    HeapPriorityQueue temp = *this;
    
    while (temp.size > 0) {
        //root has highest priority
        PrinterJob job = temp.heap[0];
        std::cout << job.printString << " (Priority: " << job.priority << ")\n";
        
        //move last element to root and reduce size
        temp.heap[0] = temp.heap[temp.size - 1];
        temp.size--;
        
        //maintain heap order
        if (temp.size > 0) {
            temp.percolateDown(0);
        }
    }
}

void HeapPriorityQueue::percolateUp(int index) {
    if (index == 0) return;
    
    int parentIndex = (index - 1) / 2;
    
    //if current node higher priority than parent, swap
    if (heap[index] < heap[parentIndex]) {
        //swap with parent
        PrinterJob temp = heap[parentIndex];
        heap[parentIndex] = heap[index];
        heap[index] = temp;
        
        percolateUp(parentIndex);
    }
}

void HeapPriorityQueue::percolateDown(int index) {
    int leftChild = 2 * index + 1;
    int rightChild = 2 * index + 2;
    int smallest = index;
    
    //check if left child exists and has higher priority
    if (leftChild < size && heap[leftChild] < heap[smallest]) {
        smallest = leftChild;
    }
    
    //check if right child exists and has higher priority
    if (rightChild < size && heap[rightChild] < heap[smallest]) {
        smallest = rightChild;
    }
    
    //if smallest not current node, swap and continue
    if (smallest != index) {
        PrinterJob temp = heap[index];
        heap[index] = heap[smallest];
        heap[smallest] = temp;
        
        percolateDown(smallest);
    }
}