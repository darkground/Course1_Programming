#include <iostream>
#include <limits> //нужно для numeric_limits

const int N = 6;

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

int main()
{
    if (N % 2 != 0) {
        cout << "Invalid Size!\n";
        return 0;
    }
    srand(time(0));
    int array[N][N]{};
    while (true) {
        system("cls");
        cout <<
            "Choose a category from below:\n"
            "0. Exit\n"
            "1. Fill matrix\n"
            "2. Switch blocks (A)\n"
            "3. Switch blocks (B)\n"
            "4. Switch blocks (C)\n"
            "5. Switch blocks (D)\n"
            "6. Sort matrix\n"
            "7. Append number (+)\n"
            "8. Substract number (-)\n"
            "9. Multiply by a number (*)\n"
            "10. Divide by a number (/)\n\n";
        cout << "Type a number to continue: ";
        int choice = readValue<int>();
        cout << endl;
        switch (choice) {
        case 0:
            return 0;
        case 1:
            break;
        case 2:
             break;
        case 3:
             break;
        case 4:
             break;
        case 5:
             break;
        case 6:
             break;
        case 7:
             break;
        case 8:
             break;
        case 9:
             break;
        default:
            cout << "\nCategory with number " << choice << " does not exist." << endl;
        }
        system("pause");
    }
}