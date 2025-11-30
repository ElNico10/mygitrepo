#include "Graph.h"
#include <queue>
#include <algorithm>
#include <functional>
#include <iostream>

void Graph::addEdge(const std::string &source, const std::string &dest, int weight) {
    adjList[source].push_back({dest, weight});
    adjList[dest].push_back({source, weight});

    if (std::find(cities.begin(), cities.end(), source) == cities.end()) {
        cities.push_back(source);
    }
    if (std::find(cities.begin(), cities.end(), dest) == cities.end()) {
        cities.push_back(dest);
    }
}

std::vector<std::string> Graph::getCities() const {
    return cities;
}

const std::vector<Edge> &Graph::getNeighbors(const std::string &city) const {
    static const std::vector<Edge> empty;
    auto it = adjList.find(city);
    if (it != adjList.end()) {
        return it->second;
    }
    return empty;
}

void Graph::initializeHospitalNetwork() {
    // Add all cities and connections based on the specification
    addEdge("Pullman", "Moscow", 8);
    addEdge("Pullman", "Colfax", 17);
    addEdge("Pullman", "Lewiston", 30);
    addEdge("Moscow", "Lewiston", 32);
    addEdge("Moscow", "Spokane", 85);
    addEdge("Colfax", "Spokane", 50);
}

std::map<std::string, int> Graph::dijkstraShortestPath(const std::string &start) {
    std::map<std::string, int> distances;
    std::priority_queue<QueueNode, std::vector<QueueNode>, std::greater<QueueNode>> minHeap;
    std::map<std::string, bool> visited;

    for (const std::string &city : cities) {
        distances[city] = INF;
    }
    
    distances[start] = 0;
    minHeap.push({start, 0});

    while (!minHeap.empty()) {
        QueueNode current = minHeap.top();
        minHeap.pop();
        
        std::string currentCity = current.city;
        
        if (visited[currentCity]) {
            continue;
        }
        
        visited[currentCity] = true;
        
        for (const Edge &edge : getNeighbors(currentCity)) {
            std::string neighbor = edge.destination;
            int newDistance = distances[currentCity] + edge.weight;
            
            if (newDistance < distances[neighbor]) {
                distances[neighbor] = newDistance;
                minHeap.push({neighbor, newDistance});
            }
        }
    }

    return distances;
}

std::map<std::string, std::map<std::string, int>> Graph::precomputeAllShortestPaths() {
    std::map<std::string, std::map<std::string, int>> allPaths;
    for (const std::string& city : cities) {
        allPaths[city] = dijkstraShortestPath(city);
    }
    return allPaths;
}