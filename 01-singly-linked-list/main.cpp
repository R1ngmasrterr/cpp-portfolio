#include <iostream>
#include <limits>
#include <windows.h>

using namespace std;

struct Node {
    double data;
    Node* next;
};

// Добавление элемента в конец списка
void DobavVKonec(Node*& head, Node*& tail, double value) {
    Node* newNode = new Node;
    newNode->data = value;
    newNode->next = nullptr;

    if (head == nullptr) {
        head = newNode;
        tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }
}

// Печать списка
void Napechatat(Node* head) {
    if (head == nullptr) {
        cout << "Список пуст." << endl;
        return;
    }
    Node* tekush = head;
    while (tekush != nullptr) {
        cout << tekush->data << " ";
        tekush = tekush->next;
    }
    cout << endl;
}

// Очистка памяти
void Ochistit(Node*& head) {
    while (head != nullptr) {
        Node* tekush = head;
        head = head->next;
        delete tekush;
    }
}

// Вычисление среднего арифметического первого и последнего элементов
double Srednee(Node* head) {
    if (head == nullptr) {
        cout << "Список пуст, невозможно вычислить среднее." << endl;
        return 0;
    }
    
    double first = head->data;
    Node* tekush = head;
    
    // Идем до последнего элемента
    while (tekush->next != nullptr) {
        tekush = tekush->next;
    }
    double last = tekush->data;
    
    return (first + last) / 2.0;
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");

    cout << "Вариант №6: Написать программу, которая вводит с клавиатуры список\n"
         << "вещественных чисел и ищет среднее арифметическое головного и\n"
         << "концевого элементов списка." << endl;

    Node* head = nullptr;
    Node* tail = nullptr;
    int n;

    cout << "\nВведите количество элементов списка: ";
    while (!(cin >> n) || n < 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Ошибка. Введите неотрицательное целое: ";
    }

    for (int i = 0; i < n; ++i) {
        double znach;
        cout << "Введите элемент " << i + 1 << ": ";
        cin >> znach;
        DobavVKonec(head, tail, znach);
    }

    cout << "\nВведённый список: ";
    Napechatat(head);

    double avg = Srednee(head);
    if (head != nullptr) {
        cout << "Среднее арифметическое первого и последнего элементов: " << avg << endl;
    }

    Ochistit(head);
    return 0;
}
