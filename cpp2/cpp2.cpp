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

void printArray(int* array) {
    for(int i = 0; i < 100; i++) {
        cout << array[i] << endl;
    }
}

void step1(int* array) {
    for(int i = 0; i < 100; i++) {
        array[i] = -99 + (rand() * (int)(99 - (-99)) / RAND_MAX);
    }
}

void step2(int* array, int ptStart, int ptEnd)
{
	int lb = ptStart; //Левый край (left bound)
	int rb = ptEnd; //Правый край (right bound)
	int anchor = array[(lb + rb)/ 2]; //Опорная точка
	while (lb < rb)
	{
		while (array[lb] < anchor) lb++;
		while (array[rb]> anchor) rb--;
		if (lb <= rb)
		{
			swap(array[lb], array[rb]);
			lb++;
			rb--;
		}
	}
	if (ptStart < rb) step2(array, ptStart, rb);
	if (lb < ptEnd) step2(array, lb, ptEnd);
}

int main() {
    int array[100] {};
    bool sortedIndicator = false;
    step1(array);
    while (true) {
        system("cls");
        cout << "Array state: " << (sortedIndicator ? "sorted" : "not sorted") << "\n\n";
        cout <<
            "Choose a category from below:\n"
            "0. Exit\n"
            "1. Generate new array\n"
            "2. Quick-sort array\n";
        cout << "Type a number to continue: ";
        int choice = readValue<int>();
        system("cls");
        switch (choice) {
            case 0:
                return 0;
            case 1: 
                step1(array);
                sortedIndicator = false;
                cout << "Generated new array (N=100)." << endl;
                break;
            case 2: {
                steady_clock::time_point t1 = high_resolution_clock::now();
                step2(array, 0, 99);
                steady_clock::time_point t2 = high_resolution_clock::now();
                duration<double, milli> result = t2 - t1;
                sortedIndicator = true;
                cout << "Sorted array, it took " << result.count() << " milliseconds" << endl;
            }
                break;
            default:
                cout << "\nCategory with number " << choice << " does not exist." << endl;
        }
        system("pause");
    }
}