//1. Суть и принцип работы задачи о рюкзаке
//2. Чем отличается задача "рюкзак без повторений" от "рюкзака с повторениями" ?
//3. Что является входными данными для задачи о рюкзаке ?
//4. Что является результатом решения задачи о рюкзаке ?
//5. Какова временная сложность алгоритма решения задачи о рюкзаке методом ДП ?
//6. Какие реальные задачи можно свести к задаче о рюкзаке ?
//7. Почему жадные алгоритмы не подходят для задачи о рюкзаке ?
#include <iostream>
#include <string>
#include <windows.h>

using namespace std;

struct Item {
    string name;
    int weight;
    int value;
};

const int MAX_ITEMS = 100;
const int MAX_CAPACITY = 1000;

void algoritm(int capacity, Item items[], int numItems, int& maxValue, Item selectedItems[], int& selectedCount) {
    int dp[MAX_ITEMS+1][MAX_CAPACITY+1];

    for (int w = 0; w <= capacity; w++) {
        dp[0][w] = 0;
    }

    for (int i = 1; i <= numItems; i++) {
        for (int w = 0; w <= capacity; w++) {
            if (items[i - 1].weight <= w) {
                int takeValue = dp[i - 1][w - items[i - 1].weight] + items[i - 1].value;
                int skipValue = dp[i - 1][w];
                dp[i][w] = (takeValue > skipValue) ? takeValue : skipValue;
            }
            else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    maxValue = dp[numItems][capacity];

    selectedCount = 0;
    int w = capacity;

    for (int i = numItems; i > 0 && maxValue > 0; i--) {
        if (dp[i][w] != dp[i - 1][w]) {
            selectedItems[selectedCount] = items[i - 1];
            selectedCount++;
            maxValue -= items[i - 1].value;
            w -= items[i - 1].weight;
        }
    }

    maxValue = dp[numItems][capacity];
}

int main() {
    setlocale(LC_ALL, "ru");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int capacity;
    Item items[MAX_ITEMS];
    Item selectedItems[MAX_ITEMS];
    int numItems;
    int selectedCount;
    int maxValue;

    cout << "Введите вместимость рюкзака (N): ";
    cin >> capacity;

    if (capacity <= 0 || capacity > MAX_CAPACITY) {
        cout << "Ошибка: вместимость должна быть от 1 до " << MAX_CAPACITY << endl;
        return 1;
    }

    cout << "Введите количество предметов: ";
    cin >> numItems;

    if (numItems <= 0 || numItems > MAX_ITEMS) {
        cout << "Ошибка: количество предметов должно быть от 1 до " << MAX_ITEMS << endl;
        return 1;
    }

    cout << "\nВведите информацию о предметах:" << endl;
    for (int i = 0; i < numItems; i++) {
        cout << "Предмет " << i + 1 << ":" << endl;

        cout << "  Название: ";
        cin.ignore();
        getline(cin, items[i].name);

        cout << "  Вес: ";
        cin >> items[i].weight;

        if (items[i].weight <= 0) {
            cout << "Ошибка: вес должен быть положительным числом!" << endl;
            return 1;
        }

        cout << "  Стоимость: ";
        cin >> items[i].value;

        if (items[i].value < 0) {
            cout << "Ошибка: стоимость не может быть отрицательной!" << endl;
            return 1;
        }

        cout << endl;
    }

    algoritm(capacity, items, numItems, maxValue, selectedItems, selectedCount);

    cout << "Максимальная стоимость: " << maxValue << endl;

    if (selectedCount == 0) {
        cout << "В рюкзак не поместился ни один предмет." << endl;
    }
    else {
        cout << "\nПредметы в рюкзаке:" << endl;

        int totalWeight = 0;
        for (int i = 0; i < selectedCount; i++) {
            cout << selectedItems[i].name << " (вес: " << selectedItems[i].weight
                << ", стоимость: " << selectedItems[i].value << ")" << endl;
            totalWeight += selectedItems[i].weight;
        }

        cout << "Общий вес: " << totalWeight << " из " << capacity << endl;
    }

    return 0;
}