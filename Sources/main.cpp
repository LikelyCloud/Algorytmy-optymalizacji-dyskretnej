#include <Graph.hpp>

int main(int argc, char *argv[])
{
    if (argc > 1)
    {
        std::string filepath(argv[1]);

        Graph graph(filepath);
        graph.performDFS();
        graph.performBFS();

        graph.performTopologicalSort();

        // graph.printGraph();
    }
    return 0;
}
