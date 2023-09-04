#include <iostream>
#include <limits> //нужно для numeric_limits
#include <iomanip> //нужно для setw (красивый вывод)
#include "cpp3.h"

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

/*
*   Получить рандомное число от 1 до N * N
*/
int rval() {
    return rand() % (N * N - 1) + 1;
}

int cpp3main()
{
    if (N < 2 || N % 2 != 0) {
        cout << "Invalid Size!\n";
        return 0;
    }
    srand(time(0));
    int arr[N][N]{};
    while (true) {
        system("cls");
        cout << "Project #3: Pointers & Double arrays\n\n";
        cout << "Matrix (" << N << "x" << N << "):\n";
        printMatrix(arr);
        cout <<
            "\nChoose a category from below:\n"
            "0. Return to menu\n"
            "1. Fill matrix (circles)\n"
            "2. Fill matrix (snake)\n"
            "3. Switch blocks (A)\n"
            "4. Switch blocks (B)\n"
            "5. Switch blocks (C)\n"
            "6. Switch blocks (D)\n"
            "7. Sort matrix\n"
            "8. Append number (+)\n"
            "9. Subtract number (-)\n"
            "10. Multiply by a number (*)\n"
            "11. Divide by a number (/)\n"
            "12. Individual task\n\n";
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
            switchA(arr);
            break;
        case 4:
            switchB(arr);
            break;
        case 5:
            switchC(arr);
            break;
        case 6:
            switchD(arr);
            break;
        case 7:
            system("cls");
            printMatrix(arr);
            quicksort(arr[0], 0, N * N - 1);
            cout << "\nAfter sorting:\n\n";
            printMatrix(arr);
            break;
        case 8:
            system("cls");
            addition(arr);
            break;
        case 9:
            system("cls");
            subtraction(arr);
            break;
        case 10:
            system("cls");
            multiplication(arr);
            break;
        case 11:
            system("cls");
            division(arr);
            break;
        case 12:
            system("cls");
            indvTask(arr);
            break;
        default:
            cout << "\nCategory with number " << choice << " does not exist." << endl;
        }
        system("pause");
    }
}

/*
*   Функция для вывода матрицы в терминал
*   setw используется для задания ширины поля числа (т.е. вывод будет красивым, в виде таблицы)
*   Если поставить blocks = true, то вывод будет форматирован в 4 блока
*/
void printMatrix(int (*arr)[N], bool blocks) {
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            int v = *(*(arr + i) + j);
            cout << setw(4) << v;
            if (blocks && (j + 1 == N / 2))
                cout << ' ';
        }
        if (blocks && (i + 1 == N / 2))
            cout << endl;
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
void fillStep(int (*arr)[N], int i, int j) {
    system("cls");
    int v = rval();
    *(*(arr + i) + j) = v;
    printMatrix(arr);
    cout << "Value at " << "[" << i + 1 << ", " << j + 1 << "] was set to " << v << endl;
    system("pause");
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
            fillStep(arr, loops, i);
        for(int i = loops + 1; i < N - loops; i++)
            fillStep(arr, i, N - loops - 1);
        for(int i = N - loops - 2; i >= loops; i--)
            fillStep(arr, N - loops - 1, i);
        for(int i = N - loops - 2; i > loops; i--)
            fillStep(arr, i, loops);
        
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
            fillStep(arr, i, column);
        column++;
        for(int i = N - 1; i >= 0; i--)
            fillStep(arr, i, column);
        column++;
    }
}

/*
*   Смена блоков матрицы A (задание 2a)
*   1 2  ->  3 1
*   3 4      4 2
*/
void switchA(int (*arr)[N]) {
    system("cls");
    printMatrix(arr, true);

    int tempBlock[N/2][N/2]{};
    for(int i = 0; i < N / 2; i++)
        for(int j = 0; j < N / 2; j++)
            *(*(tempBlock + i) + j) = *(*(arr + i) + j);
    
    for(int i = 0; i < N / 2; i++)
        for(int j = 0; j < N / 2; j++)
            *(*(arr + i) + j) = *(*(arr + i + N / 2) + j);
    
    for(int i = N / 2; i < N; i++)
        for(int j = 0; j < N / 2; j++)
            *(*(arr + i) + j) = *(*(arr + i) + j + N / 2);
    
    for(int i = N / 2; i < N; i++)
        for(int j = N / 2; j < N; j++)
            *(*(arr + i) + j) = *(*(arr + i - N / 2) + j);

    for(int i = 0; i < N / 2; i++)
        for(int j = N / 2; j < N; j++)
            *(*(arr + i) + j) = *(*(tempBlock + i) + j - N / 2);
    
    cout << "\nAfter switching blocks:\n\n";
    printMatrix(arr, true);
}

