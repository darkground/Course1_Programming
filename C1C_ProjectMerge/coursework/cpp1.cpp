#include <iostream>
#include <limits>
#include "cpp1.h"

using namespace std;

/*
*   Функция для ввода данных в терминал
*   При вызове функции нужно указать получаемые данные в скобках, т.е. readValue<int>() - получить число
*/
template <typename T>
T readValue() {
    T value;
    while (true) {
        cin >> value;
        if (cin.fail()) {
            cout << "\nIncorrect input. Enter new value: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
    }
}

int cpp1main() {
    while (true) {
        system ("cls");
        cout <<
            "Project #1: Memory structure\n\n"
            "Choose a category from below:\n"
            "0. Return to menu\n"
            "1. Type sizes\n"
            "2. Integer in memory\n"
            "3. Float in memory\n"
            "4. Double in memory\n\n";
        cout << "Type a number to continue: ";
        int choice = readValue<int>();
        system("cls");
        switch (choice) {
            case 0:
                return 0;
            case 1:
                typeSizes();
                break;
            case 2:
                integerTask();
                break;
            case 3:
                floatTask();
                break;
            case 4:
                doubleTask();
                break;
            default:
                cout << "\nCategory with number " << choice << " does not exist." << endl;
        }
        system("pause");
    }
}

/*
*   1) Вывести, сколько памяти(в байтах) на вашем компьютере отводится под различные типы данных
*   со спецификаторами и без : int, short int, long int, float, double, long double, char и bool.
*/
void typeSizes() {
    cout << "Size of 'int': \t\t" << sizeof(int) << " bytes" << endl;
    cout << "Size of 'short int': \t" << sizeof(short int) << " bytes" << endl;
    cout << "Size of 'long int': \t" << sizeof(long int) << " bytes" << endl;
    cout << "Size of 'float': \t" << sizeof(float) << " bytes" << endl;
    cout << "Size of 'double': \t" << sizeof(double) << " bytes" << endl;
    cout << "Size of 'long double': \t" << sizeof(long double) << " bytes" << endl;
    cout << "Size of 'char': \t" << sizeof(char) << " bytes" << endl;
    cout << "Size of 'bool': \t" << sizeof(bool) << " bytes" << endl;
}

void printInteger(int number) {
    unsigned int order = sizeof(number) * 8;
    unsigned int mask = 1 << (order - 1);

    for (unsigned int bit = 1; bit <= order; bit++) {
        cout << (bool)(number & mask);
        mask >>= 1;
        if (bit % 8 == 0 || bit == 1)
            cout << ' ';
    }
}

/*
*   2) Вывести на экран двоичное представление в памяти (все разряды) целого числа.
*   При выводе необходимо визуально обозначить знаковый разряд и значащие разряды
*   отступами или цветом
*/
void integerTask() {
    int number = 0;
    cout << "Input an integer: ";
    number = readValue<int>();
    
    printInteger(number);
    cout << "(" << number << ")" << endl;
      
    while (true) {
        char choice;
        do {
            cout << "Invert bytes? (y/n): ";
            choice = readValue<char>();
        } while (choice != 'y' && choice != 'n');

        if (choice == 'y') {
            number = ~number;
            printInteger(number);
            cout << "(" << number << ")" << endl;
        }
        else break;
    }
}

void printFloat(int sharedInt) {
    unsigned int order = sizeof(sharedInt) * 8;
    unsigned int mask = 1 << (order - 1);

    for (unsigned int bit = 1; bit <= order; bit++) {
        cout << (bool)(sharedInt & mask);
        mask >>= 1;
            
        if (bit <= 9) {
            if (bit == 1 || bit == 9)
                cout << ' ';
        }
        else {
            if (bit % 4 == 1)
                cout << ' ';
        }
    }
}

/*
*   3) Вывести на экран двоичное представление в памяти (все разряды) типа float.
*   При выводе необходимо визуально обозначить знаковый разряд мантиссы,
*   знаковый разряд порядка (если есть), мантиссу и порядок.
*/
void floatTask() {
    union {
        float number = 0.0;
        int numberInt;
    };

    cout << "Input a float: ";
    number = readValue<float>();

    printFloat(numberInt);
    cout << " (" << number << ")" << endl;

    while (true) {
        char choice;
        do {
            cout << "Invert bytes? (y/n): ";
            choice = readValue<char>();
        } while (choice != 'y' && choice != 'n');

        if (choice == 'y') {
            numberInt = ~numberInt;
            printFloat(numberInt);
            cout << " (" << number << ")" << endl;
        }
        else break;
    }

    printFloat(numberInt);
    cout << " (" << number << ")" << endl;
}

void printDouble(short int numberSegments[]) {
    unsigned int order = sizeof(short int) * 8;

    for (int memSegment = 4 - 1; memSegment >= 0; memSegment--)
    {
        int segment = numberSegments[memSegment];
        unsigned int mask = 1 << (order - 1);
        for (int bit = 1; bit <= order; bit++) {
            cout << (bool)(segment & mask);
            mask >>= 1;

            // Вычисление позиции бита во всём double, а не в текущем сегменте
            int totalBit = (3 - memSegment) * order + bit;
            if (totalBit == 1 || totalBit == 12)
                cout << ' ';
        }
    }
}

/*
*   4) Вывести на экран двоичное представление в памяти (все разряды) типа double. 
*   При выводе необходимо визуально обозначить знаковый разряд мантиссы, 
*   знаковый разряд порядка (если есть), мантиссу и порядок.
*/
void doubleTask() {
    union {
        double number = 0.0;
        short int numberSegments[4];
    };

    cout << "Input a double: ";
    number = readValue<double>();

    printDouble(numberSegments);
    cout << " (" << number << ")" << endl;

    while (true) {
        char choice;
        do {
            cout << "Invert bytes? (y/n): ";
            choice = readValue<char>();
        } while (choice != 'y' && choice != 'n');

        if (choice == 'y') {
            for (int memSegment = 4 - 1; memSegment >= 0; memSegment--)
                numberSegments[memSegment] = ~numberSegments[memSegment];
            printDouble(numberSegments);
            cout << "(" << number << ")" << endl;
        }
        else break;
    }
}
