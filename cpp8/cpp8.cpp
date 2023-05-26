#include <iostream>
#include <fstream>
#include <chrono>
#include "bt.h"
#include "avl.h"

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

// - BT --------------------------------------------------------------

void walkBT(BTNode*& root) {
    system("cls");
    cout <<
        "Walk:\n"
        "1. Straight walk\n"
        "2. Reverse walk\n"
        "3. Symmetrical walk\n\n";
    int choice = readValue<int>("Type a number to continue: ");
    switch(choice) {
        case 1:
            strwBT(root);
            cout << endl;
            break;
        case 2:
            revwBT(root);
            cout << endl;
            break;
        case 3:
            symwBT(root);
            cout << endl;
            break;
    }
}

void fillBT(BTNode*& root) {
    system("cls");
    cout <<
        "Fill:\n"
        "1. Create with random values\n"
        "2. Create with manual values\n"
        "3. Read from file\n\n";
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
        case 3: {
            destroyBT(root);
            root = NULL;
            int n = readValue<int>("Input N: ");
            ifstream ifs("bt.txt");
            if (ifs) {
                for (int i = 0; i < n && !ifs.eof(); i++) {
                    int inp;
                    ifs >> inp;
                    addBT(inp, root);
                }
                ifs.close();
            }
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
            case 3: {
                int n = readValue<int>("Input a number to insert: ");
                auto t1 = steady_clock::now();
                addBT(n, bt);
                auto t2 = steady_clock::now();
                auto result = duration_cast<nanoseconds>(t2 - t1);
                cout << "Inserted in " << result.count() << " nanoseconds." << endl;
                break;
            }
            case 4: {
                int n = readValue<int>("Input a number to delete: ");
                auto t1 = steady_clock::now();
                deleteBT(n, bt);
                auto t2 = steady_clock::now();
                auto result = duration_cast<nanoseconds>(t2 - t1);
                cout << "Deleted in " << result.count() << " nanoseconds." << endl;
                break;
            }
            case 5: {
                int n = readValue<int>("Input a number to search: ");
                auto t1 = steady_clock::now();
                BTNode* node = searchBT(n, bt);
                auto t2 = steady_clock::now();
                auto result = duration_cast<nanoseconds>(t2 - t1);
                if (node != NULL)
                    cout << "Element found: " << node->value << " (" << result.count() << " nanoseconds)" << endl;
                else
                    cout << "Element not found (" << result.count() << " nanoseconds)" << endl;
                break;
            }
            case 6:
                walkBT(bt);
                break;
            default:
                cout << "\nCategory with number " << choice << " does not exist." << endl;
                break;
        }
        system("pause");
    }
}

// - AVL --------------------------------------------------------------

void fillAVL(AVLNode*& root) {
    system("cls");
    cout <<
        "Fill:\n"
        "1. Create with random values\n"
        "2. Create with manual values\n"
        "2. Create from file\n\n";
    int choice = readValue<int>("Type a number to continue: ");
    switch(choice) {
        case 1: {
            destroyAVL(root);
            root = NULL;
            int n = readValue<int>("Input N: ");
            for(int i = 0; i < n; i++){
                int r = rand() % 200 - 99;
                addAVL(r, root);
            }
            break;
        }
        case 2: {
            destroyAVL(root);
            root = NULL;
            cout << "Input numbers line by line, finish by typing any non-digit character (e.g. \"a\").\n";
            int val;
            while (true) {
                cin >> val;
                if (cin.fail())
                    break;
                addAVL(val, root);
            }
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }
        case 3: {
            destroyAVL(root);
            root = NULL;
            int n = readValue<int>("Input N: ");
            ifstream ifs("bt.txt");
            if (ifs) {
                for (int i = 0; i < n && !ifs.eof(); i++) {
                    int inp;
                    ifs >> inp;
                    addAVL(inp, root);
                }
                ifs.close();
            }
            break;
        }
    }
}

void avlmenu() {
    AVLNode* avl = NULL;
    while (true) {
        system("cls");
        cout <<
            "AVL Trees - Choose a category from below:\n"
            "0. Back\n"
            "1. Create AVL\n"
            "2. Print AVL Tree\n"
            "3. Insert element into BST\n"
            "4. Delete element from BST\n"
            "5. Find element in BST\n"
            "6. Task generation\n\n";
        int choice = readValue<int>("Type a number to continue: ");
        cout << endl;
        switch (choice) {
            case 0:
                return;
			case 1:
                fillAVL(avl);
                break;
            case 2:
                printAVL(avl);
                break;
            case 3: {
                int n = readValue<int>("Input a number to insert: ");
                auto t1 = steady_clock::now();
                addAVL(n, avl);
                auto t2 = steady_clock::now();
                auto result = duration_cast<nanoseconds>(t2 - t1);
                cout << "Inserted in " << result.count() << " nanoseconds." << endl;
                break;
            }
            case 4: {
                int n = readValue<int>("Input a number to delete: ");
                auto t1 = steady_clock::now();
                avl = deleteAVL(n, avl);
                auto t2 = steady_clock::now();
                auto result = duration_cast<nanoseconds>(t2 - t1);
                cout << "Deleted in " << result.count() << " nanoseconds." << endl;
                break;
            }
            case 5: {
                int n = readValue<int>("Input a number to search: ");
                auto t1 = steady_clock::now();
                AVLNode* node = searchAVL(n, avl);
                auto t2 = steady_clock::now();
                auto result = duration_cast<nanoseconds>(t2 - t1);
                if (node != NULL)
                    cout << "Element found: " << node->value << " (" << result.count() << " nanoseconds)" << endl;
                else
                    cout << "Element not found (" << result.count() << " nanoseconds)" << endl;
                break;
            }
            default:
                cout << "\nCategory with number " << choice << " does not exist." << endl;
                break;
        }
        system("pause");
    }
}

// -     --------------------------------------------------------------

int main()
{
    srand(time(NULL));
	while (true) {
        system("cls");
        cout <<
            "Choose tree type from below:\n"
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
            case 2:
                avlmenu();
            default:
                cout << "\nCategory with number " << choice << " does not exist." << endl;
                break;
        }
    }
}