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

    std::vector<std::vector<int>> getAdjacencyList(); // adjacency list of graph nodes
    void performDFS();                                // preforms DFS algorithm on the graph
    void performBFS();                                // preforms BFS algorithm on the graph
    void performTopologicalSort();                    // performs topological sort algorithm
    void printGraph() const;                          // prints list of adjacency, DFS order, DFS tree, BFS order, BFS tree, topological order

private:
    enum class State
    {
        NotVisited,
        PartiallyVisited,
        FullyVisited
    };                  // state of node used in topological sort
    bool validInstance; // true if contains valid graph instance;
    bool performedDFS;  // true if already performed DFS on this graph
    bool performedBFS;  // true if already performed BFS on this graph
    bool isDirected;    // true if graph is directed, false otherwise
    bool containsCycle; // true if graph contains cycle (to use after the topological sort)
    int n;              // number of nodes
    int m;              // number of edges

    std::vector<std::vector<int>> adjacencyList; // adjacencyList[i] <- list of nodes adjacent to node i
    std::vector<bool> visitedDFS;                // true if node already visited (used in DFS algorithm)
    std::vector<int> DFS;                        // nodes in DFS order
    std::vector<std::pair<int, int>> DFSTree;    // edges included in DFS tree
    std::vector<bool> visitedBFS;                // true if node already visited (used in BFS algorithm)
    std::vector<int> BFS;                        // nodes in BFS order
    std::vector<std::pair<int, int>> BFSTree;    // edges included in BFS tree
    std::vector<State> topologicalState;         // contains current state of nodes
    std::vector<int> topologicalOrder;           // (reversed - read backwards) contains nodes in topological order

    bool topologicalVisit(const int &node);      // visits one node in topological search
    void DFSHelper(const int &node);             // helper function in DFS algorithm
    void reset();                                // clears all data about graph instance;
    bool loadGraph(const std::string &filepath); // loads graph instance from file
};

#endif
