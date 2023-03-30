#include <iostream>
#include "list.h"
#include <chrono>

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

List* step1_random(unsigned n) {
    List* list = listCreate();
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

    return list;
}

List* step1_input() {
    cout << "Input numbers line by line, finish by typing any non-digit character (e.g. \"a\").\n";
    
    List* list = listCreate();
    int val;
    ListNode* prev = 0;
    while (true) {
        cin >> val;
        if (cin.fail())
            break;
        if (list->length == 0) {
            prev = new ListNode;
            prev->data = val;
            list->head = prev;
        } else {
            ListNode* curr = new ListNode;
            curr->data = val;
            prev->next = curr;
            curr->prev = prev;
            prev = curr;
        }
        list->length++;
    }
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return list;
}

int main()
{
    List* list = 0;
    while (true) {
        system("cls");
        printList(list);
        cout <<
            "\nChoose a category from below:\n"
            "0. Exit\n"
            "1. Create list with Pre-Defined N (Random numbers)\n"
            "2. Create list until stopped (Input numbers)\n"
            "3. Insert element into list by index\n"
            "4. Remove element from list by index\n"
            "5. Swap elements in list by index\n\n";
        int choice = readValue<int>("Type a number to continue: ");
        cout << endl;
        switch (choice) {
            case 0:
                return 0;
            case 1: {
                int n = 0;
                do {
                    n = readValue<int>("Element count N: ");
                } while (n < 0);
                auto t1 = steady_clock::now();
                list = step1_random(n);
                auto t2 = steady_clock::now();
                auto result = duration_cast<nanoseconds>(t2 - t1);
                cout << "List generation complete in " << result.count() << " nanoseconds." << endl;
            }
                break;
            case 2:
                list = step1_input();
                cout << "List generation complete." << endl;
                break;
            default:
                cout << "\nCategory with number " << choice << " does not exist." << endl;
                break;
        }
        system("pause");
    }
    if (list)
        listClear(list);
    return 0;
}