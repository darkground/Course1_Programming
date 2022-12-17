#include <iostream>
#include <limits> //нужно для numeric_limits
#include <chrono> //нужно для измерения выполнения функции
#include "cpp2.h"

using namespace std;
using namespace chrono;

const int N = 100;

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

int cpp2main() {
    srand(time(0));
    int array[N] {};
    bool sortedIndicator = false;
    step1(array);
    while (true) {
        system("cls");
        cout << "Project #2: Sorting algorithms\n\n";
        for(int i = 0; i < N; i++) {
            cout << array[i] << ' ';
        }
        cout << "\nArray: N = " << N << ", " << (sortedIndicator ? "SORTED" : "UNSORTED") << "\n\n";
        cout <<
            "Choose a category from below:\n"
            "0. Return to menu\n"
            "1. Generate new array\n"
            "2. Sort array using Quick Sort\n"
            "3. Sort array using Bubble Sort\n"
            "4. Sort array using Comb Sort\n"
            "5. Sort array using Insert Sort\n"
            "6. Sort array using Shaker Sort\n"
            "7. Min, max, average values in array\n"
            "8. Count values that are more than N\n"
            "9. Count values that are less than N\n"
            "10. Find a value\n"
            "11. Swap values by index\n"
            "12. Individual Task\n\n";
        cout << "Type a number to continue: ";
        int choice = readValue<int>();
        cout << endl;
        switch (choice) {
            case 0:
                return 0;
            case 1: 
                step1(array);
                sortedIndicator = false;
                cout << "Generated new array with 100 elements in range [-99, 99]." << endl;
                break;
            case 2: {
                auto t1 = steady_clock::now();
                step2_quick(array, 0, N - 1);
                auto t2 = steady_clock::now();
                auto result = duration_cast<nanoseconds>(t2 - t1);
                sortedIndicator = true;
                cout << "Sorted array, it took " << result.count() << " nanoseconds." << endl;
            }
                break;
            case 3: {
                auto t1 = steady_clock::now();
                step2_bubble(array);
                auto t2 = steady_clock::now();
                auto result = duration_cast<nanoseconds>(t2 - t1);
                sortedIndicator = true;
                cout << "Sorted array, it took " << result.count() << " nanoseconds." << endl;
            }
                break;
            case 4: {
                auto t1 = steady_clock::now();
                step2_comb(array);
                auto t2 = steady_clock::now();
                auto result = duration_cast<nanoseconds>(t2 - t1);
                sortedIndicator = true;
                cout << "Sorted array, it took " << result.count() << " nanoseconds." << endl;
            }
                break;
            case 5: {
                auto t1 = steady_clock::now();
                step2_insert(array);
                auto t2 = steady_clock::now();
                auto result = duration_cast<nanoseconds>(t2 - t1);
                sortedIndicator = true;
                cout << "Sorted array, it took " << result.count() << " nanoseconds." << endl;
            }
                break;
            case 6: {
                auto t1 = steady_clock::now();
                step2_shaker(array);
                auto t2 = steady_clock::now();
                auto result = duration_cast<nanoseconds>(t2 - t1);
                sortedIndicator = true;
                cout << "Sorted array, it took " << result.count() << " nanoseconds." << endl;
            }
                break;
            case 7: {
                int maxValue = -101;
                int minValue = 101;
                if (sortedIndicator) {
                    minValue = array[0];
                    maxValue = array[N-1];
                } else {
                    for(int i = 1; i < N; i++) {    
                        if (array[i] > maxValue)
                            maxValue = array[i];
                        if (array[i] < minValue)
                            minValue = array[i];
                    }
                }
                int midValue = (minValue + maxValue) / 2;
                cout << "Min: " << minValue << endl;
                cout << "Max: " << maxValue << endl;
                cout << "Average: " << midValue << endl;
                if (sortedIndicator) {
                    auto t1 = steady_clock::now();
                    int counted = count_sorted(array, midValue);
                    auto t2 = steady_clock::now();
                    auto result = duration_cast<nanoseconds>(t2 - t1);
                    cout << "Counted " << counted << " values (took " << result.count() << " nanoseconds.)" << endl; 
                } else {
                    auto t1 = steady_clock::now();
                    int counted = count_unsorted(array, midValue);
                    auto t2 = steady_clock::now();
                    auto result = duration_cast<nanoseconds>(t2 - t1);
                    cout << "Counted " << counted << " values (took " << result.count() << " nanoseconds.)" << endl; 
                }
            }
                break;
            case 8: {
                cout << "Input a number N: ";
                int number = readValue<int>();
                int count = 0;
                for(int i = 0; i < 100; i++) {    
                    if (array[i] > number)
                        count++;
                    else break;
                }
                cout << "There are " << count << " values more than " << number << "." << endl;
            }
                break;
            case 9: {
                cout << "Input a number N: ";
                int number = readValue<int>();
                int count = 0;
                for(int i = 0; i < 100; i++) {    
                    if (array[i] < number)
                        count++;
                    else break;
                }
                cout << "There are " << count << " values less than " << number << "." << endl;
            }
                break;
            case 10: {
                cout << "Input a number N: ";
                int number = readValue<int>();
                cout << "Binary search -- ";
                if (sortedIndicator){
                    auto bt1 = steady_clock::now();
                    int bvalIndex = step7binary(array, number);
                    auto bt2 = steady_clock::now();
                    auto bresult = duration_cast<nanoseconds>(bt2 - bt1);
                    if (bvalIndex == -1)
                        cout << "Value was not found!";
                    else 
                        cout << "Value's index: " << bvalIndex;
                    cout << " (took " << bresult.count() << " nanoseconds)" << endl;
                }
                else cout << "Array is not sorted!" << endl;

                cout << "Default search -- ";
                auto dt1 = steady_clock::now();
                int dvalIndex = step7default(array, number);
                auto dt2 = steady_clock::now();
                auto dresult = duration_cast<nanoseconds>(dt2 - dt1);
                if (dvalIndex == -1)
                    cout << "Value was not found!";
                else 
                    cout << "Value's index: " << dvalIndex;
                cout << " (took " << dresult.count() << " nanoseconds)" << endl;
            }
                  break;
            case 11: {
                int index1 = 0;
                do {
                    cout << "Input an index N1: ";
                    index1 = readValue<int>();
                } while (index1 < 0 || index1 > N - 1);                
                
                int index2 = 0;
                do {
                    cout << "Input an index N2: ";
                    index2 = readValue<int>();
                } while (index2 < 0 || index2 > N - 1);
                
                if (index1 == index2) {
                    cout << "Error, indexes are the same" << endl;
                    break;
                }
                auto t1 = steady_clock::now();
                swap(array[index1], array[index2]);
                auto t2 = steady_clock::now();
                auto result = duration_cast<nanoseconds>(t2 - t1);
                sortedIndicator = false;
                cout << "Swapping took " << result.count() << " nanoseconds." << endl;
            }
                break;
            case 12: {
                cout << "Input a number N: ";
                int n = readValue<int>();
                for (int i = 1; i < N; i += 2) {
                    array[i] -= n;
                    array[i] *= rand() % 9 + 1;
                }
                for (int i = 1; i < 10; i++) {
                    cout << "Dividable by " << i << ": ";
                    int count = 0;
                    for (int j = 0; j < N; j++) {
                        if (array[j] % i == 0)
                            count++;
                    }
                    cout << count << endl;
                }
            }
                break;
            default:
                cout << "\nCategory with number " << choice << " does not exist." << endl;
        }
        system("pause");
    }
}

