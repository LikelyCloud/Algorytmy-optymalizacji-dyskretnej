#include <Graph.hpp>

int main(int argc, char *argv[])
{
    if (argc > 1)
    {
        std::string filepath(argv[1]);

        Graph graph(filepath);
        // graph.performTarjan();
        auto [a, b, c] = graph.bipartite();
        std::cout << a << std::endl;

        std::cout << "Set 1:\n";
        for (const auto &elem : b)
        {
            std::cout << elem << " ";
        }

        std::cout << "\n\nSet 3:\n";
        for (const auto &elem : c)
        {
            std::cout << elem << " ";
        }

        //  graph.performDFS();
        //  graph.performBFS();

        // graph.performTopologicalSort();

        // graph.printGraph();
    }
    return 0;
}
