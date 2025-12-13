//1. Что такое жадный алгоритм ?
//2. Что такое энтропия алфавита
//3. Опишите алгоритм построения дерева Хаффмана.
//4. Почему коды Хаффмана называют префиксными ?
//5. Какой принцип лежит в основе оптимизации кода Хаффмана ?
//6. Чем отличается равномерное кодирование(ASCII) от неравномерного кодирования(Хаффман) ?
//7. Как изменится кодировка, если частоты символов изменятся ?
#include <iostream>
#include <string>
#include <map>
#include <queue>

using namespace std;

struct Node {
    char c;
    int freq;
    Node* left;
    Node* right;
};

Node* makeLeaf(char c, int f) {
    Node* n = new Node;
    n->c = c;
    n->freq = f;
    n->left = nullptr;
    n->right = nullptr;
    return n;
}

Node* makeNode(Node* a, Node* b) {
    Node* n = new Node;
    n->c = '\0';
    n->freq = a->freq + b->freq;
    n->left = a;
    n->right = b;
    return n;
}

struct Cmp {
    bool operator()(Node* a, Node* b) {
        return a->freq > b->freq;
    }
};

void build(Node* root, string code, map<char, string>& out) {
    if (!root) return;

    if (!root->left && !root->right) {
        out[root->c] = code;
        return;
    }

    build(root->left, code + "0", out);
    build(root->right, code + "1", out);
}

string decode(Node* root, const string& s) {
    string res;
    Node* cur = root;

    for (char bit : s) {
        if (bit == '0') cur = cur->left;
        else cur = cur->right;

        if (!cur->left && !cur->right) {
            res += cur->c;
            cur = root;
        }
    }
    return res;
}

int main() {
    setlocale(LC_ALL, "ru");

    cout << "Введите строку: ";
    string text;
    getline(cin, text);

    // Частоты
    map<char, int> freq;
    for (char c : text) freq[c]++;

    cout << "\nЧастоты символов:\n";
    for (auto p : freq)
        cout << p.first << " " << p.second << "\n";

    // Построение дерева
    priority_queue<Node*, vector<Node*>, Cmp> pq;

    for (auto p : freq)
        pq.push(makeLeaf(p.first, p.second));

    while (pq.size() > 1) {
        Node* a = pq.top(); pq.pop();
        Node* b = pq.top(); pq.pop();
        pq.push(makeNode(a, b));
    }

    Node* root = pq.top();

    // Коды
    map<char, string> code;
    build(root, "", code);

    cout << "\nКоды Хаффмана:\n";
    for (auto p : code)
        cout << p.first << " " << p.second << "\n";

    // Кодирование
    string encoded;
    for (char c : text) encoded += code[c];

    cout << "\nЗакодированная строка:\n" << encoded << "\n";

    // Декодирование
    string decoded = decode(root, encoded);

    cout << "\nДекодированная строка:\n" << decoded << "\n";

    return 0;
}
