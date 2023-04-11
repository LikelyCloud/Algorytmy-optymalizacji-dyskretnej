#include <Graph.hpp>

Graph::Graph() {}

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
    std::vector<bool> visitedDFS;
    visitedDFS.resize(this->n, false); // reserves space for nodes visited in DFS

    for (size_t i = 0; i < this->n; ++i)
    {
        if (visitedDFS[i] == false)
        {
            DFSHelper(visitedDFS, i);
        }
    }

    this->performedDFS = true;
}

void Graph::performBFS()
{
    std::queue<int> nodesToVisit;
    std::vector<bool> visitedBFS;
    int currentNode;

    visitedBFS.resize(this->n, false); // reserves space for nodes visited in BFS

    for (size_t i = 0; i < this->n; ++i)
    {
        if (visitedBFS[i] == false)
        {
            nodesToVisit.push(i);
            visitedBFS[i] = true;

            while (!nodesToVisit.empty())
            {
                currentNode = nodesToVisit.front();
                BFS.push_back(currentNode + 1);
                nodesToVisit.pop();

                for (const auto &elem : this->adjacencyList[currentNode])
                {
                    if (visitedBFS[elem] == false)
                    {
                        this->BFSTree.push_back({currentNode + 1, elem + 1});
                        visitedBFS[elem] = true;
                        nodesToVisit.push(elem);
                    }
                }
            }
        }
    }

    this->performedBFS = true;
}

void Graph::performTopologicalSort()
{
    std::vector<State> topologicalState;
    topologicalState.resize(this->n, Graph::State::NotVisited);

    for (size_t i = 0; i < this->n; ++i)
    {
        if (topologicalState[i] == State::NotVisited)
        {
            if (topologicalVisit(topologicalState, i) == false)
            {
                this->containsCycle = true;
                return;
            }
        }
    }
    this->containsCycle = false;
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
        std::cout << "(" << e1 << ", " << e2 << ") ";
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
        std::cout << "(" << e1 << ", " << e2 << ") ";
    }

    std::cout << std::endl;
    if (this->containsCycle)
    {
        std::cout << "Graph contains cycle";
    }
    else
    {
        std::cout << "Graph does not contain cycle";

        std::cout << std::endl;

        if (this->n <= 200)
        {
            std::cout << "Topological sort:\n";
            for (auto it = this->topologicalOrder.rbegin(); it != this->topologicalOrder.rend(); it++)
            {
                std::cout << *it << " ";
            }
            std::cout << std::endl;
        }
    }
}

void Graph::performKosaraju()
{
    std::vector<std::vector<int>> transposedGraph; // adjacency list of transposed original graph
    std::stack<int> visitedNodeStack;
    std::vector<bool> visitedNodes;
    std::vector<std::vector<int>> stronglyConnectedComponents;
    std::vector<int> currentComponent;
    int sscCounter = 0;
    int topNode;

    transposedGraph.resize(this->n);
    visitedNodes.resize(this->n, false);

    // transposes original graph
    for (size_t i = 0; i < this->n; ++i)
    {
        for (const auto &elem : this->adjacencyList[i])
        {
            transposedGraph[elem].push_back(i);
        }
    }

    for (size_t i = 0; i < this->n; ++i)
    {
        if (visitedNodes[i] == false)
        {
            KosarajuDFS(visitedNodes, visitedNodeStack, i);
        }
    }

    std::fill(visitedNodes.begin(), visitedNodes.end(), false);

    while (!visitedNodeStack.empty())
    {
        topNode = visitedNodeStack.top();
        visitedNodeStack.pop();

        if (visitedNodes[topNode] == false)
        {
            ++sscCounter;
            currentComponent = {topNode};
            KosarajuFindSCC(transposedGraph, visitedNodes, currentComponent, topNode);
            stronglyConnectedComponents.push_back(currentComponent);
        }
    }
    std::cout << "Kosaraju-scc: " << sscCounter << std::endl;
    for (const auto &elem : stronglyConnectedComponents)
    {
        std::cout << elem.size() << " ";
    }
    std::cout << std::endl;
    if (this->n <= 200)
    {
        for (const auto &elem : stronglyConnectedComponents)
        {
            for (const auto val : elem)
            {
                std::cout << val + 1 << " ";
            }
            std::cout << std::endl
                      << std::endl;
        }
    }
}

