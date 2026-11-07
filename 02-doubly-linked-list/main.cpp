#define NOMINMAX
#include <iostream>
#include <limits>
#include <windows.h>

using namespace std;

struct Node {
    int data;
    Node* next;
    Node* pred;
};

// Добавление элемента в конец списка
void DobavVKonec(Node*& head, Node*& tail, int value) {
    Node* newNode = new Node;
    newNode->data = value;
    newNode->next = nullptr;
    newNode->pred = tail;

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
void Ochistit(Node*& head, Node*& tail) {
    while (head != nullptr) {
        Node* tekush = head;
        head = head->next;
        delete tekush;
    }
    tail = nullptr;
}

// Поиск узла с минимальным значением
Node* NaytiMinimalny(Node* head) {
    if (head == nullptr) {
        return nullptr;
    }
    Node* minNode = head;
    Node* tekush = head->next;
    while (tekush != nullptr) {
        if (tekush->data < minNode->data) {
            minNode = tekush;
        }
        tekush = tekush->next;
    }
    return minNode;
}

// Добавление элемента после минимального
void DobavPosleMinimalnogo(Node*& head, Node*& tail, int value) {
    if (head == nullptr) {
        cout << "Список пуст, невозможно найти минимальный элемент." << endl;
        return;
    }
    Node* minNode = NaytiMinimalny(head);
    cout << "Минимальное значение в информационном поле: " << minNode->data << endl;

    Node* newNode = new Node;
    newNode->data = value;
    newNode->next = minNode->next;
    newNode->pred = minNode;

    if (minNode->next != nullptr) {
        minNode->next->pred = newNode;
    } else {
        tail = newNode; // Если минимальный был хвостом
    }
    minNode->next = newNode;
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");

    cout << "Вариант №6: Написать программу, которая формирует двунаправленный список\n"
         << "целых чисел и добавляет в список элемент после элемента с минимальным\n"
         << "числовым значением в информационном поле." << endl;

    char povtor;
    do {
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
            int znach;
            cout << "Введите элемент " << i + 1 << " : ";
            cin >> znach;
            DobavVKonec(head, tail, znach);
        }

        cout << "Введённый список: ";
        Napechatat(head);

        if (head != nullptr) {
            int novoeZnach;
            cout << "Введите значение для нового элемента: ";
            cin >> novoeZnach;
            DobavPosleMinimalnogo(head, tail, novoeZnach);
            
            cout << "Список после обработки: ";
            Napechatat(head);
        }

        Ochistit(head, tail);

        cout << "Хотите начать заново (Y/N)? ";
        cin >> povtor;
    } while (povtor == 'Y' || povtor == 'y');

    return 0;
}
