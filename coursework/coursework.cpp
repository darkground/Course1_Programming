#include <iostream>
#include "cpp1.h"
#include "cpp2.h"
#include "cpp3.h"
#include "cpp4.h"

using namespace std;

/*
*   Функция для ввода данных в терминал
*   При вызове функции нужно указать получаемые данные в скобках,
*   т.е. readValue<int>() - получить число.
*   prompt - текст перед вводом
*/
template <typename T>
T readValue(const char* prompt) {
    T value;
    cout << prompt;
    while (true) {
        cin >> value;
        if (cin.fail()) {
            cout << "Incorrect input. Enter new value: ";
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

int main()
{
    while (true) {
        system("cls");
        cout <<
            "Choose project to open from below:\n"
            "0. Exit\n"
            "1. Project #1: Memory structure\n"
            "2. Project #2: Sorting algorithms\n"
            "3. Project #3: Pointers & Double arrays\n"
            "4. Project #4: String structure\n\n";
        int choice = readValue<int>("Type a number to continue: ");
        cout << endl;
        switch (choice) {
        case 0:
            return 0;
        case 1:
            cpp1main();
            break;
        case 2:
            cpp2main();
            break;
        case 3:
            cpp3main();
            break;
        case 4:
            cpp4main();
            break;
        default:
            cout << "\nProject with number " << choice << " does not exist." << endl;
            system("pause");
            break;
        }
    }
}