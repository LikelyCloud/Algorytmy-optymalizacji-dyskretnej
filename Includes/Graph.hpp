#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <map>
#include <stack>
#include <vector>
#include <queue>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <chrono>

class Graph
{
public:
    Graph();
    Graph(const std::string &filepath);
    ~Graph();

    bool loadGraph();                                                 // loads graph instance from command line
    bool loadGraph(const std::string filepath);                       // loads graph instance from file
    std::vector<std::vector<int>> getAdjacencyList();                 // adjacency list of graph nodes
    void performDFS();                                                // preforms DFS algorithm on the graph
    void performBFS();                                                // preforms BFS algorithm on the graph
    void performTopologicalSort();                                    // performs topological sort algorithm
    void printGraph() const;                                          // prints list of adjacency, DFS order, DFS tree, BFS order, BFS tree, topological order
    void performKosaraju();                                           // performs Kosaraju algorithm to find SCC
    void performTarjan();                                             // performs Tarjan's algorithm to find SCC
    std::tuple<bool, std::vector<int>, std::vector<int>> bipartite(); // checks if graph is bipartite and if so returns two sets of nodes (assuming graph is not directed)
    int getSize() const;

private:
    enum class State
    {
        NotVisited,
        PartiallyVisited,
        FullyVisited
    }; // state of node used in topological sort
    enum class Color
    {
        Uncolored,
        Red,
        Blue
    };                  // color of node used in coloring to bipartite
    bool validInstance; // true if contains valid graph instance;
    bool performedDFS;  // true if already performed DFS on this graph
    bool performedBFS;  // true if already performed BFS on this graph
    bool isDirected;    // true if graph is directed, false otherwise
    bool containsCycle; // true if graph contains cycle (to use after the topological sort)
    int n;              // number of nodes
    int m;              // number of edges

    std::vector<std::vector<int>> adjacencyList; // adjacencyList[i] <- list of nodes adjacent to node i
    std::vector<int> DFS;                        // nodes in DFS order
    std::vector<std::pair<int, int>> DFSTree;    // edges included in DFS tree
    std::vector<int> BFS;                        // nodes in BFS order
    std::vector<std::pair<int, int>> BFSTree;    // edges included in BFS tree
    std::vector<int> topologicalOrder;           // (reversed - read backwards) contains nodes in topological order

    bool topologicalVisit(std::vector<Graph::State> &topologicalState, const int &node); // visits one node in topological search
    void DFSHelper(std::vector<bool> &visited, const int &node);                         // helper function in DFS algorithm
    void reset();                                                                        // clears all data about graph instance;
    Color alterateColor(const Color &color);                                             // alterateColor(red) = blue | alterateColor(blue) = red

    void visitTarjan(const int node, int nodeIdCounter, int &sccCounter, std::vector<int> &id, std::vector<int> &low, std::vector<bool> &onStack, std::stack<int> &nodeStack); // DFS visit method modified for Tarjan's SCC algorithm

    void KosarajuDFS(std::vector<bool> &visited, std::stack<int> &visitedNodeStack, const int node);
    void KosarajuFindSCC(std::vector<std::vector<int>> &transposedGraph, std::vector<bool> &visited, std::vector<int> &component, const int node);

    void KosarajuDFSIter(std::vector<bool> &visited, std::stack<int> &visitedNodeStack, const int node);
    void KosarajuFindSCCIter(std::vector<std::vector<int>> &transposedGraph, std::vector<bool> &visited, std::vector<int> &component, const int node);
};

#endif
