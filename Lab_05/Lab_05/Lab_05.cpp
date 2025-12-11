//Что такое остовное связное дерево ?
//Что такое минимальное остовное дерево графа ?
//В чём основное различие между алгоритмами Прима и Краскала при построении минимального остовного дерева ?
#include <iostream>
#include <climits> 
using namespace std;

const int N = 8, M = 16;

int graph[N][N] = {
    {INT_MAX, 2, INT_MAX, 8, 2, INT_MAX, INT_MAX, INT_MAX},
    {2, INT_MAX, 3, 10, 5, INT_MAX, INT_MAX, INT_MAX},
    {INT_MAX, 3, INT_MAX, INT_MAX, 12, INT_MAX, INT_MAX, 7},
    {8, 10, INT_MAX, INT_MAX, 14, 3, 1, INT_MAX},
    {2, 5, 12, 14, INT_MAX, 11, 4, 8},
    {INT_MAX, INT_MAX, INT_MAX, 3, 11, INT_MAX, 6, INT_MAX},
    {INT_MAX, INT_MAX, INT_MAX, 1, 4, 6, INT_MAX, 9},
    {INT_MAX, INT_MAX, 7, INT_MAX, 8, INT_MAX, 9, INT_MAX}
};

void PrimaAlgorithm(int start) {
    int countEdges = 0;
    int totalWeight = 0;
    bool visited[N] = { false };
    visited[start] = true;
    int x, y;
    cout << "Алгоритм Прима: " << endl;
    cout << "Ребро \tВес" << endl;
    while (countEdges < N - 1)
    {
        int min = INT_MAX;
        x = 0;
        y = 0;
        for (int i = 0; i < N; i++) {
            if (visited[i]) {
                for (int j = 0; j < N; j++) {
                    if (!visited[j] && graph[i][j] != INT_MAX) {
                        if (graph[i][j] < min) {
                            min = graph[i][j];
                            x = i;
                            y = j;
                        }
                    }
                }
            }
        }
        cout << x + 1 << " - " << y + 1 << '\t' << graph[x][y] << endl;
        totalWeight += graph[x][y];
        visited[y] = true;
        countEdges++;
    }
    cout << "Общий вес остовного дерева: " << totalWeight << endl;
}

struct Edges
{
    int x, y, weight;
};

Edges edges[N * (N - 1) / 2];
int nodes[N];

int findRoot(int n) {
    if (nodes[n] < 0) {
        return n;
    }
    return nodes[n] = findRoot(nodes[n]);
}

void BubbleSort(Edges edges[], int countEdges) {
    for (int i = 0; i < countEdges - 1; i++) {
        for (int j = 0; j < countEdges - i - 1; j++) {
            if (edges[j].weight > edges[j + 1].weight) {
                Edges temp = edges[j];
                edges[j] = edges[j + 1];
                edges[j + 1] = temp;
            }
        }
    }
}

void KraskalAlgorithm() {
    int edgeCount = 0;
    int totalWeight = 0;
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            if (graph[i][j] != INT_MAX) {
                edges[edgeCount].x = i;
                edges[edgeCount].y = j;
                edges[edgeCount].weight = graph[i][j];
                edgeCount++;
            }
        }
    }

    for (int i = 0; i < N; i++) {
        nodes[i] = -1;
    }

    BubbleSort(edges, edgeCount);
    cout << "Алгоритм Краскала: " << endl;
    cout << "Ребро \tВес" << endl;

    int countEdges = 0;
    for (int i = 0; i < edgeCount && countEdges < N - 1; i++) {
        int u = edges[i].x;
        int v = edges[i].y;
        int c1 = findRoot(u);
        int c2 = findRoot(v);
        if (c1 != c2) {
            cout << u + 1 << " - " << v + 1 << "\t" << edges[i].weight << endl;
            nodes[c1] = c2;
            totalWeight += edges[i].weight;
            countEdges++;
        }
    }
    cout << "Общий вес остовного дерева: " << totalWeight << endl;
}

int main() {
    system("chcp 1251");
    int start;
    cout << "Введите стартовую вершину: ";
    cin >> start;
    if (start < 1 || start > 8) {
        cout << "Вершина введена неверно" << endl;
        return 1;
    }
    PrimaAlgorithm(start - 1);
    cout << endl;
    KraskalAlgorithm();
    cout << "Цикломатическое число: " << M - N + 1 << endl;
    return 0;
}