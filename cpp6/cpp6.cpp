#include <iostream>
#include <chrono>
#include "list.h"
#include "dynarr.h"

using namespace std;
using namespace chrono;

/*
*   Функция для ввода данных в терминал
*   При вызове функции нужно указать получаемые данные в скобках,
*   т.е. readValue<int>() - получить число.
*   prompt - текст перед вводом
*   value - значение для заполнения
*/
template <typename T>
T readValue(const char* prompt = "") {
    T value = 0;
    cout << prompt;
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

void printList(List* list) {
    if (list) {
        cout << "List[" << list->length << "] = { ";
        for(int i = 0; i < list->length; i++)
            cout << listItem(list, i)->data << " ";
        cout << "}\n";
    } else
        cout << "List is undefined.\n";
}

void printDynarr(Dynarr* arr) {
    if (arr) {
        cout << "Array[" << arr->length << "/" << arr->capacity << "] = { ";
        for (int i = 0; i < arr->length; i++)
            cout << dynarrItem(arr, i) << " ";
        cout << "}\n";
    }
    else
        cout << "Array is undefined.\n";
}

void step1ListRandom(List*& list, unsigned n) {
    list = listCreate();
    list->length = n;

    ListNode* prev = new ListNode;
    prev->data = rand() % 100;
    list->head = prev;
    if (n != 0) {
        n--;
        while (n--) {
            ListNode* curr = new ListNode;
            curr->data = rand() % 100;
            prev->next = curr;
            curr->prev = prev;
            prev = curr;
        }
    }
}

void step1ArrayRandom(Dynarr*& arr, unsigned n) {
    arr = dynarrCreate();
    for (int i = 0; i < n; i++)
        dynarrAdd(arr, rand() % 100);
}

void step1Input(List*& list, Dynarr*& arr) {
    cout << "Input numbers line by line, finish by typing any non-digit character (e.g. \"a\").\n";
    
    list = listCreate();
    arr = dynarrCreate();

    int val;
    ListNode* prev = 0;
    while (true) {
        cout << "#" << list->length + 1 << ": ";
        cin >> val;
        if (cin.fail())
            break;
        //Array
        dynarrAdd(arr, val);
        //List
        if (list->length == 0) {
            prev = new ListNode;
            prev->data = val;
            list->head = prev;
        } else {
            ListNode* curr = new ListNode;
            curr->data = val;
            curr->prev = prev;
            if (prev) // C6011??
                prev->next = curr;
            prev = curr;
        }
        list->length++;
    }
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int main()
{
    bool notEqual = false;
    List* list = 0;
    Dynarr* arr = 0;
    while (true) {
        system("cls");
        printList(list);
        printDynarr(arr);
        cout <<
            "\nChoose a category from below:\n"
            "0. Exit\n"
            "1. Create list & array with Pre-Defined N (Random numbers)\n"
            "2. Create list & array until stopped (Input numbers)\n"
            "3. Insert element into list & array by index\n"
            "4. Remove element from list & array by index\n"
            "5. Remove element from list & array by value\n"
            "6. Swap elements in list & array by index\n"
            "7. Get element in list & array by index\n"
            "8. Get element in list & array by value\n"
            "9. Individual task\n\n";
        int choice = readValue<int>("Type a number to continue: ");
        cout << endl;
        switch (choice) {
            case 0:
                return 0;
            case 1: {
                if (list) {
                    listClear(list);
                    dynarrClear(arr);
                }

                int n = 0;
                do {
                    n = readValue<int>("Element count N: ");
                } while (n < 0);
                auto t = time(NULL);
                auto t1 = steady_clock::now();
                srand(t);
                step1ListRandom(list, n);
                auto t2 = steady_clock::now();
                srand(t);
                step1ArrayRandom(arr, n);
                auto t3 = steady_clock::now();
                notEqual = false;
                auto list_t = duration_cast<nanoseconds>(t2 - t1);
                auto arr_t = duration_cast<nanoseconds>(t3 - t2);
                cout << "List generation complete in " << list_t.count() << " nanoseconds." << endl;
                cout << "Array generation complete in " << arr_t.count() << " nanoseconds." << endl;
            }
                break;
            case 2:
                if (list) {
                    listClear(list);
                    dynarrClear(arr);
                }

                step1Input(list, arr);
                notEqual = false;
                cout << "List/array generation complete." << endl;
                break;
            case 3: {
                if (!list) {
                    cout << "Generate a list/array first!" << endl;
                    break;
                }
                if (notEqual) {
                    cout << "New list/array should be generated before inserting (speed cannot be compared, elements are not equal)" << endl;
                    break;
                }
                int i = 0;
                do {
                    i = readValue<int>("Element index I: ");
                } while (i < 0 || i > list->length);
                int v = readValue<int>("Element value V: ");
                auto t1 = steady_clock::now();
                listInsert(list, i, v);
                auto t2 = steady_clock::now();
                dynarrInsert(arr, i, v);
                auto t3 = steady_clock::now();
                notEqual = false;
                auto list_t = duration_cast<nanoseconds>(t2 - t1);
                auto arr_t = duration_cast<nanoseconds>(t3 - t2);
                cout << "Element inserted into list, took " << list_t.count() << " nanoseconds." << endl;
                cout << "Element inserted into array, took " << arr_t.count() << " nanoseconds." << endl;
            }
                  break;
            case 4: {
                if (!list) {
                    cout << "Generate a list/array first!" << endl;
                    break;
                }
                if (notEqual) {
                    cout << "New list/array should be generated before removing (speed cannot be compared, elements are not equal)" << endl;
                    break;
                }
                if (list->length == 0) {
                    cout << "List/array has no elements!" << endl;
                    break;
                }
                int i = 0;
                do {
                    i = readValue<int>("Element index I: ");
                } while (i < 0 || i >= list->length);
                auto t1 = steady_clock::now();
                listRemove(list, i);
                auto t2 = steady_clock::now();
                dynarrRemove(arr, i);
                auto t3 = steady_clock::now();
                auto list_t = duration_cast<nanoseconds>(t2 - t1);
                auto arr_t = duration_cast<nanoseconds>(t3 - t2);
                cout << "Element removed from list, took " << list_t.count() << " nanoseconds." << endl;
                cout << "Element removed from list, took " << arr_t.count() << " nanoseconds." << endl;
            }
                  break;
            case 5: {
                if (!list) {
                    cout << "Generate a list/array first!" << endl;
                    break;
                }
                if (notEqual) {
                    cout << "New list/array should be generated before removing (speed cannot be compared, elements are not equal)" << endl;
                    break;
                }
                if (list->length == 0) {
                    cout << "List/array has no elements!" << endl;
                    break;
                }
                int v = readValue<int>("Element value V: ");
                auto t1 = steady_clock::now();
                ListNode* prev = list->head;
                int nodeindex = 0;
                while (prev) {
                    if (prev->data == v)
                        break;
                    nodeindex++;
                    prev = prev->next;
                }
                
                if (nodeindex < list->length)
                    listRemove(list, nodeindex);
                auto t2 = steady_clock::now();
                int index = -1;
                for (int i = 0; i < arr->length; i++) {
                    int val = dynarrItem(arr, i);
                    if (val == v) {
                        index = i;
                        break;
                    }
                }
                if (index != -1)
                    dynarrRemove(arr, index);
                auto t3 = steady_clock::now();
                auto list_t = duration_cast<nanoseconds>(t2 - t1);
                auto arr_t = duration_cast<nanoseconds>(t3 - t2);
                if (index == -1) {
                    cout << "Element not found" << endl; 
                } else {
                    cout << "Element removed from list, took " << list_t.count() << " nanoseconds." << endl;
                    cout << "Element removed from list, took " << arr_t.count() << " nanoseconds." << endl;
                }
            }
                  break;
            case 6: {
                if (!list) {
                    cout << "Generate a list/array first!" << endl;
                    break;
                }
                if (notEqual) {
                    cout << "New list/array should be generated before swapping (speed cannot be compared, elements are not equal)" << endl;
                    break;
                }
                int n1 = 0;
                int n2 = 0;
                do {
                    n1 = readValue<int>("Element index N1: ");
                } while (n1 < 0 || n1 >= list->length);
                do {
                    n2 = readValue<int>("Element index N2: ");
                } while (n2 < 0 || n2 >= list->length);
                if (n1 == n2)
                    cout << "You entered same indexes.";
                else {
                    auto t1 = steady_clock::now();
                    listSwap(list, n1, n2);
                    auto t2 = steady_clock::now();
                    dynarrSwap(arr, n1, n2);
                    auto t3 = steady_clock::now();
                    auto list_t = duration_cast<nanoseconds>(t2 - t1);
                    auto arr_t = duration_cast<nanoseconds>(t2 - t1);
                    cout << "Elements swapped in list, took " << list_t.count() << " nanoseconds." << endl;
                    cout << "Elements swapped in array, took " << arr_t.count() << " nanoseconds." << endl;
                }
            }
                  break;
            case 7: {
                if (!list) {
                    cout << "Generate a list/array first!" << endl;
                    break;
                }
                if (notEqual) {
                    cout << "New list/array should be generated before getting (speed cannot be compared, elements are not equal)" << endl;
                    break;
                }
                if (list->length == 0) {
                    cout << "List/array has no elements!" << endl;
                    break;
                }
                int i = 0;
                do {
                    i = readValue<int>("Element index I: ");
                } while (i < 0 || i >= list->length);
                auto t1 = steady_clock::now();
                int v1 = listItem(list, i)->data;
                auto t2 = steady_clock::now();
                int v2 = dynarrItem(arr, i);
                auto t3 = steady_clock::now();
                auto list_t = duration_cast<nanoseconds>(t2 - t1);
                auto arr_t = duration_cast<nanoseconds>(t2 - t1);
                cout << "Element value in list: " << v1 << ", took " << list_t.count() << " nanoseconds." << endl;
                cout << "Element value in array: " << v2 << ", took " << arr_t.count() << " nanoseconds." << endl;
            }
                  break;
            case 8: {
                if (!list) {
                    cout << "Generate a list/array first!" << endl;
                    break;
                }
                if (notEqual) {
                    cout << "New list/array should be generated before removing (speed cannot be compared, elements are not equal)" << endl;
                    break;
                }
                if (list->length == 0) {
                    cout << "List/array has no elements!" << endl;
                    break;
                }
                int v = readValue<int>("Element value V: ");
                auto t1 = steady_clock::now();
                ListNode* prev = list->head;
                int nodeindex = 0;
                while (prev) {
                    if (prev->data == v)
                        break;
                    nodeindex++;
                    prev = prev->next;
                }
                auto t2 = steady_clock::now();
                int index = -1;
                for (int i = 0; i < arr->length; i++) {
                    int val = dynarrItem(arr, i);
                    if (val == v) {
                        index = i;
                        break;
                    }
                }
                auto t3 = steady_clock::now();
                auto list_t = duration_cast<nanoseconds>(t2 - t1);
                auto arr_t = duration_cast<nanoseconds>(t3 - t2);
                if (index == -1) {
                    cout << "Element not found" << endl; 
                } else {
                    cout << "Element index in list: " << nodeindex << ", took " << list_t.count() << " nanoseconds." << endl;
                    cout << "Element index in array: " << index << ", took " << arr_t.count() << " nanoseconds." << endl;
                }
            }
                  break;
            case 9: {
                /*
                *   Увеличьте каждое значение исходного динамического массива на случайное число (в диапазоне от 0 до 5).
                *   Добавьте в двусвязный список все положительные элементы динамического массива.
                */
                if (!list) {
                    cout << "Generate a list/array first!" << endl;
                    break;
                }
                auto t1 = steady_clock::now();
                for (int i = 0; i < arr->length; i++) {
                    arr->arr[i] += rand() % 10 - 5;
                    if (arr->arr[i] > 0)
                        listInsert(list, list->length + 1, arr->arr[i]);
                }
                auto t2 = steady_clock::now();
                notEqual = true;
                auto t = duration_cast<nanoseconds>(t2 - t1);
                cout << "Operation took " << t.count() << " nanoseconds." << endl;
            }
                  break;
            default:
                cout << "\nCategory with number " << choice << " does not exist." << endl;
                break;
        }
        system("pause");
    }
    if (list) {
        listClear(list);
        dynarrClear(arr);
    }
    return 0;
}