//Заполнение массива случайными числами
void step1(int* array) {
    for(int i = 0; i < N; i++) {
        array[i] = rand() % 199 - 99;
    }
}

//Быстрая сортировка
//Сложность: O(n^2)
void step2_quick(int* array, int ptStart, int ptEnd) {
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
	if (ptStart < rb) step2_quick(array, ptStart, rb);
	if (lb < ptEnd) step2_quick(array, lb, ptEnd);
}

//Пузырьковая сортировка
//Сложность: O(n^2)
void step2_bubble(int* array) {
    for(int i = 0; i < N - 1; i++) {
        bool flag = true;
        for (int j = 0; j < N - i - 1; j++) {
            if(array[j] > array[j + 1]) {
                flag = false;
                swap(array[j], array[j + 1]);
            }
        }
        if (flag)
            break;
    }
}

//Сортировка вставками
//Сложность: O(n^2)
void step2_insert(int* array) {
    for(int i = 1; i < N; i++) {
        for(int j = i; j > 0 && array[j - 1] > array[j]; j--) {
            swap(array[j - 1], array[j]);
        }
    }
}

//Сортировка расчёской
//Сложность: O(n^2)
void step2_comb(int* array) {
    const float K = 1.247; //Коэффициент уменьшения
    float S = N - 1; //Расстояние
    while(S >= 1) {
        for (int i = 0; i + S < N; i++) {
            if (array[i] > array[int(i + S)]) {
                swap(array[i], array[int(i + S)]);
            }
        }
        S /= K;
    }
    step2_bubble(array);
}

//Сортировка шейкер
//Сложность: O(n^2)
void step2_shaker(int* array) {
    int lb = 0;
    int rb = N - 1;
    bool changed = true;
    while(changed) {
        changed = false;
        for(int i = lb; i < rb; i++) {
            if (array[i] > array[i + 1]) {
                swap(array[i], array[i + 1]);
                changed = true;
            }
        }

        if (!changed)
            break;
        rb--;

        for(int i = rb - 1; i >= lb; i--) {
            if (array[i] > array[i + 1]) {
                swap(array[i], array[i + 1]);
                changed = true;
            }
        }
        lb++;
    }
}

//Бинарный поиск индекса числа
int step7binary(int* array, int value) {
    int low = 0;
    int mid = 0;
    int high = N - 1;
    while (low <= high) {
        mid = low + (high - low) / 2;
        if (value == array[mid])
            return mid;
        
        if (value > array[mid])
            low = mid + 1; //Для смещения mid направо на следующей итерации поиска
        else
            high = mid - 1; //Для смещения mid налево на следующей итерации поиска
    };
    return -1; //Значение не найдено
}

//Обычный поиск индекса числа
int step7default(int* array, int value) {
    for(int i = 0; i < N; i++) {
        if (array[i] == value)
            return i;
    }
    return -1; //Значение не найдено
}

//Подсчёт элементов сортированного массива
int count_sorted(int* array, int value) {
    int index = step7binary(array, value);
    if (index == -1) return 0;
    int count = 1;
    for (int i = index - 1; i > 0; i--) {
        if (array[i] == value) count++;
    }
    for (int i = index + 1; i < N - 1; i++) {
        if (array[i] == value) count++;
    }
    return count;
}

//Подсчёт элементов сортированного массива
int count_unsorted(int* array, int value) {
    int index = step7default(array, value);
    if (index == -1) return 0;
    int count = 1;
    for (int i = index + 1; i < N - 1; i++) {
        if (array[i] == value) count++;
    }
    return count;
}