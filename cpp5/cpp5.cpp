#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct Student {
    string fullname;
    char sex;
    
    string faculty;
    int courseId;
    int group;
    int id;
    int grades[8];
    
    string update_date;
};

/*
*   Функция для ввода данных в терминал
*   При вызове функции нужно указать получаемые данные в скобках,
*   т.е. readValue<int>() - получить число.
*   prompt - текст перед вводом
*   value - значение для заполнения
*/
template <typename T>
T readValue(const char* prompt = "") {
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
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
    }
}

/*
*   Функция для ввода данных в терминал (как строку)
*   prompt - текст перед вводом
*   line - строка для заполнения
*/
void readLine(const char* prompt, string* line) {
    cout << prompt;
    if (!getline(cin, *line)) {
        // Так как определённый тип не требуется, то при остатке символов в буфере просто очищаем их
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// Создать 
void entryCreate() {
    cout << "Creating new entry.\n";
    struct tm newtime;
    char buf[64] {};
    time_t now = time(0);
    localtime_s(&newtime,&now);
    asctime_s(buf, &newtime);

	Student student;
    readLine("Full name: ", &student.fullname);
    student.sex = readValue<char>("Sex [F/M]: ");
    readLine("Faculty: ", &student.faculty);
    student.courseId = readValue<int>("Course Number: ");
    student.group = readValue<int>("Group: ");
    student.id = readValue<int>("Id in list: ");
    for(int i = 0; i < 8; i++) {
        cout << "Term grade #" << i << ": ";
        student.grades[i] = readValue<int>();
    }
    student.update_date = buf;
	
    bool hasFailure = false;
	for (int i = 0; i < 8; i++)
	{
		if (student.grades[i] == 2) {
            hasFailure = true;
            break;
        }
	}
	if (!hasFailure)
	{
		ofstream database;
		database.open("students.txt", ios::app); 
		if (!database.is_open())
			cout << '\n' << "Database write error!";
		else
		{
			database << student.fullname << '\n';
			database << student.sex << '\n';
            database << student.faculty << '\n';
            database << student.courseId << '\n';
			database << student.group << '\n';
			database << student.id << '\n';
			for (int i = 0; i < 8; i++)
				database << student.grades[i] << " ";
			database << '\n' << student.update_date;
			database.close();
			cout << '\n' << "Profile successfully written to databse.\n";
		}
	}
	else
        cout << '\n' << "This student will be expelled. The profile will not be written to the database.\n";
}

int countEntries() {
	ifstream database("students.txt");
	if (database.is_open())
	{
		int lines = 0;
		string data;
		while (!database.eof())
		{
			getline(database, data);
			lines++;
		}
		database.close();
		return lines / 8;
	}
	else return 0;
}

int main()
{
    while (true) {
        system("cls");
        cout << "Database has " << countEntries() << " students.\n";
        cout <<
            "\nChoose a category from below:\n"
            "0. Exit\n"
            "1. Create student entry\n\n";
        int choice = readValue<int>("Type a number to continue: ");
        cout << endl;
        switch (choice) {
            case 0:
                return 0;
            case 1:
                entryCreate();
                break;
            default:
                cout << "\nCategory with number " << choice << " does not exist." << endl;
                break;
        }
        system("pause");
    }
    return 0;
}
