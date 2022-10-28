#include <iostream>
#include <limits> //нужно для numeric_limits
#include <chrono> //нужно для измерения выполнения функции

using namespace std;
using namespace chrono;

const int N = 120;

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
    for(int i = 0; i < N; i++) {
        cout << array[i] << ' ';
    }
    cout << endl;
}

// Заполнение массива случайными числами
void step1(int* array) {
    for(int i = 0; i < N; i++) {
        array[i] = rand() % 100 - 50;
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

int main() {
    srand(time(0));
    int array[N] {};
    bool sortedIndicator = false;
    step1(array);
    while (true) {
        system("cls");
        printArray(array);
        cout << "Array: N = " << N << ", " << (sortedIndicator ? "SORTED" : "UNSORTED") << "\n\n";
        cout <<
            "Choose a category from below:\n"
            "0. Exit\n"
            "1. Generate new array\n"
            "2. Quick-sort array\n"
            "3. Min, max, average values in array\n"
            "4. Count values that are more than N\n"
            "5. Count values that are less than N\n"
            "6. Find a value\n"
            "7. Swap values by index\n\n";
        cout << "Type a number to continue: ";
        int choice = readValue<int>();
        cout << endl;
        switch (choice) {
            case 0:
                return 0;
            case 1: 
                step1(array);
                sortedIndicator = false;
                cout << "Generated new array with 100 elements in range [-50, 50]." << endl;
                break;
            case 2: {
                auto t1 = steady_clock::now();
                step2(array, 0, 99);
                auto t2 = steady_clock::now();
                auto result = duration_cast<nanoseconds>(t2 - t1);
                sortedIndicator = true;
                cout << "Sorted array, it took " << result.count() << " nanoseconds." << endl;
            }
                break;
            case 3: {
                int maxValue = array[0];
                int minValue = array[0];
                if (sortedIndicator) {   
                    auto t1 = steady_clock::now();
                    maxValue = array[N-1];
                    minValue = array[0];
                    auto t2 = steady_clock::now();
                    auto result = duration_cast<nanoseconds>(t2 - t1);
                    cout << "Finding min and max values in SORTED array took " << result.count() << " nanoseconds." << endl; 
                } else {
                    auto t1 = steady_clock::now();
                    for(int i = 1; i < N; i++) {    
                        if (array[i] > maxValue)
                            maxValue = array[i];
                        if (array[i] < minValue)
                                minValue = array[i];
                    }
                    auto t2 = steady_clock::now();
                    auto result = duration_cast<nanoseconds>(t2 - t1);
                    cout << "Finding min and max values in UNSORTED array took " << result.count() << " nanoseconds." << endl; 
                }
                cout << "Min: " << minValue << endl;
                cout << "Max: " << maxValue << endl;
                cout << "Average: " << (minValue + maxValue) / 2 << endl;
            }
                break;
            case 4: {
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
            case 5: {
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
            case 6: {
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
            case 7: {
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
            default:
                cout << "\nCategory with number " << choice << " does not exist." << endl;
        }
        system("pause");
    }
}