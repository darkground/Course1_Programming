#include <iostream>
#include <limits> //нужно для numeric_limits

using namespace std;

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

void sort1() {

}

void sort2() {

}

int main() {
    while (true) {
        system("cls");
        cout <<
            "Choose a category from below:\n"
            "0. Exit\n"
            "1. Bubble Sort\n"
            "2. Shaker Sort\n"
            "3. Comb Sort\n"
            "4. Insert Sort\n"
            "5. Quick Sort\n\n";
        cout << "Type a number to continue: ";
        int choice = readValue<int>();
        system("cls");
        switch (choice) {
        case 0:
            return 0;
        default:
            cout << "\nCategory with number " << choice << " does not exist." << endl;
        }
        system("pause");
    }
}