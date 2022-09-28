#include <iostream>

using namespace std;

/*
*   1) Вывести, сколько памяти(в байтах) на вашем компьютере отводится под различные типы данных
*   со спецификаторами и без : int, short int, long int, float, double, long double, char и bool.
*/
void task1() {
    cout << "Size of 'int': \t\t" << sizeof(int) << " bytes" << endl;
    cout << "Size of 'short int': \t" << sizeof(short int) << " bytes" << endl;
    cout << "Size of 'long int': \t" << sizeof(long int) << " bytes" << endl;
    cout << "Size of 'float': \t" << sizeof(float) << " bytes" << endl;
    cout << "Size of 'double': \t" << sizeof(double) << " bytes" << endl;
    cout << "Size of 'long double': \t" << sizeof(long double) << " bytes" << endl;
    cout << "Size of 'char': \t" << sizeof(char) << " bytes" << endl;
    cout << "Size of 'bool': \t" << sizeof(bool) << " bytes" << endl;
}

/*
*   2) Вывести на экран двоичное представление в памяти (все разряды) целого числа.
*   При выводе необходимо визуально обозначить знаковый разряд и значащие разряды
*   отступами или цветом
*/
void task2() {
    int number = 0;
    cout << "Input an integer: ";
    cin >> number;
    cout << "Representation in memory: ";

    unsigned int order = sizeof(number) * 8;
    unsigned int mask = 1 << (order - 1);

    for (unsigned int bit = 1; bit <= order; bit++) {
        cout << (bool)(number & mask);
        mask >>= 1;
        if (bit % 8 == 0 || bit == 1)
            cout << ' ';
    }
    cout << endl;
}

/*
*   3) Вывести на экран двоичное представление в памяти (все разряды) типа float.
*   При выводе необходимо визуально обозначить знаковый разряд мантиссы,
*   знаковый разряд порядка (если есть), мантиссу и порядок.
*/
void task3() {
    union {
        float number = 0.0f;
        int numberInt;
    };

    cout << "Input a float: ";
    cin >> number;
    cout << "Representation in memory: ";

    unsigned int order = sizeof(number) * 8;
    unsigned int mask = 1 << (order - 1);

    for (unsigned int bit = 1; bit <= order; bit++) {
        cout << (bool)(numberInt & mask);
        mask >>= 1;
        if (bit == 1 || bit == 9)
            cout << ' ';
    }
    //
    cout << endl;
}


/*
*   3) Вывести на экран двоичное представление в памяти (все разряды) типа float.
*   При выводе необходимо визуально обозначить знаковый разряд мантиссы,
*   знаковый разряд порядка (если есть), мантиссу и порядок.
*/
void task4() {
    union {
        double x = 1.5;
        short int doubleSegments[4];
    };

    unsigned int order = sizeof(short int) * 8;
    
    for (int memSegment = 4 - 1; memSegment >= 0; memSegment--)
    {
        int segment = doubleSegments[memSegment];
        unsigned int mask = 1 << (order - 1);
        for (int bit = 1; bit <= order; bit++) {
            cout << (bool)(segment & mask);
            mask >>= 1;
        }
    }

    cout << endl;
}

int main() {
    task1();
    //while (true) {
        //task2();
        //task3();
        task4();
        //}
}