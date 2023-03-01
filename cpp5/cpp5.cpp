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

	Student student;
    readLine("Full name: ", &student.fullname);
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

    struct tm newtime;
    char buf[64] {};
    time_t now = time(0);
    localtime_s(&newtime,&now);
    asctime_s(buf, &newtime);
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

// Изменить данные студента
void entryEdit() {
    cout << "Editing existing entry.\n";
    int c = countEntries();
    int id;
    do {
        id = readValue<int>("Enter ID: ");
    } while (id < 0 || id > c);

    ifstream database("students.txt");

    if (database.is_open())
	{
        Student student;
        for(int i = 0; i <= id; i++) {
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
        }
        database.close();

        cout << "Change name (" << student.fullname << ") to: ";
        readLine("", &student.fullname);
        do {
            cout << "Change sex (" << student.sex << ") to: ";
            student.sex = readValue<char>();
        } while (student.sex != 'F' && student.sex != 'M');
        do {
            cout << "Change age (" << student.age << ") to: ";
            student.age = readValue<int>();
        } while (student.age < 1);
        cout << "Change faculty (" << student.faculty << ") to: ";
        readLine("", &student.faculty);
        do {
            cout << "Change course number (" << student.courseId << ") to: ";
            student.courseId = readValue<int>();
        } while (student.courseId < 1 || student.courseId > 5);
        cout << "Change group (" << student.group << ") to: ";
        student.group = readValue<int>();
        do {
            cout << "Change id in list (" << student.id << ") to: ";
            student.id = readValue<int>();
        } while (student.id < 0);
        for(int i = 0; i < 8; i++) {
            cout << "Change term grade #" << i + 1 << " (" << student.grades[i] << ") to: ";
            student.grades[i] = readValue<int>();
        }

        struct tm newtime;
        char buf[64] {};
        time_t now = time(0);
        localtime_s(&newtime,&now);
        asctime_s(buf, &newtime);
        student.update_date = buf;

        ifstream database("students.txt");
        ofstream swap("temp.txt"); 
		if (!database.is_open() || !swap.is_open())
			cout << "Database write error!\n";
		else
		{   string line;
            int curLine = 0;
            while (getline(database, line)) {
                if(curLine / 9 == id) {
                    for(int i = 0; i < 8; i++)
                        getline(database, line); // удаляем старые данные из файла
                    swap << student.fullname << '\n';
                    swap << student.sex << '\n';
                    swap << student.age << '\n';
                    swap << student.faculty << '\n';
                    swap << student.courseId << '\n';
                    swap << student.group << '\n';
                    swap << student.id << '\n';
                    for (int i = 0; i < 8; i++)
                        swap << student.grades[i] << " ";
                    swap << '\n' << student.update_date;
                    curLine += 9;
                } else {
                    swap << line << '\n';
                    curLine++;
                }
            }

			database.close();
            swap.close();
            remove("students.txt");
            rename("temp.txt", "students.txt");
            cout << '\n' << "Profile successfully updated.\n";
		}
	}
	else
        cout << "Database read error!\n";
}

void printEntries() {
	ifstream database("students.txt");
	if (database.is_open())
	{
        cout 
            << "ID  Faculty  Course Group  Id   Sex  Age  Name                     Last Updated & Grades\n"
            << "----------------------------------------------------------------------------------------\n";

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
                << setw(3) << left << i << ' ' 
                << setw(8) << student.faculty << ' '
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
            "2. Create student entry\n";
            "3. Edit student entry\n\n";
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
            case 3:
                entryEdit();
                break;
            default:
                cout << "\nCategory with number " << choice << " does not exist." << endl;
                break;
        }
        system("pause");
    }
    return 0;
}
