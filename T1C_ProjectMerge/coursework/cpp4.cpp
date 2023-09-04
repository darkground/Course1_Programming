#include <iostream>
#include <fstream>
#include "cpp4.h"

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

/*
*   Функция для ввода данных в терминал (как строку)
*   prompt - текст перед вводом
*   line - строка для заполнения
*   chars - максимальное количество входных данных
*/
void readLine(const char* prompt, char* line, int chars) {
    cout << prompt;
    if (!cin.getline(line, chars)) {
        // Так как определённый тип не требуется, то при остатке символов в буфере просто очищаем их
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

int cpp4main() {
    char sentence[512] = "";

    while (true) {
        system("cls");
        cout << "Project #4: String structure\n\n";
        cout << "Sentence: \"" << sentence << "\"\n";
        cout <<
            "\nChoose a category from below:\n"
            "0. Return to menu\n"
            "1. Read text from a file or text\n"
            "2. Fix text issues\n"
            "3. Individual task 1\n"
            "4. Individual task 2\n"
            "5. Linear Search\n"
            "6. Knuth-Morris-Pratt (KMP) Search\n\n";
        int choice = readValue<int>("Type a number to continue: ");
        cout << endl;
        switch (choice) {
        case 0:
            return 0;
        case 1:
            read(sentence);
            break;
        case 2: {
            char wordlist[50][11]{};
            tokenize(sentence, wordlist);
            for(int i = 0; wordlist[i][0]; i++)
                fixTypos(wordlist[i]);
            join(sentence, wordlist);
        }
            break;
        case 3:
            indTask1(sentence);
            break;
        case 4:
            indTask2(sentence);
            break;
        case 5: {
            char substring[512] {};
            readLine("Enter substring line: ", substring, 512);
            linearSearch(sentence, substring);
        }
            break;
        case 6: {
            char substring[512] {};
            readLine("Enter substring line: ", substring, 512);
            kmpSearch(sentence, substring);
        }
            break;
        default:
            cout << "\nCategory with number " << choice << " does not exist." << endl;
            break;
        }
        system("pause");
    }
}

/*
*   Считать ввод в строку.
*   sentence - Строка слов
*/
void read(char* sentence) {
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
            cout << "Complete." << endl;
            sentence[x] = '\0';
        }
            break;
        case 't':
            readLine("Enter text line: ", sentence, 512);
            break;
    }
}

/*
*   Конвертировать строку слов в массив слов (убрав лишние пробелы)
*   sentence - Строка слов
*   words - Массив слов
*/
void tokenize(char* sentence, char words[][11]) {
    char word[11]{};
    int wlx = 0; // Индекс списка слов
    int wx = 0; // Индекс буквы слов

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
    words[wlx][0] = '\0';
    if (wx != 0)
        scopy(words[wlx], word);
}

/*
*   Конвертировать список слов в строку слов.
*   sentence - Строка слов
*   words - Массив слов
*/
void join(char* sentence, char words[][11]) {
    sentence[0] = '\0';
    
    scopy(sentence, words[0]);
    for(int i = 1; words[i][0]; i++)
        sappend(sentence, words[i]);
}

/*
*   Исправить знаки и регистр в слове
*   char - Слово для исправления
*/
void fixTypos(char* word) {
    // Знаки
    unsigned int wlen = slen(word);
    if (isPunctuation(word[wlen - 1])) {
        int count = 1;
        char pType = word[wlen - 1];
        for (int i = wlen - 2; isPunctuation(word[i]) && i >= 0; i--)
            count++;
        if (count != 1 && (count != 3 || pType != '.'))
            word[wlen - count + 1] = '\0';
    }
    // Регистр
    for (int i = 1; word[i]; i++)
        word[i] = lower(word[i]);
}

/*
*   Индивидуальное задание 1:
*   Вывести на экран сначала все слова, содержащие только буквы,
*   Затем слова, содержащие только цифры, а потом слова, содержащие и буквы, и цифры.
*/
void indTask1(char* sentence) {
    char tokenized[50][11] {};
    tokenize(sentence, tokenized);

    cout << " -- Only Letters --\n";
    for(int i = 0; tokenized[i][0]; i++) {
        if (onlyLetters(tokenized[i]))
            cout << tokenized[i] << '\n';
    }
    cout << " -- Only Numbers --\n";
    for(int i = 0; tokenized[i][0]; i++) {
        if (onlyNumbers(tokenized[i]))
            cout << tokenized[i] << '\n';
    }
    cout << " -- Has Letters & Numbers --\n";
    for(int i = 0; tokenized[i][0]; i++) {
        if (onlyLettersNumbers(tokenized[i]))
            cout << tokenized[i] << '\n';
    }
}