/*
*   Смена блоков матрицы B (задание 2b)
*   1 2  ->  4 3
*   3 4      2 1
*/
void switchB(int (*arr)[N]) {
    system("cls");
    printMatrix(arr, true);

    int tempBlock1[N/2][N/2]{};
    int tempBlock2[N/2][N/2]{};

    for(int i = 0; i < N / 2; i++)
        for(int j = 0; j < N / 2; j++)
            *(*(tempBlock1 + i) + j) = *(*(arr + i) + j);

    for(int i = 0; i < N / 2; i++)
        for(int j = N / 2; j < N; j++)
            *(*(tempBlock2 + i) + j - N / 2) = *(*(arr + i) + j);

    for(int i = 0; i < N / 2; i++)
        for(int j = 0; j < N / 2; j++)
            *(*(arr + i) + j) = *(*(arr + i + N / 2) + j + N / 2);

    for(int i = 0; i < N / 2; i++)
        for(int j = N / 2; j < N; j++)
            *(*(arr + i) + j) = *(*(arr + i + N / 2) + j - N / 2);

    for(int i = N / 2; i < N; i++)
        for(int j = N / 2; j < N; j++)
            *(*(arr + i) + j) = *(*(tempBlock1 + i - N / 2) + j - N / 2);

    for(int i = N / 2; i < N; i++)
        for(int j = 0; j < N / 2; j++)
            *(*(arr + i) + j) = *(*(tempBlock2 + i - N / 2) + j);
    
    cout << "\nAfter switching blocks:\n\n";
    printMatrix(arr, true);
}

/*
*   Смена блоков матрицы C (задание 2c)
*   1 2  ->  3 4
*   3 4      1 2
*/
void switchC(int (*arr)[N]) {
    system("cls");
    printMatrix(arr, true);

    int tempBlock1[N/2][N/2]{};
    int tempBlock2[N/2][N/2]{};

    for(int i = 0; i < N / 2; i++)
        for(int j = 0; j < N / 2; j++)
            *(*(tempBlock1 + i) + j) = *(*(arr + i) + j);

    for(int i = 0; i < N / 2; i++)
        for(int j = N / 2; j < N; j++)
            *(*(tempBlock2 + i) + j - N / 2) = *(*(arr + i) + j);

    for(int i = 0; i < N / 2; i++)
        for(int j = 0; j < N / 2; j++)
            *(*(arr + i) + j) = *(*(arr + i + N / 2) + j);

    for(int i = 0; i < N / 2; i++)
        for(int j = N / 2; j < N; j++)
            *(*(arr + i) + j) = *(*(arr + i + N / 2) + j);

    for(int i = N / 2; i < N; i++)
        for(int j = 0; j < N / 2; j++)
            *(*(arr + i) + j) = *(*(tempBlock1 + i - N / 2) + j);

    for(int i = N / 2; i < N; i++)
        for(int j = N / 2; j < N; j++)
            *(*(arr + i) + j) = *(*(tempBlock2 + i - N / 2) + j - N / 2);
    
    cout << "\nAfter switching blocks:\n\n";
    printMatrix(arr, true);
}

/*
*   Смена блоков матрицы D (задание 2d)
*   1 2  ->  2 1
*   3 4      4 3
*/
void switchD(int (*arr)[N]) {
    system("cls");
    printMatrix(arr, true);

    int tempBlock1[N/2][N/2]{};
    int tempBlock2[N/2][N/2]{};

    for(int i = 0; i < N / 2; i++)
        for(int j = 0; j < N / 2; j++)
            *(*(tempBlock1 + i) + j) = *(*(arr + i) + j);

    for(int i = N / 2; i < N; i++)
        for(int j = 0; j < N / 2; j++)
            *(*(tempBlock2 + i - N / 2) + j) = *(*(arr + i) + j);

    for(int i = 0; i < N / 2; i++)
        for(int j = 0; j < N / 2; j++)
            *(*(arr + i) + j) = *(*(arr + i) + j + N / 2);

    for(int i = N / 2; i < N; i++)
        for(int j = 0; j < N / 2; j++)
            *(*(arr + i) + j) = *(*(arr + i) + j + N / 2);

    for(int i = 0; i < N / 2; i++)
        for(int j = N / 2; j < N; j++)
            *(*(arr + i) + j) = *(*(tempBlock1 + i) + j - N / 2);

    for(int i = N / 2; i < N; i++)
        for(int j = N / 2; j < N; j++)
            *(*(arr + i) + j) = *(*(tempBlock2 + i - N / 2) + j - N / 2);
    
    cout << "\nAfter switching blocks:\n\n";
    printMatrix(arr, true);
}

