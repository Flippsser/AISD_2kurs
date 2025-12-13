//1. Принцип динамического программирования ?
//2. Что такое Мемоизация ?
//3. Опишите принцип работы алгоритма нахождения наибольшей возрастающей подпоследовательности 
//4. Что такое подпоследовательность ?
//5. Что такое  возрастающая подпоследовательность.
//6. Какая сложность у возрастающей подпоследовательности ?
//7. Как можно восстановить саму подпоследовательность, а не только длину ?
#include <iostream>
#include <vector>
#include <algorithm>
#include <locale>

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");

    int n;
    cout << "Введите количество элементов последовательности: ";
    cin >> n;

    if (n <= 0) {
        cout << "Ошибка: количество элементов должно быть положительным" << endl;
        return 1;
    }

    vector<int> arr(n);
    cout << "Введите элементы последовательности: ";

    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    vector<int> len(n, 1);
    vector<int> prev(n, -1);

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (arr[j] < arr[i]) {
                if (len[j] + 1 > len[i]) {
                    len[i] = len[j] + 1;
                    prev[i] = j;
                }

                else if (len[j] + 1 == len[i] && arr[j] < arr[prev[i]]) {
                    prev[i] = j;
                }
            }
        }
    }

    int max_len = 1;
    int last_index = 0;

    for (int i = 0; i < n; i++) {
        if (len[i] > max_len) {
            max_len = len[i];
            last_index = i;
        }

        else if (len[i] == max_len && arr[i] < arr[last_index]) {
            last_index = i;
        }
    }

    vector<int> list;
    int cur = last_index;
    while (cur != -1) {
        list.push_back(arr[cur]);
        cur = prev[cur];
    }
    reverse(list.begin(), list.end());

    cout << max_len << endl;
    for (size_t i = 0; i < list.size(); i++) {
        cout << list[i];
        if (i != list.size() - 1) cout << ", ";
    }
    cout << endl;

    return 0;
}