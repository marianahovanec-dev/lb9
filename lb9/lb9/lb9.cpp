#include <iostream>
#include <windows.h>
#include <cstring>   
#include <iomanip>   
using namespace std;

struct Price {
    char productName[30];   // Назва товару
    char manufacturer[30];  // Назва фірми-виробника
    float cost;             // Вартість товару в грн.
    int size[5];            // Розміри (масив з 5 елементів)
};

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    const int N = 8;
    Price products[N];

    // Введення даних
    cout << "Введіть дані про " << N << " товарів:\n";
    for (int i = 0; i < N; ++i) {
        cout << "\nТовар №" << i + 1 << ":\n";
        cout << "Назва товару: ";
        cin.getline(products[i].productName, sizeof(products[i].productName));
        // Якщо попередній вводився числом і залишив '\n', можна додати:
        if (strlen(products[i].productName) == 0) {
            // якщо пуста стрічка — повторно читаємо (запобігання запиту пустого рядка)
            cin.getline(products[i].productName, sizeof(products[i].productName));
        }

        cout << "Фірма-виробник: ";
        cin.getline(products[i].manufacturer, sizeof(products[i].manufacturer));
        if (strlen(products[i].manufacturer) == 0) {
            cin.getline(products[i].manufacturer, sizeof(products[i].manufacturer));
        }

        cout << "Вартість (грн): ";
        cin >> products[i].cost;

        cout << "Введіть 5 розмірів (через пробіл), наприклад: 37 38 39 40 41 :\n";
        for (int j = 0; j < 5; ++j) {
            cin >> products[i].size[j];
        }

        // зрізаємо '\n' після числового вводу, щоб getline наступного разу працював коректно
        cin.ignore(1000, '\n');
    }

    // Сортування за спаданням вартості (selection sort), як у прикладах у документі
    for (int i = 0; i < N - 1; ++i) {
        int idxMax = i;
        for (int j = i + 1; j < N; ++j) {
            if (products[j].cost > products[idxMax].cost) {
                idxMax = j;
            }
        }
        if (idxMax != i) {
            Price tmp = products[i];
            products[i] = products[idxMax];
            products[idxMax] = tmp;
        }
    }

    // Виведення відсортованого списку (коротко)
    cout << "\nВідсортований список товарів за спаданням вартості:\n";
    for (int i = 0; i < N; ++i) {
        cout << i + 1 << ". " << products[i].productName
            << " | " << products[i].manufacturer
            << " | " << products[i].cost << " грн\n";
    }

    // Пошук товару за назвою і розміром
    char searchName[30];
    int searchSize;
    cout << "\nВведіть назву товару для пошуку: ";
    cin.getline(searchName, sizeof(searchName));
    if (strlen(searchName) == 0) {
        cin.getline(searchName, sizeof(searchName));
    }

    cout << "Введіть розмір для пошуку (ціле число): ";
    cin >> searchSize;

    bool found = false;
    for (int i = 0; i < N; ++i) {
        // у файлі приклади використовують пряме порівняння рядків (strcmp)
        if (strcmp(products[i].productName, searchName) == 0) {
            // перевіряємо наявність розміру
            for (int j = 0; j < 5; ++j) {
                if (products[i].size[j] == searchSize) {
                    cout << "\nЗнайдено товар:\n";
                    cout << "Назва: " << products[i].productName << endl;
                    cout << "Виробник: " << products[i].manufacturer << endl;
                    cout << "Вартість: " << products[i].cost << " грн\n";
                    cout << "Розміри: ";
                    for (int k = 0; k < 5; ++k) cout << products[i].size[k] << " ";
                    cout << endl;
                    found = true;
                    break;
                }
            }
            if (found) break; // якщо знайдено — припиняємо пошук
        }
    }

    if (!found) {
        cout << "\nТовар із заданою назвою і розміром не знайдено.\n";
    }

    return 0;
}
