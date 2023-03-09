#include <Graph.hpp>

Graph::Graph(const std::string &filepath)
{
    bool isLoaded;

    isLoaded = this->loadGraph(filepath);
    if (!isLoaded)
    {
        std::cerr << "Could not load instance from file! Please provide a valid file!";
        this->reset();
    }
}

Graph::~Graph()
{
}

void Graph::performDFS()
{
    int currentNode = 0;

    DFSHelper(currentNode);
    this->performedDFS = true;
}

void Graph::performBFS()
{
    std::queue<int> nodesToVisit;
    int currentNode;

    nodesToVisit.push(0);

    while (!nodesToVisit.empty())
    {
        currentNode = nodesToVisit.front();
        BFS.push_back(currentNode + 1);
        nodesToVisit.pop();

        for (const auto &elem : this->adjacencyList[currentNode])
        {
            if (visitedBFS[elem] == false)
            {
                this->BFSTree.push_back({currentNode, elem});
                visitedBFS[elem] = true;
                nodesToVisit.push(elem);
            }
        }
    }

    this->performedBFS = true;
}

void Graph::performTopologicalSort()
{
}

void Graph::printGraph() const
{
    for (const auto &elem : this->adjacencyList)
    {
        for (const auto &node : elem)
        {
            std::cout << node << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "DFS:\n";
    for (const auto &elem : this->DFS)
    {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
    std::cout << "DFS tree:\n";
    for (const auto &[e1, e2] : this->DFSTree)
    {
        std::cout << "(" << e1 + 1 << ", " << e2 + 1 << ") ";
    }
    std::cout << std::endl;
    std::cout << std::endl;

    std::cout << "BFS:\n";
    for (const auto &elem : this->BFS)
    {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
    std::cout << "BFS tree:\n";
    for (const auto &[e1, e2] : this->BFSTree)
    {
        std::cout << "(" << e1 + 1 << ", " << e2 + 1 << ") ";
    }
}

std::vector<std::vector<int>> Graph::getAdjacencyList()
{
    return this->adjacencyList;
}

void Graph::DFSHelper(const int &currentNode)
{
    visitedDFS[currentNode] = true;
    DFS.push_back(currentNode + 1);

    for (const auto &elem : adjacencyList[currentNode])
    {
        if (visitedDFS[elem] == false)
        {
            this->DFSTree.push_back({currentNode, elem});
            DFSHelper(elem);
        }
    }
}

void Graph::reset()
{
    this->validInstance = false;
    this->n = 0;
    this->m = 0;
    this->performedDFS = false;
    this->performedBFS = false;
    this->isDirected = false;
    this->adjacencyList.clear();
    this->visitedDFS.clear();
    this->visitedBFS.clear();
    this->DFS.clear();
    this->DFSTree.clear();
    this->BFS.clear();
    this->BFSTree.clear();
}

bool Graph::loadGraph(const std::string &filepath)
{
    std::ifstream file;
    std::string line;
    char isDirected;
    int n, m;
    int e1, e2;
    bool loaded = true;

    this->performedBFS = false;
    this->performedDFS = false;

    file.open(filepath, std::ios::in);
    if (file.is_open())
    {
        file >> isDirected;
        switch (isDirected)
        {
        case 'U':
            this->isDirected = false;
            break;
        case 'D':
            this->isDirected = true;
            break;
        default:
            std::cerr << "Unknown flag!!!";
            loaded = false;
        }

        file >> n >> m;
        this->n = n;
        this->m = m;
        this->adjacencyList.resize(n);     // reserves space for nodes in adjacency list
        this->visitedDFS.resize(n, false); // reserves space for nodes visited in DFS
        this->visitedBFS.resize(n, false); // reserves space for nodes visited in BFS

        for (size_t i = 0; i < m; ++i)
        {
            file >> e1 >> e2;
            this->adjacencyList[e1 - 1].push_back(e2 - 1);
            if (!this->isDirected)
            {
                this->adjacencyList[e2 - 1].push_back(e1 - 1);
            }
        }
    }
    else
    {
        std::cerr << "Cannot open file!!!";
        loaded = false;
    }
    file.close();

    return loaded;
}
