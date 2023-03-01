#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

struct Student {
    string fullname;
    char sex;
    int age;
    
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

// Внести данные о студенте
void entryCreate() {
    cout << "Creating new entry.\n";
    struct tm newtime;
    char buf[64] {};
    time_t now = time(0);
    localtime_s(&newtime,&now);
    asctime_s(buf, &newtime);

	Student student;
    readLine("Full name: ", &student.fullname);
    student.sex = ' ';
    do {
        student.sex = readValue<char>("Sex [F/M]: ");
    } while (student.sex != 'F' && student.sex != 'M');
    do {
        student.age = readValue<int>("Age: ");
    } while (student.age < 1);
    readLine("Faculty: ", &student.faculty);
    do {
        student.courseId = readValue<int>("Course Number [1-5]: ");
    } while (student.courseId < 1 || student.courseId > 5);
    student.group = readValue<int>("Group: ");
    do {
        student.id = readValue<int>("Id in list: ");
    } while (student.id < 0);
    for(int i = 0; i < 8; i++) {
        cout << "Term grade #" << i + 1 << (i < 3 ? " (exam)" : "") << ": ";
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
			cout << "Database write error!\n";
		else
		{
			database << student.fullname << '\n';
			database << student.sex << '\n';
			database << student.age << '\n';
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
		return lines / 9;
	}
	else return 0;
}

void printEntries() {
	ifstream database("students.txt");
	if (database.is_open())
	{
        cout 
            << "Faculty  Course Group  Id   Sex  Age  Name                     Last Updated & Grades\n"
            << "------------------------------------------------------------------------------------\n";

        for(int i = 0; i < countEntries(); i++) {
            Student student;
            getline(database, student.fullname, '\n');
            database >> student.sex;
            database >> student.age >> ws;
            getline(database, student.faculty, '\n');
            database >> student.courseId;
            database >> student.group;
            database >> student.id;
            for (int i = 0; i < 8; i++)
                database >> student.grades[i];
            database >> ws;
            getline(database, student.update_date, '\n');

            cout 
                << setw(8) << left << student.faculty << ' '
                << setw(6) << student.courseId << ' '
                << setw(6) << student.group << ' '
                << setw(4) << student.id << ' '
                << setw(4) << student.sex << ' '
                << setw(4) << student.age << ' '
                << setw(24) << student.fullname << ' '
                << setw(24) << student.update_date << ' ';
            for(int i = 0; i < 8; i++)
                cout << ' ' << student.grades[i];
            cout << '\n';
        }
        database.close();
	}
	else
        cout << "Database read error!\n";
}

int main()
{
    while (true) {
        system("cls");
        cout << "Database has " << countEntries() << " students.\n";
        cout <<
            "\nChoose a category from below:\n"
            "0. Exit\n"
            "1. View all entries\n"
            "2. Create student entry\n\n";
        int choice = readValue<int>("Type a number to continue: ");
        cout << endl;
        switch (choice) {
            case 0:
                return 0;
            case 1:
                printEntries();
                break;
            case 2:
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