void Graph::performTarjan()
{
    std::vector<int> tarjanNodeId;
    std::vector<int> tarjanNodeLow;
    std::vector<bool> tarjanNodeOnStack;
    std::stack<int> tarjanNodeStack;
    std::map<int, std::vector<int>> stronglyConnectedComponents;

    int nodeIdCounter = 0;
    int sccCounter = 0;

    tarjanNodeId.resize(this->n, -1);         // mark all nodes as unvisited
    tarjanNodeLow.resize(this->n, 0);         // set 0 as default node low (must and will be changed)
    tarjanNodeOnStack.resize(this->n, false); // no nodes on the stack at the beginning

    for (size_t node = 0; node < this->n; ++node)
    {
        if (tarjanNodeId[node] == -1)
        {
            visitTarjan(node, nodeIdCounter, sccCounter, tarjanNodeId, tarjanNodeLow, tarjanNodeOnStack, tarjanNodeStack);
        }
    }

    for (size_t node = 0; node < this->n; ++node)
    {
        stronglyConnectedComponents[tarjanNodeLow[node]].push_back(node);
    }

    std::cout << "Tarjan-scc: " << sccCounter << std::endl;
    for (const auto &[key, value] : stronglyConnectedComponents)
    {
        std::cout << value.size() << " ";
    }
    std::cout << std::endl;

    /*for (const auto &[key, value] : stronglyConnectedComponents)
    {
        std::cout << "Key:" << key << std::endl;
        for (const auto &elem : value)
        {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
        std::cout << "Value:" << value.size() << " ";
        std::cout << std::endl;
        std::cout << std::endl;
    }*/
}

std::tuple<bool, std::vector<int>, std::vector<int>> Graph::bipartite()
{
    std::vector<Color> nodeColor;
    std::queue<int> nodesToVisit;
    std::vector<int> nodeSetOne;
    std::vector<int> nodeSetTwo;
    int currentNode;

    nodeColor.resize(this->n, Color::Uncolored);

    for (size_t i = 0; i < this->n; ++i)
    {
        if (nodeColor[i] == Color::Uncolored)
        {
            nodeColor[i] = Color::Blue;
            nodesToVisit.push(i);
            nodeSetOne.push_back(i);

            while (!nodesToVisit.empty())
            {
                currentNode = nodesToVisit.front();
                nodesToVisit.pop();

                for (const auto &elem : this->adjacencyList[currentNode])
                {
                    if (nodeColor[elem] == nodeColor[currentNode])
                    {
                        return {false, {}, {}};
                    }
                    else if (nodeColor[elem] == Color::Uncolored)
                    {
                        nodesToVisit.push(elem);
                        nodeColor[elem] = this->alterateColor(nodeColor[currentNode]);
                        switch (nodeColor[elem])
                        {
                        case Color::Blue:
                            nodeSetOne.push_back(elem);
                            break;
                        case Color::Red:
                            nodeSetTwo.push_back(elem);
                        case Color::Uncolored: // should never happen !!!
                            break;
                        }
                    }
                }
            }
        }
    }

    return {true, nodeSetOne, nodeSetTwo};
}

int Graph::getSize() const
{
    return this->n;
}

std::vector<std::vector<int>> Graph::getAdjacencyList()
{
    return this->adjacencyList;
}

bool Graph::topologicalVisit(std::vector<State> &topologicalState, const int &node)
{
    if (topologicalState[node] == State::PartiallyVisited)
    {
        return false;
    }
    else if (topologicalState[node] == State::FullyVisited)
    {
        return true;
    }

    topologicalState[node] = State::PartiallyVisited;
    for (const auto &elem : this->adjacencyList[node])
    {
        if (topologicalVisit(topologicalState, elem) == false)
        {
            return false;
        }
    }
    topologicalState[node] = State::FullyVisited;
    this->topologicalOrder.push_back(node + 1);
    return true;
}

void Graph::DFSHelper(std::vector<bool> &visitedDFS, const int &currentNode)
{
    visitedDFS[currentNode] = true;
    DFS.push_back(currentNode + 1);

    for (const auto &elem : adjacencyList[currentNode])
    {
        if (visitedDFS[elem] == false)
        {
            this->DFSTree.push_back({currentNode + 1, elem + 1});
            DFSHelper(visitedDFS, elem);
        }
    }
    // DFS.push_back(currentNode + 1); (kiedy uznawać wierzchołek za odwiedzony???)
}

void Graph::reset()
{
    this->validInstance = false;
    this->n = 0;
    this->m = 0;
    this->performedDFS = false;
    this->performedBFS = false;
    this->isDirected = false;
    this->containsCycle = false;
    this->adjacencyList.clear();
    this->DFS.clear();
    this->DFSTree.clear();
    this->BFS.clear();
    this->BFSTree.clear();
}

bool Graph::loadGraph()
{
    char isDirected;
    int n, m;
    int e1, e2;
    bool loaded = true;

    std::cin >> isDirected;
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
    // ################################ DELETE
    this->isDirected = false;

    std::cin >> n >> m;
    this->n = n;
    this->m = m;
    this->adjacencyList.resize(n); // reserves space for nodes in adjacency list

    for (size_t i = 0; i < m; ++i)
    {
        std::cin >> e1 >> e2;
        this->adjacencyList[e1 - 1].push_back(e2 - 1);
        if (!this->isDirected)
        {
            this->adjacencyList[e2 - 1].push_back(e1 - 1);
        }
    }
    return loaded;
}