/*
*   Быстрая сортировка двумерного массива. (задание 3)
*   Из-за того, что подмассивы идут последовательно в памяти,
*   сортирует как будто бы это одномерный массив
*/
void quicksort(int* arr, int ptStart, int ptEnd)
{
	int lb = ptStart; //Левый край (left bound)
	int rb = ptEnd; //Правый край (right bound)
	int anchor = *(arr + (lb + rb) / 2); //Опорная точка
	while (lb < rb)
	{
		while (*(arr + lb) < anchor) lb++;
		while (*(arr + rb) > anchor) rb--;
		if (lb <= rb)
		{
			swap(*(arr + lb), *(arr + rb));
			lb++;
			rb--;
		}
	}
	if (ptStart < rb) quicksort(arr, ptStart, rb);
	if (lb < ptEnd) quicksort(arr, lb, ptEnd);
}

/*
*   Добавить N ко всем числам (задание 4)
*/
void addition(int (*arr)[N]) {
    printMatrix(arr);
    cout << "Enter N: ";
    int nv = readValue<int>();
    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
            *(*(arr + i) + j) = *(*(arr + i) + j) + nv;
    cout << "\nAfter addition:\n\n";
    printMatrix(arr);
}

/*
*   Вычесть N из всех чисел (задание 4)
*/
void subtraction(int (*arr)[N]) {
    printMatrix(arr);
    cout << "Enter N: ";
    int nv = readValue<int>();
    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
            *(*(arr + i) + j) = *(*(arr + i) + j) - nv;
    cout << "\nAfter subtraction:\n\n";
    printMatrix(arr);
}

/*
*   Все числа умножить на N (задание 4)
*/
void multiplication(int (*arr)[N]) {
    printMatrix(arr);
    cout << "Enter N: ";
    int nv = readValue<int>();
    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
            *(*(arr + i) + j) = *(*(arr + i) + j) * nv;
    cout << "\nAfter multiplication:\n\n";
    printMatrix(arr);
}

/*
*   Все числа разделить на N (задание 4)
*   N = 0 не принимается
*/
void division(int (*arr)[N]) {
    printMatrix(arr);
    int nv = 0;
    do {
        cout << "Enter N: ";
        nv = readValue<int>();
    } while (nv == 0);

    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
            *(*(arr + i) + j) = *(*(arr + i) + j) / nv;
    cout << "\nAfter division:\n\n";
    printMatrix(arr);
}

/*
*   Индивидуальное задание (1).
*   Заполните матрицу случайными числами от 1 до N*N.
*   Создайте ещё одну матрицу порядка N. Заполните её случайными числами от 1 до N*N.
*   Сложите две матрицы, при этом отобразите все промежуточные выводы.
*/
void indvTask(int (*arr)[N]) {
    int arr2[N][N]{};
    
    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
            *(*(arr2 + i) + j) = rval();
    
    cout << "Created a new " << N << "x" << N << " matrix:\n";
    printMatrix(arr2);
    system("pause");
    
    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++) {
            system("cls");
            cout << "Old matrix:\n";
            printMatrix(arr);
            cout << "New matrix:\n";
            printMatrix(arr2);
            int s = *(*(arr + i) + j) + *(*(arr2 + i) + j);
            cout << "Value at [" << i + 1 << "," << j + 1 << "] = " << s << " (" << *(*(arr + i) + j) << " + " << *(*(arr2 + i) + j) << ")" << endl;
            *(*(arr + i) + j) = s;
            system("pause");
        }
    system("cls");
    cout << "Old matrix:\n";
    printMatrix(arr);
    cout << "Calculation complete." << endl;
}