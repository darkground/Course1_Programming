#include <iostream>
#include <limits> //нужно для numeric_limits
#include <iomanip> //нужно для setw (красивый вывод)

const int N = 6; //8 or 10

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

/*
*   Функция для вывода матрицы в терминал
*   setw используется для задания ширины поля числа (т.е. вывод будет красивым, в виде таблицы)
*/
void printMatrix(int (*arr)[N]) {
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            int v = *(*(arr + i) + j);
            if (v == 0) // Если число равно нулю, то просто вывести точку (для видимости)
                cout << "   ."; 
            else
                cout << setw(4) << v;
        }
        cout << endl;
    }
}

/*
*   Функция для установки всех чисел матрицы на ноль
*/
void emptyMatrix(int (*arr)[N]) {
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            *(*(arr + i) + j) = 0;
        }
    }
}

/*
*   Промежуточный этап заполнения матрицы:
*   Поэтапный вывод полученной матрицы, вывод того, что изменилось
*/
void fillStep(int (*arr)[N], int i, int j, int value) {
    system("cls");
    *(*(arr + i) + j) = value;
    printMatrix(arr);
    cout << "Value at " << "[" << i + 1 << ", " << j + 1 << "] was set to " << value << endl;
    system("pause");
}

/*
*   Получить рандомное число от 1 до N * N
*/
int rval() {
    return rand() % (N*N - 1) + 1;
}

/*
*   Задание 1, часть 1
*   Поэтапно заполнить матрицу кругом случайными числами от 1 до N * N
*/
void fillCircled(int (*arr)[N]) {
    emptyMatrix(arr);
    int loops = 0;
    while (loops < N) {
        for(int i = loops; i < N - loops; i++)
            fillStep(arr, loops, i, rval());
        for(int i = loops + 1; i < N - loops; i++)
            fillStep(arr, i, N - loops - 1, rval());
        for(int i = N - loops - 2; i >= loops; i--)
            fillStep(arr, N - loops - 1, i, rval());
        for(int i = N - loops - 2; i > loops; i--)
            fillStep(arr, i, loops, rval());
        
        loops++;
    }
}

/*
*   Задание 1, часть 2
*   Поэтапно заполнить матрицу змейкой случайными числами от 1 до N * N
*/
void fillSnake(int (*arr)[N]) {
    emptyMatrix(arr);
    int column = 0;
    while (column < N) {
        for(int i = 0; i < N; i++)
            fillStep(arr, i, column, rval());
        column++;
        for(int i = N - 1; i >= 0; i--)
            fillStep(arr, i, column, rval());
        column++;
    }
}

int main()
{
    if (N % 2 != 0) {
        cout << "Invalid Size!\n";
        return 0;
    }
    srand(time(0));
    int arr[N][N]{};
    while (true) {
        system("cls");
        cout << "Matrix (" << N << "x" << N << "):\n";
        printMatrix(arr);
        cout <<
            "Choose a category from below:\n"
            "0. Exit\n"
            "1. Fill matrix (circles)\n"
            "2. Fill matrix (snake)\n"
            "3. Switch blocks (A)\n"
            "4. Switch blocks (B)\n"
            "5. Switch blocks (C)\n"
            "6. Switch blocks (D)\n"
            "7. Sort matrix\n"
            "8. Append number (+)\n"
            "9. Substract number (-)\n"
            "10. Multiply by a number (*)\n"
            "11. Divide by a number (/)\n\n";
        cout << "Type a number to continue: ";
        int choice = readValue<int>();
        cout << endl;
        switch (choice) {
        case 0:
            return 0;
        case 1:
            fillCircled(arr);
            system("cls");
            printMatrix(arr);
            cout << "Matrix generation complete." << endl;
            break;
        case 2:
            fillSnake(arr);
            system("cls");
            printMatrix(arr);
            cout << "Matrix generation complete." << endl;
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
        case 10:
            break;
        case 11:
            break;
        default:
            cout << "\nCategory with number " << choice << " does not exist." << endl;
        }
        system("pause");
    }
}