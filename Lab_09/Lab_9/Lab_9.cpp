//1.   полиномиальные задачи\ Недетерминированные полиномиальные задачи 
//2.  Хромосома.Популяция.
//3. Как происходит скрещивание.Виды скрещивания генетического алгоритма
//4. как происходит мутация
//5. Генетический алгоритм
//6. Задача о коммивояжере
//7.  Преимущества генетического алгоритма для коммивояжера ?
//8. Что происходит, если между двумя городами нет ребра
//9. Как влияет размер популяции и количество поколений на работу алгоритма ?
//10. Как меняется количество возможных маршрутов коммивояжёра при увеличении числа городов
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <climits>
#include <chrono>

using namespace std;

const int V = 8;
const int INF = INT_MAX;

int cities[V][V] = {
    { INF, 25, 40, 31, 27, 10, 5, 9 },
    { 5, INF, 17, 30, 25, 15, 20, 10 },
    { 19, 15, INF, 6, 1, 20, 30, 25 },
    { 9, 50, 24, INF, 6, 10, 5, 9 },
    { 22, 8, 7, 10, INF, 15, 20, 10 },
    { 10, 15, 20, 10, 15, INF, 17, 30 },
    { 5, 20, 30, 5, 20, 17, INF, 6 },
    { 9, 10, 25, 9, 10, 30, 6, INF }
};

struct Individual {
    vector<int> path;
    int fitness;
};

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

// Подсчёт длины маршрута
int calcFitness(const vector<int>& path) {
    int total = 0;
    for (int i = 0; i + 1 < path.size(); ++i) {
        int from = path[i];
        int to = path[i + 1];
        int cost = cities[from][to];
        if (cost == INF) return INF;
        total += cost;
    }
    return total;
}

// Генерация случайной особи

Individual randomIndividual() {
    vector<int> path = { 0 };
    vector<int> rest;
    for (int i = 1; i < V; ++i) rest.push_back(i);
    shuffle(rest.begin(), rest.end(), rng);
    path.insert(path.end(), rest.begin(), rest.end());
    path.push_back(0);
    return { path, calcFitness(path) };
}

// Мутация (swap двух городов)
void mutate(Individual& ind) {
    int i = rng() % (V - 1) + 1;
    int j = rng() % (V - 1) + 1;
    if (i != j) swap(ind.path[i], ind.path[j]);
    ind.fitness = calcFitness(ind.path);
}

//crossover
Individual crossoverOX(const Individual& p1, const Individual& p2) {
    int cut1 = rng() % (V - 1) + 1;
    int cut2 = rng() % (V - 1) + 1;
    if (cut1 > cut2) swap(cut1, cut2);

    vector<int> child(V + 1, -1);
    child[0] = 0;
    child[V] = 0;

    vector<bool> used(V, false);
    used[0] = true;

    for (int i = cut1; i <= cut2; ++i) {
        child[i] = p1.path[i];
        used[p1.path[i]] = true;
    }

    int idx = 1;
    for (int i = 1; i < V; ++i) {
        int gene = p2.path[i];
        if (used[gene]) continue;
        while (idx >= cut1 && idx <= cut2) ++idx;
        child[idx++] = gene;
        used[gene] = true;
    }

    return { child, calcFitness(child) };
}

// Турнирный отбор
Individual tournamentSelect(const vector<Individual>& pop, int k = 3) {
    int best = rng() % pop.size();
    for (int i = 1; i < k; ++i) {
        int idx = rng() % pop.size();
        if (pop[idx].fitness < pop[best].fitness) best = idx;
    }
    return pop[best];
}
// Генетический алгоритм

void geneticAlgorithm(int popSize, int pairCount, int generations, double mutationRate) {
    vector<Individual> population;
    for (int i = 0; i < popSize; ++i)
        population.push_back(randomIndividual());

    sort(population.begin(), population.end(),
        [](const Individual& a, const Individual& b) {
            return a.fitness < b.fitness;
        });

    cout << "\nСтартовая популяция:\n";
    for (const auto& ind : population) {
        for (int v : ind.path) cout << v << " ";
        cout << " | длина: " << ind.fitness << "\n";
    }

    for (int gen = 1; gen <= generations; ++gen) {
        vector<Individual> newPop;
        newPop.push_back(population[0]); // элитизм

        for (int i = 0; i < pairCount; ++i) {
            Individual p1 = tournamentSelect(population);
            Individual p2 = tournamentSelect(population);

            Individual c1 = crossoverOX(p1, p2);
            Individual c2 = crossoverOX(p2, p1);

            if ((double)rng() / rng.max() < mutationRate) mutate(c1);
            if ((double)rng() / rng.max() < mutationRate) mutate(c2);

            newPop.push_back(c1);
            newPop.push_back(c2);
        }

        while (newPop.size() < popSize)
            newPop.push_back(randomIndividual());

        population = move(newPop);
        sort(population.begin(), population.end(),
            [](const Individual& a, const Individual& b) {
                return a.fitness < b.fitness;
            });

        cout << "\nПоколение " << gen << ":\n";
        cout << "Лучший маршрут: ";
        for (int v : population[0].path) cout << v << " ";
        cout << "| длина: " << population[0].fitness << "\n";
    }

    cout << "\nНаиболее оптимальный маршрут:\n";
    for (int v : population[0].path) cout << v << " ";
    cout << "| длина: " << population[0].fitness << "\n";
}


int main() {
    setlocale(LC_ALL, "ru");

    int popSize, pairCount, generations;
    double mutationRate;

    cout << "Введите размер популяции: ";
    cin >> popSize;
    cout << "Введите количество пар родителей: ";
    cin >> pairCount;
    cout << "Введите количество поколений: ";
    cin >> generations;
    cout << "Введите вероятность мутации (например, 0.1): ";
    cin >> mutationRate;

    geneticAlgorithm(popSize, pairCount, generations, mutationRate);
    return 0;
}

