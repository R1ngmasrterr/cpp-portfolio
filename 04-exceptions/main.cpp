#define NOMINMAX
#include <iostream>
#include <string>
#include <stdexcept>
#include <windows.h>

using namespace std;

class Sfera {
public:
    Sfera(int r, int cx, int cy, int cz) {
        if (r <= 0) {
            throw invalid_argument("Ошибка: Радиус сферы должен быть больше нуля!");
        }
        radius = r;
        x = cx;
        y = cy;
        z = cz;
        cout << "Сфера успешно создана." << endl;
    }

    void Napechatat() const {
        cout << "Параметры сферы: Радиус = " << radius 
             << ", Центр = (" << x << ", " << y << ", " << z << ")" << endl;
    }

private:
    int radius;
    int x, y, z;
};

int VvodCisla(const string& soobshenie) {
    string s;
    cout << soobshenie;
    cin >> s;

    // Посимвольная проверка: допускаем минус только в начале
    for (size_t i = 0; i < s.length(); ++i) {
        if (i == 0 && s[i] == '-') continue;
        if (s[i] < '0' || s[i] > '9') {
            throw "Ошибка: введен специальный символ вместо целого числа!";
        }
    }

    try {
        return stoi(s);
    } catch (const out_of_range&) {
        throw "Ошибка: введенное число слишком велико для типа int!";
    }
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");

    cout << "Вариант №6: Написать программу, в которой обрабатывается следующее исключение:\n"
         << "Ввод пользователем специального символа вместо целого числа.\n"
         << "Далее создается класс сфера с полями - радиус, координаты центра (x, y, z).\n"
         << "При невозможности создания сферы обработать исключение в блоках try-catch." << endl;

    char povtor;
    do {
        try {
            int r = VvodCisla("Введите радиус сферы: ");
            int x = VvodCisla("Введите координату X центра: ");
            int y = VvodCisla("Введите координату Y центра: ");
            int z = VvodCisla("Введите координату Z центра: ");

            Sfera sfera(r, x, y, z);
            sfera.Napechatat();
        }
        catch (const char* error_message) {
            cout << error_message << endl;
        }
        catch (const invalid_argument& e) {
            cout << e.what() << endl;
        }
        catch (...) {
            cout << "Неизвестная ошибка!" << endl;
        }

        cout << "Хотите начать заново (Y/N)? ";
        cin >> povtor;
    } while (povtor == 'Y' || povtor == 'y');

    return 0;
}
