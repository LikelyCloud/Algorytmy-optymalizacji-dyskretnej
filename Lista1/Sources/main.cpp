#include <Graph.hpp>

int main(int argc, char *argv[])
{
    Graph graph;

    if (argc > 1)
    {
        std::string filepath(argv[1]);
        graph.loadGraph(filepath);
    }
    else
    {
        graph.loadGraph();
    }
    // graph.performTopologicalSort();
    graph.performDFS();
    graph.printGraph();
    // graph.performKosaraju();
    // auto start = std::chrono::high_resolution_clock::now();
    //  graph.performTarjan();
    // graph.performKosaraju();
    // auto stop = std::chrono::high_resolution_clock::now();
    // auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    // std::cout << duration.count() << "ms\n";

    // const auto [v1, v2, v3] = graph.bipartite();
    // if (v1)
    // {
    //     std::cout << "Graph is bipartite";
    //     if (graph.getSize() <= 200)
    //     {
    //         std::cout << "\nV1: ";
    //         for (const auto elem : v2)
    //         {
    //             std::cout << elem << " ";
    //         }
    //         std::cout << "\nV2: ";
    //         for (const auto elem : v3)
    //         {
    //             std::cout << elem << " ";
    //         }
    //     }
    // }
    // else
    // {
    //     std::cout << "Graph is not biparitite";
    // }

    return 0;
}
