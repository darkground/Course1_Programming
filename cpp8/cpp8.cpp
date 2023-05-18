#include <iostream>
#include "bt.h"

using namespace std;

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

void fillBT(BTNode*& root) {
    system("cls");
    cout <<
        "Fill:\n"
        "0. Back\n"
        "1. Create with random values\n"
        "2. Create with manual values\n\n";
    int choice = readValue<int>("Type a number to continue: ");
    switch(choice) {
        case 1: {
            destroyBT(root);
            root = NULL;
            int n = readValue<int>("Input N: ");
            for(int i = 0; i < n; i++){
                int r = rand() % 200 - 99;
                addBT(r, root);
            }
            break;
        }
        case 2: {
            destroyBT(root);
            root = NULL;
            cout << "Input numbers line by line, finish by typing any non-digit character (e.g. \"a\").\n";
            int val;
            while (true) {
                cin >> val;
                if (cin.fail())
                    break;
                addBT(val, root);
            }
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }
    }
}

void bstmenu() {
    BTNode* bt = NULL;
    while (true) {
        system("cls");
        cout <<
            "Binary Search Trees - Choose a category from below:\n"
            "0. Back\n"
            "1. Create BST\n"
            "2. Print BST Tree\n"
            "3. Insert element into BST\n"
            "4. Delete element from BST\n"
            "5. Find element in BST\n"
            "6. BST walk\n"
            "7. Task generation\n\n";
        int choice = readValue<int>("Type a number to continue: ");
        cout << endl;
        switch (choice) {
            case 0:
                return;
			case 1:
                fillBT(bt);
                break;
            case 2:
                printBT(bt);
                break;
            default:
                cout << "\nCategory with number " << choice << " does not exist." << endl;
                break;
        }
        system("pause");
    }
}

int main()
{
	while (true) {
        system("cls");
        cout <<
            "Choose a category from below:\n"
            "0. Exit\n"
            "1. Binary Search Trees\n"
            "2. AVL Trees\n\n";
        int choice = readValue<int>("Type a number to continue: ");
        cout << endl;
        switch (choice) {
            case 0:
                return 0;
			case 1:
                bstmenu();
                break;
            default:
                cout << "\nCategory with number " << choice << " does not exist." << endl;
                break;
        }
    }
}