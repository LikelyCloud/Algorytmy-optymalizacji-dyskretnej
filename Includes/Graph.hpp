#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <queue>
#include <fstream>
#include <iostream>

class Graph
{
public:
    Graph(const std::string &filepath);
    ~Graph();

    std::vector<std::vector<int>> getAdjacencyList();
    void performDFS();
    void performBFS();
    void performTopologicalSort();
    void printGraph() const;

private:
    bool validInstance; // true if contains valid graph instance;
    bool performedDFS;  // true if already performed DFS on this graph
    bool performedBFS;  // true if already performed BFS on this graph
    bool isDirected;    // true if graph is directed, false otherwise
    int n;              // number of nodes
    int m;              // number of edges

    std::vector<std::vector<int>> adjacencyList; // adjacencyList[i] <- list of nodes adjacent to node i
    std::vector<bool> visitedDFS;                // true if node already visited (used in DFS algorithm)
    std::vector<bool> visitedBFS;                // true if node already visited (used in BFS algorithm)
    std::vector<int> DFS;                        // nodes in DFS order
    std::vector<std::pair<int, int>> DFSTree;    // edges included in DFS tree
    std::vector<std::pair<int, int>> BFSTree;    // edges included in BFS tree
    std::vector<int> BFS;                        // nodes in BFS order

    void DFSHelper(const int &node);             // helper function in DFS algorithm
    void reset();                                // clears all data about graph instance;
    bool loadGraph(const std::string &filepath); // loads graph instance from file
};

#endif
