//1. что такое О большое 6 слайд
//2. описание  алгоритма поиска в глубину
//3. описание алгоритма поиска в ширину
//4. определение неориентированного и ориентированного графа
//5. какие структуры данных использует поиск в глубину\поиск в ширину
#include <iostream>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

const int NODE_COUNT = 10;
// Матрица смежности
int adjacencyMatrix[NODE_COUNT][NODE_COUNT] =
{
  {0,1,0,0,1,0,0,0,0,0}, 
  {1,0,0,0,0,0,1,1,0,0}, 
  {0,0,0,0,0,0,0,1,0,0}, 
  {0,0,0,0,0,1,0,0,1,0}, 
  {1,0,0,0,0,1,0,0,0,0}, 
  {0,0,0,1,1,0,0,0,1,0}, 
  {0,1,0,0,0,0,0,1,0,0}, 
  {0,1,1,0,0,0,1,0,0,0}, 
  {0,0,0,1,0,1,0,0,0,1}, 
  {0,0,0,0,0,0,0,0,1,0}  
};
// Список рёбер
vector<pair<int, int>> edgeList = {
    {1,2}, {1,5}, {2,7}, {2,8}, {3,8}, {4,6}, {4,9}, {5,6}, {6,9}, {7,8}, {9,10}
};
// Список смежности 
vector<vector<int>> adjacencyList = {
    {2,5},    
    {1,7,8},  
    {8},      
    {6,9},    
    {1,6},    
    {4,5,9},  
    {2,8},    
    {2,3,7},  
    {4,6,10}, 
    {9}       
};

void printEdgeList()
{
    cout << "Список рёбер:\n";
    for (auto& e : edgeList)
        cout << "{" << e.first << ", " << e.second << "}\n";
    cout << endl;
}

void printAdjacencyMatrix()
{
    cout << "Матрица смежности:\n";
    for (int i = 0; i < NODE_COUNT; ++i)
    {
        for (int j = 0; j < NODE_COUNT; ++j)
            cout << adjacencyMatrix[i][j] << " ";
        cout << "\n";
    }
    cout << endl;
}

void printAdjacencyList()
{
    cout << "Список смежности:\n";
    for (int i = 0; i < NODE_COUNT; ++i)
    {
        cout << i + 1 << " -> ";
        for (size_t j = 0; j < adjacencyList[i].size(); ++j)
        {
            cout << adjacencyList[i][j];
            if (j + 1 < adjacencyList[i].size()) cout << ", ";
        }
        cout << "\n";
    }
    cout << endl;
}

// Итеративный DFS (использует стек)
void depthFirstSearch(int startNode)
{
    vector<bool> visited(NODE_COUNT, false);
    stack<int> st;
    st.push(startNode);
    visited[startNode] = true;
    bool first = true;

    while (!st.empty())
    {
        int v = st.top();
        st.pop();

        if (!first) cout << " - ";
        cout << v + 1;
        first = false;

        // Добавляем соседей в стек в обратном порядке чтобы соблюдать порядок обхода списка
        for (int i = (int)adjacencyList[v].size() - 1; i >= 0; --i)
        {
            int u = adjacencyList[v][i] - 1;
            if (!visited[u])
            {
                st.push(u);
                visited[u] = true;
            }
        }
    }
    cout << endl;
}

// BFS (использует очередь)
void breadthFirstSearch(int startNode)
{
    vector<bool> visited(NODE_COUNT, false);
    queue<int> q;
    q.push(startNode);
    visited[startNode] = true;
    bool first = true;

    while (!q.empty())
    {
        int v = q.front();
        q.pop();

        if (!first) cout << " - ";
        cout << v + 1;
        first = false;

        for (int u1 : adjacencyList[v])
        {
            int u = u1 - 1;
            if (!visited[u])
            {
                q.push(u);
                visited[u] = true;
            }
        }
    }
    cout << endl;
}

int main()
{
    system("chcp 1251");

    printEdgeList();
    printAdjacencyMatrix();
    printAdjacencyList();

    cout << "Поиск в глубину (DFS). Введите начальную вершину (1-" << NODE_COUNT << "): ";
    int dfsStart;
    if (!(cin >> dfsStart)) return 1;
    if (dfsStart < 1 || dfsStart > NODE_COUNT) return 1;
    cout << "Порядок обхода DFS: ";
    depthFirstSearch(dfsStart - 1);

    cout << "\nПоиск в ширину (BFS). Введите начальную вершину (1-" << NODE_COUNT << "): ";
    int bfsStart;
    if (!(cin >> bfsStart)) return 1;
    if (bfsStart < 1 || bfsStart > NODE_COUNT) return 1;
    cout << "Порядок обхода BFS: ";
    breadthFirstSearch(bfsStart - 1);

    return 0;
}
