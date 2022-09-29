#include <iostream>

using namespace std;

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

    cout << "(" << number << ")" << endl;
}

/*
*   2) Вывести на экран двоичное представление в памяти (все разряды) целого числа.
*   При выводе необходимо визуально обозначить знаковый разряд и значащие разряды
*   отступами или цветом
*/
void integerTask() {
    int number = 0;
    cout << "Input an integer: ";
    cin >> number;
    while (cin.fail()) { //Если ввыод был неправильного формата, то cin.fail() вернёт true
        cin.clear(); //Убрать флаг провала у cin
        cin.ignore(256, '\n'); //Очистить входной поток
        cin >> number;
    }
    
    printInteger(number);

    int bitN, bitV;
    cout << "Change bit... ";
    cin >> bitN;
    while (cin.fail() || bitN < 1 || bitN > 32) {
        cin.clear();
        cin.ignore(256, '\n');
        cin >> bitN;
    }
    cout << "Change to... ";
    cin >> bitV;
    while (cin.fail() || (bitV != 0 && bitV != 1)) {
        cin.clear();
        cin.ignore(256, '\n');
        cin >> bitV;
    }
    if (bitV == 0)
        number &= ~(1 << (32 - bitN));
    else 
        number |= (1 << (32 - bitN));
    
    printInteger(number);
}

void printFloat(int sharedInt) {
    unsigned int order = sizeof(sharedInt) * 8;
    unsigned int mask = 1 << (order - 1);

    for (unsigned int bit = 1; bit <= order; bit++) {
        cout << (bool)(sharedInt & mask);
        mask >>= 1;
        if (bit == 1 || bit == 9)
            cout << ' ';
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
    cin >> number;
    while (cin.fail()) {
        cin.clear();
        cin.ignore(256, '\n');
        cin >> number;
    }

    printFloat(numberInt);
    cout << " (" << number << ")" << endl;

    int bitN, bitV;
    cout << "Change bit... ";
    cin >> bitN;
    while (cin.fail() || bitN < 1 || bitN > 32) {
        cin.clear();
        cin.ignore(256, '\n');
        cin >> bitN;
    }
    cout << "Change to... ";
    cin >> bitV;
    while (cin.fail() || (bitV != 0 && bitV != 1)) {
        cin.clear();
        cin.ignore(256, '\n');
        cin >> bitV;
    }
    if (bitV == 0)
        numberInt &= ~(1 << (32 - bitN));
    else 
        numberInt |= (1 << (32 - bitN));

    printFloat(numberInt);
    cout << " (" << number << ")" << endl;
}


/*
*   4) Вывести на экран двоичное представление в памяти (все разряды) типа double. 
*   При выводе необходимо визуально обозначить знаковый разряд мантиссы, 
*   знаковый разряд порядка (если есть), мантиссу и порядок.
*/
void task4() {
    union {
        double number = 0.0;
        short int numberSegments[4];
    };

    cout << "Input a double: ";
    cin >> number;
    while (cin.fail()) {
        cin.clear();
        cin.ignore(256, '\n');
        cin >> number;
    }
    cout << "Representation in memory: ";

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

    cout << endl;
}

int main() {
    while (true) {
        system ("cls");
        cout << 
            "Choose a category from below:\n"
            "0. Exit\n"
            "1. Type sizes\n"
            "2. Integer in memory\n"
            "3. Float in memory\n"
            "4. Double in memory\n\n";
        cout << "Type a number to continue: ";
        int choice;
        cin >> choice;
        while (cin.fail()) {
            cin.clear();
            cin.ignore(256, '\n');
            cin >> choice;
        }
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
                break;
            default:
                cout << "\nCategory with that number does not exist." << endl;
        }
        system("pause");
    }
}