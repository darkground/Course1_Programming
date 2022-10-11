#include <iostream>
#include <limits> //нужно для numeric_limits
#include <chrono> //нужно для измерения выполнения функции

using namespace std;
using namespace chrono;

/*
*   Функция для ввода данных в терминал
*/

//При вызове функции нужно указать получаемые данные в скобках, т.е. readValue<int>() - получить число
template <typename T>
T readValue() {
    T value;
    while (true) {
        cin >> value;
        if (cin.fail()) {
            cout << "\nIncorrect input. Enter new value: ";
            cin.clear();
            // numeric_limits<streamsize> это предел количества знаков в streamsize (вернёт число)
            // нужно чтобы очистить максимальное количество оставшихся символов в буфере до новой строки
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        }
        else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
    }
}

/*
*   Функция для измерения выполнения переданной функции в миллисекундах.
*/

// Передавать в эту функцию нужно адрес функции, например, чтобы измерить hello():
// double result = measure(&hello);
double measure(void (*function)()){
    steady_clock::time_point t1 = high_resolution_clock::now();
    function();
    steady_clock::time_point t2 = high_resolution_clock::now();
    duration<double, milli> result = t2 - t1;
    return result.count();
}

void sort1() {

}

void sort2() {

}

void ccout() {
    for (int i = 0; i < 100; i++) {
        cout << i + 1 << endl;
    }
    cout << "Complete." << endl;
}

int main() {
    while (true) {
        system("cls");
        cout <<
            "Choose a category from below:\n"
            "0. Exit\n"
            "1. Sort\n";
        cout << "Type a number to continue: ";
        int choice = readValue<int>();
        system("cls");
        switch (choice) {
            case 0:
                return 0;
            case 1: 
                cout << "measure (ms): " << measure(&ccout) << endl;
                break;
            default:
                cout << "\nCategory with number " << choice << " does not exist." << endl;
        }
        system("pause");
    }
}