/*
*   Индивидуальное задание 2:
*   Вывести все слова исходной последовательности на экран вертикально.
*/
void indTask2(char* sentence) {
    char tokenized[50][11] {};
    tokenize(sentence, tokenized);

    for(int i = 0; tokenized[i][0]; i++)
        cout << tokenized[i] << '\n';
}

void linearSearch(char* sentence, char* substring) {
    unsigned int stl = slen(sentence);
    unsigned int sbl = slen(substring);

    int i = 0;
    cout << "Matching indexes: ";
    while (i + sbl < stl + 1) {
        bool match = true;
        for (int j = i; j < i + sbl; j++)
            if (sentence[j] != substring[j - i]) {
                match = false;
                break;
            }
        if (match) {
            cout << i << ' ';
            i += sbl;
        }
        else i++;
    }
    cout << endl;
}

void kmpSearch(char* sentence, char* substring) {
    int prefixArray[512] {};

    unsigned int stl = slen(sentence);
    unsigned int sbl = slen(substring);

    int i = 1, j = 0; //Индекс прохода и курсор
    /*
    Если Ai != Aj, тогда, если j = 0, то px[i] = 0; i++
        иначе, j = px[j - 1]
    Иначе px[i] = j + 1; i++; j++
    */
    while (i < sbl) {
        if (substring[i] == substring[j]) {
            prefixArray[i] = j + 1; //Префиксы и суффиксы совпали, запись значения
            i++; j++;
        }
        else if (j == 0) { //Префиксы и суффиксы не совпали, курсор в начале, сброс 
            prefixArray[i] = 0;
            i++;
        }
        else j = prefixArray[j - 1]; //Префиксы и суффиксы не совпали, установка курсора на прошлое успешное совпадение, сброс
    }

    int ix = -1, k = 0, l = 0;
    cout << "Matching indexes: ";
    /*
    Если Sk = Pl, то
        k++; l++;
        Если l = n, то есть совпадение
    Иначе Если l = 0, то
            k++;
            Если k = m, то совпадений нет
          Иначе l = px[l - 1]
    */
    while (k < stl) {
        if (sentence[k] == substring[l]) {
            k++; l++;
            if (l == sbl) {
                cout << k - sbl << ' ';
                l = 0;
            }
        }
        else {
            if (l == 0) k++;
            else l = prefixArray[l - 1];
        }   
    }
    cout << endl;
}

/*
*   Проверить содержит ли строка только буквы.
*   str - Строка для проверки
*/
bool onlyLetters(char* str) {
    for (int i = 0; str[i]; i++) {
        if ((str[i] < 65 || str[i] > 90) && (str[i] < 97 || str[i] > 122))
            return false;
    }
    return true;
}

/*
*   Проверить содержит ли строка только цифры.
*   str - Строка для проверки
*/
bool onlyNumbers(char* str) {
    for (int i = 0; str[i]; i++) {
        if (str[i] < 48 || str[i] > 57)
            return false;
    }
    return true;
}

/*
*   Проверить содержит ли строка только буквы.
*   str - Строка для проверки
*/
bool onlyLettersNumbers(char* str) {
    bool hadLetter = false;
    bool hadNumber = false;

    for (int i = 0; str[i]; i++) {
        if ((str[i] >= 65 && str[i] <= 90) || (str[i] >= 97 && str[i] <= 122))
            hadLetter = true;
        if (str[i] >= 48 && str[i] <= 57)
            hadNumber = true;
    }

    return hadLetter && hadNumber;
}

/*
*   Перевод в нижний регистр
*   c - Символ для перевода
*/
char lower(char c) {
    // https://www.asciitable.com/asciifull.gif
    if (c >= 65 && c <= 90)
        return c + 32; 
    return c;
}

/*
*   Определить, является ли символ знаком пунктуации
*   c - Символ для проверки
*/
bool isPunctuation(char c) {
    return c == '.' || c == ',' || c == '!' || c == '?';
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
    unsigned i = 0;
    for (; str_from[i]; ++i)
        str_to[i] = str_from[i];
    str_to[i] = '\0';
}

/*
*   Скопировать символы одной строки в конец другой.
*   str_to - Строка, в которую будут добавляться символы.
*   str_from - Строка, из которой будут копироваться символы.
*/
void sappend(char* str_to, char* str_from) {
    unsigned j = slen(str_to);
    str_to[j++] = ' ';
    for (unsigned i = 0; str_from[i]; ++i, ++j)
        str_to[j] = str_from[i];
    str_to[j] = '\0';
}

/*
*   Сравнить две строки.
*   str1 - Строка для сравнения 1.
*   str2 - Строка для сравнения 2.
*/
bool sequal(char* str1, char* str2) {
    for (unsigned i = 0; str1[i]; ++i)
        if (str1[i] != str2[i])
            return false;
    return true;
}