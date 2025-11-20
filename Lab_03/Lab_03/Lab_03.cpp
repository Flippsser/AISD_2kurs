//1. принцип алгоритма Дейкстры
//слайд 82
//2. Какой значение присваивается начальной  и остальным вершинам в начале работы алгоритма Дейкстры ?
//слайд 82
//3. Какова асимптотическая оценка времени работы алгоритма Дейкстры
//слайд 106
#include <iostream>                         
using namespace std;

const int V = 9;                            

void Dijkstra(int GR[V][V], int st);       
void PrintPath(int prev[], int v);         

int main()                                 
{
    system("chcp 1251");

    int GR[V][V] = {
        {0,  7,  10, 0,  0,  0,  0 , 0,  0}, // A
        {7,  0,  0,  0,  0,  9,  27, 0,  0}, // B
        {10, 0,  0,  0,  31, 8,  0,  0,  0}, // C
        {0,  0,  0,  0,  32, 0,  0,  17, 21},// D
        {0,  0,  31, 32, 0,  0,  0,  0,  0}, // E
        {0,  9,  8,  0,  0,  0,  0,  11, 0}, // F
        {0,  27, 0,  0,  0,  0,  0,  0,  15},// G
        {0,  0,  0,  17, 0,  11, 0,  0,  15},// H
        {0,  0,  0,  21, 0,  0,  15, 15, 0}  // I
    };

    char symb[40];                          
    bool pr = false;                        
    cout << "Введите начальную вершину: ";  
    while (!pr) {                           
        cin >> symb;                        
        if (symb[1] == '\0' && symb[0] >= 'A' && symb[0] <= 'I')
            pr = true;                      
        else
            cout << "Неверный ввод. Введите ещё раз: ";
    }

    int letter = (int)symb[0] - 65;        
    Dijkstra(GR, letter);              
    return 0;
}

void Dijkstra(int GR[V][V], int st)
{
    int distance[V], index, u, m = st + 1;
    bool visited[V];
    int prev[V];

    for (int i = 0; i < V; i++) {
        distance[i] = INT_MAX;            
        visited[i] = false;                 
        prev[i] = -1;                      
    }
    distance[st] = 0;                       

    for (int count = 0; count < V - 1; count++) {
        int min = INT_MAX;
        for (int i = 0; i < V; i++)
            if (!visited[i] && distance[i] <= min) {
                min = distance[i];
                index = i;
            }
        u = index;
        visited[u] = true;

        for (int i = 0; i < V; i++)
            if (!visited[i] && GR[u][i] && distance[u] != INT_MAX &&
                distance[u] + GR[u][i] < distance[i]) {
                distance[i] = distance[u] + GR[u][i];
                prev[i] = u;
            }
    }

    cout << "\nДлина маршрутов:\n";
    for (int i = 0; i < V; i++) {
        if (distance[i] != INT_MAX)
            cout << "Из вершины " << (char)(m + 64) << " в " << (char)(i + 65)
            << " : " << distance[i] << endl;
        else
            cout << "Из вершины " << (char)(m + 64) << " в " << (char)(i + 65)
            << " : недоступен" << endl;
    }

    cout << "\nМаршруты:\n";
    for (int i = 0; i < V; i++) {
        if (distance[i] != INT_MAX && i != st) {
            cout << "Путь из " << (char)(m + 64) << " в " << (char)(i + 65) << ": ";
            PrintPath(prev, i);
            cout << endl;
        }
    }
}

void PrintPath(int prev[], int v)
{
    if (prev[v] == -1) {
        cout << (char)(v + 65);            
        return;
    }
    PrintPath(prev, prev[v]);             
    cout << " -> " << (char)(v + 65);      
}
