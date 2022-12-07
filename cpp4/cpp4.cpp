#include <iostream>
#include <fstream>

const int LETTERS_MAX = 10; 
const int WORDS_MAX = 50;

unsigned int slen(char*);
void scopy(char*, char*);

void printSentence(bool, char[], char[][LETTERS_MAX+1]);
void readText(char[]);
void readWords(char[], char[][LETTERS_MAX+1]);

using namespace std;

/*
*   Функция для ввода данных в терминал
*   При вызове функции нужно указать получаемые данные в скобках,
*   т.е. readValue<int>() - получить число.
*   prompt - текст перед вводом
*/

template <typename T>
T readValue(const char* prompt) {
    T value;
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

int main()
{
    char sentence[512] = "";
    char wordlist[WORDS_MAX][LETTERS_MAX+1]{};
    bool split = false;

    while (true) {
        system("cls");
        printSentence(split, sentence, wordlist);
        cout <<
            "\nChoose a category from below:\n"
            "0. Exit\n"
            "1. Read text from a file or text\n"
            "2. Fix text issues\n"
            "3. Individual task 1\n"
            "4. Individual task 2\n\n";
        int choice = readValue<int>("Type a number to continue: ");
        cout << endl;
        switch (choice) {
        case 0:
            return 0;
        case 1:
            readText(sentence);
            split = false;
            break;
        case 2:
            readWords(sentence, wordlist);
            split = true;
            break;
        case 3:
            break;
        case 4:
            break;
        default:
            cout << "\nCategory with number " << choice << " does not exist." << endl;
        }
        system("pause");
    }
    return 0;
}

/*
*   Вывести строку на экран.
*   split - Флаг выполненного второго шага (устранены ли проблемы)
*   sentence - Строка для вывода в случае split = true
*   words - Массив для вывода в случае split = false
*/
void printSentence(bool split, char sentence[], char words[][LETTERS_MAX+1]) {
    cout << "State: " << (split ? "FIXED" : "UNREDACTED") << "\n";
    if (split) {

        cout << "Sentence: \"";
        for(int i = 0; words[i][0]; i++) {
            if (i != 0) 
                cout << ' ';
            cout << words[i]; 
        }
        cout << "\"\n";
    } else
        cout << "Sentence: \"" << sentence << "\"\n";
}

/*
*   Считать ввод в строку.
*   sentence - Строка слов
*/
void readText(char sentence[]) {
    char choice = ' ';
    do {
        choice = readValue<char>("Where to read from? (f)ile or (t)ext: ");
    } while (choice != 'f' && choice != 't');
    switch (choice)
    {
        case 'f': {
            ifstream ifs = ifstream("input.txt");
            if (!ifs.is_open()) break;
            char c = ' ';
            int x = 0;
            while (ifs.get(c))
                sentence[x++] = c;
            cout << "Read file.";
            sentence[x] = '\0';
        }
            break;
        case 't':
            cout << "Enter text line: ";
            cin.getline(sentence, 512);
            break;
    }
}

/*
*   Конвертировать строку слов в массив слов (убрав лишние пробелы)
*   sentence - Строка слов
*   words - Массив слов
*/
void readWords(char sentence[], char words[][LETTERS_MAX+1]) {
    char word[LETTERS_MAX + 1]{};
    int wlx = 0;
    int wx = 0;

    for (int x = 0; sentence[x]; x++) {
        if (wx != 0 && sentence[x] == ' ') {
            word[wx] = '\0';
            scopy(words[wlx++], word);
            wx = 0;
        }
        if (sentence[x] != ' ')
            word[wx++] = sentence[x];
    }
    
    word[wx] = '\0';
    if (wx != 0)
        scopy(words[wlx], word);
}

/*
*   Подсчёт длины строки.
*   str - Строка, длину которой необходимо посчитать. 
*/
unsigned int slen(char* str) {
    unsigned L = 0;
    while (str[L])
        ++L;
    return L;
}

/*
*   Скопировать символы одной строки в другую.
*   str_to - Строка, в которую будут копироваться символы.
*   str_from - Строка, из которой будут копироваться символы. 
*/
void scopy(char* str_to, char* str_from) {
    unsigned j = slen(str_to);
    for (unsigned i = 0; str_from[i]; ++i, ++j)
        str_to[j] = str_from[i];
    str_to[++j] = '\0';
}
