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
        cout << "Array[" << i << "] = " << array[i] << endl;
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
        cout << "Array state: " << (sortedIndicator ? "SORTED" : "UNSORTED") << "\n\n";
        cout <<
            "Choose a category from below:\n"
            "0. Exit\n"
            "1. Print array\n"
            "2. Generate new array\n"
            "3. Quick-sort array\n"
            "4. Min, max, average values in array\n"
            "5. Count values that are more than N\n"
            "6. Count values that are less than N\n\n";
        cout << "Type a number to continue: ";
        int choice = readValue<int>();
        cout << endl;
        switch (choice) {
            case 0:
                return 0;
            case 1:
                printArray(array);
                break;
            case 2: 
                step1(array);
                sortedIndicator = false;
                cout << "Generated new array with 100 elements in range [-99, 99]." << endl;
                break;
            case 3: {
                steady_clock::time_point t1 = high_resolution_clock::now();
                step2(array, 0, 99);
                steady_clock::time_point t2 = high_resolution_clock::now();
                duration<double, milli> result = t2 - t1;
                sortedIndicator = true;
                cout << "Sorted array, it took " << result.count() << " milliseconds." << endl;
            }
                break;
            case 4: {
                steady_clock::time_point t1 = high_resolution_clock::now();
                int maxValue = array[0];
                int minValue = array[0];
                for(int i = 1; i < 100; i++) {    
                    if (array[i] > maxValue)
                        maxValue = array[i];
                    if (array[i] < minValue)
                            minValue = array[i];
                }
                steady_clock::time_point t2 = high_resolution_clock::now();
                duration<double, milli> result = t2 - t1;
                cout << "Finding min and max values in " << (sortedIndicator ? "SORTED" : "UNSORTED") <<
                    " array took " << result.count() << " milliseconds." << endl;
                cout << "Min: " << minValue << endl;
                cout << "Max: " << maxValue << endl;
                cout << "Average: " << (minValue + maxValue) / 2 << endl;
            }
                break;
            case 5: {
                cout << "Input a number N: ";
                int number = readValue<int>();
                int count = 0;
                for(int i = 0; i < 100; i++) {    
                    if (array[i] > number)
                        count++;
                }
                cout << "There are " << count << " values more than " << number << "." << endl;
            }
                break;
            case 6: {
                cout << "Input a number N: ";
                int number = readValue<int>();
                int count = 0;
                for(int i = 0; i < 100; i++) {    
                    if (array[i] < number)
                        count++;
                }
                cout << "There are " << count << " values less than " << number << "." << endl;
            }
                break;
            default:
                cout << "\nCategory with number " << choice << " does not exist." << endl;
        }
        system("pause");
    }
}