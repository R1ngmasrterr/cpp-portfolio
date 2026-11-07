#include <iostream>
#include <string>
#include <limits>

using namespace std;

// Проверка, является ли строка целым числом
bool Proverka_na_chislo(const char* s) {
    if (s[0] == '\0') return false; // Пустая строка
    int start = 0;
    if (s[0] == '-') {
        if (s[1] == '\0') return false; // Только минус
        start = 1;
    }
    for (int i = start; s[i] != '\0'; ++i) {
        if (s[i] < '0' || s[i] > '9') return false;
    }
    return true;
}

// Перевод строки в число
int Perevod_v_chislo(const char* s) {
    int n = 0;
    bool otr = false;
    int start = 0;
    if (s[0] == '-') {
        otr = true;
        start = 1;
    }
    for (int i = start; s[i] != '\0'; ++i) {
        n = n * 10 + (s[i] - '0');
    }
    if (otr) n *= -1;
    return n;
}

// Модифицированный алгоритм простого выбора
void Sortirovka() {
    const int BUF = 256;
    char line[BUF];
    int n = -1;
    
    cout << "Введите длину массива: ";
    while (cin.getline(line, BUF)) {
        n = -1;
        if (Proverka_na_chislo(line)) {
            n = Perevod_v_chislo(line);
        }
        if (n < 1) {
            cout << "Некорректный ввод. Длина массива должна быть больше 0\n";
        } else {
            break;
        }
    }

    int* R = new int[n];
    for (int i = 0; i < n; ++i) {
        cout << "Введите число №" << (i + 1) << ": ";
        while (cin.getline(line, BUF)) {
            if (Proverka_na_chislo(line)) {
                R[i] = Perevod_v_chislo(line);
                break;
            }
            cout << "Некорректный ввод. Введите число.\n";
        }
    }

    int left = 0;
    int right = n - 1;
    while (left < right) {
        int min_ind = left;
        int max_ind = left;
        for (int i = left; i <= right; ++i) {
            if (R[i] < R[min_ind]) min_ind = i;
            if (R[i] > R[max_ind]) max_ind = i;
        }
        // Меняем местами левое значение с минимальным
        int temp = R[left]; 
        R[left] = R[min_ind]; 
        R[min_ind] = temp;
        
        // Если максимум стоял на месте left, после смены он переместился в min_ind
        if (max_ind == left) max_ind = min_ind;
        
        // Меняем местами правое значение с максимальным
        temp = R[right]; 
        R[right] = R[max_ind]; 
        R[max_ind] = temp;
        
        left += 1;
        right -= 1;
    }

    cout << "\nОтсортированный массив: ";
    for (int i = 0; i < n; ++i) {
        cout << R[i] << ' ';
    }
    cout << endl;
    delete[] R;
}

// Поиск значений в матрице
void Poisk_znachenie() {
    bool flag = true;
    const int BUF = 256;
    char line[BUF];
    int n = -1;
    int** M = nullptr;

    cout << "\nВариант №16:\nВ матрице n-го порядка найти максимальный среди элементов, лежащих ниже побочной диагонали,\nи минимальный среди элементов, лежащих выше главной диагонали.\n";

    while (flag) {
        cout << "\nВведите порядок матрицы: ";
        while (cin.getline(line, BUF)) {
            n = -1;
            if (Proverka_na_chislo(line)) {
                n = Perevod_v_chislo(line);
            }
            if (n >= 2) break;
            cout << "Некорректный ввод. Порядок матрицы должен быть больше 1,\nтак как при 0 - матрица не существует,\na при 1 - нет элементов выше и ниже диагоналей.\n";
            cout << "\nВведите порядок матрицы: ";
        }

        M = new int*[n];
        for (int i = 0; i < n; ++i) {
            M[i] = new int[n];
        }

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                cout << "Введите элемент [" << i << "][" << j << "]: ";
                while (cin.getline(line, BUF)) {
                    if (Proverka_na_chislo(line)) {
                        M[i][j] = Perevod_v_chislo(line);
                        break;
                    }
                    cout << "Некорректный ввод. Введите число.\n";
                }
            }
        }

        cout << "\nВы ввели матрицу:\n";
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                cout << M[i][j] << ' ';
            }
            cout << endl;
        }

        cout << "\nВерно? (Y/N)\n";
        while (cin.getline(line, BUF)) {
            if (line[0] == 'Y' || line[0] == 'y') {
                flag = false;
                break;
            } else if (line[0] == 'N' || line[0] == 'n') {
                for (int i = 0; i < n; ++i) delete[] M[i];
                delete[] M;
                flag = true;
                break;
            } else {
                cout << "Некорректный ввод. Введите N или Y\n";
            }
        }
        
        // Если пользователь подтвердил матрицу, ищем значения
        if (!flag) {
            int minim = M[0][1];
            int maxim = M[1][n - 1];
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    if (i < j && M[i][j] < minim) minim = M[i][j];
                    if (i + j > n - 1 && M[i][j] > maxim) maxim = M[i][j];
                }
            }
            cout << "\nМинимальное значение (выше главной): " << minim << endl;
            cout << "Максимальное значение (ниже побочной): " << maxim << endl;
            
            for (int i = 0; i < n; ++i) delete[] M[i];
            delete[] M;
        }
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    const int BUF = 256;
    char line[BUF];

    while (true) {
        cout << "\nВыберите функцию (1 или 2):\n";
        cout << "1. Модифицированный алгоритм простого выбора.\n";
        cout << "2. Поиск значений в матрице.\n";
        
        while (cin.getline(line, BUF)) {
            if (line[0] == '1' && line[1] == '\0') {
                Sortirovka();
                break;
            } else if (line[0] == '2' && line[1] == '\0') {
                Poisk_znachenie();
                break;
            }
            cout << "Некорректный ввод. Введите 1 или 2\n";
        }

        cout << "\nНачать заново? (Y/N)\n";
        bool exit_flag = false;
        while (cin.getline(line, BUF)) {
            if (line[0] == 'N' || line[0] == 'n') {
                exit_flag = true;
                break;
            } else if (line[0] == 'Y' || line[0] == 'y') {
                break;
            }
            cout << "Некорректный ввод. Введите N или Y\n";
        }
        
        if (exit_flag) return 0;
    }
}
