#include "Graph.h"
#include <queue>
#include <algorithm>
#include <functional>
#include <iostream>
#include <set>

using namespace std;

void Graph::addEdge(const string &source, const string &dest, int weight) {
    adjList[source].push_back({dest, weight});
    adjList[dest].push_back({source, weight});

    if (find(cities.begin(), cities.end(), source) == cities.end()) {
        cities.push_back(source);
    }
    if (find(cities.begin(), cities.end(), dest) == cities.end()) {
        cities.push_back(dest);
    }
}

vector<string> Graph::getCities() const {
    return cities;
}

const vector<Edge> &Graph::getNeighbors(const string &city) const {
    static const vector<Edge> empty;
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

// EXACT MA3 Dijkstra Implementation
map<string, int> Graph::dijkstraShortestPath(const string &start) {
    map<string, int> distances;
    priority_queue<QueueNode, vector<QueueNode>, greater<QueueNode>> minHeap;
    set<string> visited;

    // Initialize all distances to infinity
    for (const string &city : cities) {
        distances[city] = INF;
    }
    
    // Set starting node distance to 0 and add to priority queue
    distances[start] = 0;
    minHeap.push({start, 0});

    while (!minHeap.empty()) {
        // Get the city with the smallest distance
        QueueNode current = minHeap.top();
        minHeap.pop();
        
        string currentCity = current.city;
        
        // If we've already processed this city, skip it
        if (visited.find(currentCity) != visited.end()) {
            continue;
        }
        
        // Mark as visited
        visited.insert(currentCity);
        
        // Check all neighbors of the current city
        for (const Edge &edge : getNeighbors(currentCity)) {
            string neighbor = edge.destination;
            int newDistance = distances[currentCity] + edge.weight;
            
            // If we found a shorter path to the neighbor
            if (newDistance < distances[neighbor]) {
                distances[neighbor] = newDistance;
                minHeap.push({neighbor, newDistance});
            }
        }
    }

    return distances;
}

map<string, map<string, int>> Graph::precomputeAllShortestPaths() {
    map<string, map<string, int>> allPaths;
    for (const string& city : cities) {
        allPaths[city] = dijkstraShortestPath(city);
    }
    return allPaths;
}