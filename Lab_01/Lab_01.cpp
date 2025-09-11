#include <iostream>

using namespace std;

//1. Что содержит рекурсивная функция ? Слайд 7
//2. Что такое рекурсия ? Слайд 3
//3. Что такое базовый случай ? Слайд 9
//4. Правила Ханойской башни.Слайд 13
void hanoi(int N, int from, int to, int dop) {
    if (N == 1) {
        cout << "Переместить диск 1 с " << from << " на " << to << " стержень\n";
        return;
    }
    hanoi(N - 1, from, dop, to);
    cout << "Переместить диск " << N << " с " << from << " на " << to << " стержень\n";
    hanoi(N - 1, dop, to, from);
}

int main() {
    system("chcp 1251");
    int N, from, to;
    cout << "Введите количество дисков (N): ";
    cin >> N;
    cout << "Введите номер начального стержня (от 1 до 3): ";
    cin >> from;
    cout << "Введите номер конечного стержня (от 1 до 3): ";
    cin >> to;

    if (from < 1 || from > 3 || to < 1 || to > 3 || from == to) {
        cout << "Неверный ввод. Стержни должны быть от 1 до 3 и не совпадать.\n";
        return 1;
    }

    int dop = 6 - from - to; 
    cout << "\nПоследовательность действий:\n";
    hanoi(N, from, to, dop);

    return 0;
}