bool Graph::loadGraph(const std::string filepath)
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
        // ################################ DELETE
        // this->isDirected = false;

        file >> n >> m;
        this->n = n;
        this->m = m;
        this->adjacencyList.resize(n); // reserves space for nodes in adjacency list

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

Graph::Color Graph::alterateColor(const Color &color)
{
    switch (color)
    {
    case Color::Red:
        return Color::Blue;
    case Color::Blue:
        return Color::Red;
    case Color::Uncolored: // should not happen !!!
        return Color::Uncolored;
    }
}

void Graph::visitTarjan(const int node, int nodeIdCounter, int &sccCounter, std::vector<int> &tarjanNodeId, std::vector<int> &tarjanNodeLow, std::vector<bool> &tarjanNodeOnStack, std::stack<int> &tarjanNodeStack)
{
    int stackTop;

    tarjanNodeStack.push(node);
    tarjanNodeOnStack[node] = true;
    tarjanNodeId[node] = nodeIdCounter;
    tarjanNodeLow[node] = nodeIdCounter;
    nodeIdCounter++;

    for (const auto &neighbour : this->adjacencyList[node])
    {
        if (tarjanNodeId[neighbour] == -1)
        {
            visitTarjan(neighbour, nodeIdCounter, sccCounter, tarjanNodeId, tarjanNodeLow, tarjanNodeOnStack, tarjanNodeStack);
        }
        if (tarjanNodeOnStack[neighbour])
        {
            tarjanNodeLow[node] = std::min(tarjanNodeLow[node], tarjanNodeLow[neighbour]);
        }
    }

    if (tarjanNodeId[node] == tarjanNodeLow[node])
    {
        while (!tarjanNodeStack.empty())
        {
            stackTop = tarjanNodeStack.top();
            tarjanNodeStack.pop();
            tarjanNodeOnStack[stackTop] = false;
            tarjanNodeLow[stackTop] = tarjanNodeId[node];
            if (stackTop == node)
            {
                break;
            }
        }
        ++sccCounter;
    }
}

void Graph::KosarajuDFS(std::vector<bool> &visited, std::stack<int> &visitedNodeStack, const int node)
{
    visited[node] = true;

    for (const auto &elem : this->adjacencyList[node])
    {
        if (visited[elem] == false)
        {
            KosarajuDFS(visited, visitedNodeStack, elem);
        }
    }
    visitedNodeStack.push(node);
}

void Graph::KosarajuFindSCC(std::vector<std::vector<int>> &transposedGraph, std::vector<bool> &visited, std::vector<int> &component, const int node)
{
    visited[node] = true;

    for (const auto &elem : transposedGraph[node])
    {
        if (visited[elem] == false)
        {
            component.push_back(elem);
            KosarajuFindSCC(transposedGraph, visited, component, elem);
        }
    }
}

void Graph::KosarajuDFSIter(std::vector<bool> &visited, std::stack<int> &visitedNodeStack, const int node)
{
    std::vector<bool> onStack(this->n, false); // onStack[i] true if i is on visitedNodeStack
    std::vector<int> stackSize(this->n, -1);   // stackSize[i] == size of stack after popping i

    std::stack<int> dfsStack;
    int stackTop;

    dfsStack.push(node);

    while (!dfsStack.empty())
    {
        stackTop = dfsStack.top();
        dfsStack.pop();
        stackSize[stackTop] = dfsStack.size();

        visited[stackTop] = true;
        for (const auto elem : this->adjacencyList[stackTop])
        {
            if (visited[elem] == false)
            {
                dfsStack.push(elem);
            }
        }

        /*for (size_t i = 0; i < this->n; ++i)
        {
            if (!onStack[i] && stackSize[i] == dfsStack.size())
            {
                onStack[i] = true;
                visitedNodeStack.push(i);
            }
        }*/
        visitedNodeStack.push(stackTop);
    }
}

void Graph::KosarajuFindSCCIter(std::vector<std::vector<int>> &transposedGraph, std::vector<bool> &visited, std::vector<int> &component, const int node)
{
    std::stack<int> dfsStack;
    int stackTop;

    dfsStack.push(node);

    while (!dfsStack.empty())
    {
        stackTop = dfsStack.top();
        dfsStack.pop();
        visited[stackTop] = true;
        for (const auto elem : transposedGraph[stackTop])
        {
            if (visited[elem] == false)
            {
                component.push_back(elem);
                dfsStack.push(elem);
            }
        }
    }
}
