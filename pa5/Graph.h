#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <vector>
#include <map>
#include <limits>

const int INF = std::numeric_limits<int>::max();

struct Edge {
    std::string destination;
    int weight;
};

struct QueueNode {
    std::string city;
    int distance;
    
    bool operator>(const QueueNode& other) const {
        return distance > other.distance;
    }
};

class Graph {
private:
    std::map<std::string, std::vector<Edge>> adjList;
    std::vector<std::string> cities;

public:
    void addEdge(const std::string &source, const std::string &dest, int weight);
    std::vector<std::string> getCities() const;
    const std::vector<Edge> &getNeighbors(const std::string &city) const;
    void initializeHospitalNetwork();
    std::map<std::string, int> dijkstraShortestPath(const std::string &start);
    std::map<std::string, std::map<std::string, int>> precomputeAllShortestPaths();
};

#endif