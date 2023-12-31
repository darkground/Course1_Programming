﻿#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

struct Student {
    string fullname;
    char sex = ' ';
    int age = 0;
    
    string faculty;
    int courseId = 0;
    int group = 0;
    int id = 0;
    int grades[8] {0, 0, 0, 0, 0, 0, 0, 0};
    float avg = 0.0f;
    
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
    T value = NULL;
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

// Подсчёт количества студентов в базе
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
    int c = countEntries();
    if (c == 0) {
        cout << "Database has no entries!\n";
        return;
    }

    cout << "Editing existing entry.\n";
    int id;
    do {
        id = readValue<int>("Enter ID: ");
    } while (id < 0 || id > c);

    ifstream database("students.txt");

    if (database.is_open())
	{
        Student* students = new Student[c];
        for(int i = 0; i < c; i++) {
            getline(database, students[i].fullname);
            database >> students[i].sex;
            database >> students[i].age >> ws;
            getline(database, students[i].faculty);
            database >> students[i].courseId;
            database >> students[i].group;
            database >> students[i].id;
            for (int j = 0; j < 8; j++)
                database >> students[i].grades[j];
            database >> ws;
            getline(database, students[i].update_date);
            students[i].update_date.push_back('\n'); // из-за того, что asctime добавляет \n в конец
        }
        database.close();

        cout << "Change name (" << students[id].fullname << ") to: ";
        readLine("", &students[id].fullname);
        do {
            cout << "Change sex (" << students[id].sex << ") to: ";
            students[id].sex = readValue<char>();
        } while (students[id].sex != 'F' && students[id].sex != 'M');
        do {
            cout << "Change age (" << students[id].age << ") to: ";
            students[id].age = readValue<int>();
        } while (students[id].age < 1);
        cout << "Change faculty (" << students[id].faculty << ") to: ";
        readLine("", &students[id].faculty);
        do {
            cout << "Change course number (" << students[id].courseId << ") to: ";
            students[id].courseId = readValue<int>();
        } while (students[id].courseId < 1 || students[id].courseId > 5);
        cout << "Change group (" << students[id].group << ") to: ";
        students[id].group = readValue<int>();
        do {
            cout << "Change id in list (" << students[id].id << ") to: ";
            students[id].id = readValue<int>();
        } while (students[id].id < 0);
        for(int i = 0; i < 8; i++) {
            cout << "Change term grade #" << i + 1 << " (" << students[id].grades[i] << ") to: ";
            students[id].grades[i] = readValue<int>();
        }

        struct tm newtime;
        char buf[64] {};
        time_t now = time(0);
        localtime_s(&newtime,&now);
        asctime_s(buf, &newtime);
        students[id].update_date = buf;

        ofstream database("students.txt"); 
		if (!database.is_open())
			cout << "Database write error!\n";
		else
		{
            for(int i = 0; i < c; i++) {
                database << students[i].fullname << '\n';
                database << students[i].sex << '\n';
                database << students[i].age << '\n';
                database << students[i].faculty << '\n';
                database << students[i].courseId << '\n';
                database << students[i].group << '\n';
                database << students[i].id << '\n';
                for (int j = 0; j < 8; j++)
                    database << students[i].grades[j] << " ";
                database << '\n' << students[i].update_date;
            }
            database.close();
            cout << '\n' << "Profile successfully updated.\n";
		}
        delete[] students;
	}
	else
        cout << "Database read error!\n";
}

// Просмотр студентов из определенной группы
void viewGroupEntries() {
    int c = countEntries();
    if (c == 0) {
        cout << "Database has no entries!\n";
        return;
    }

    cout << "Viewing entries from group.\n";
    int group = readValue<int>("Enter group: ");

    ifstream database("students.txt");

    if (database.is_open())
	{
        Student* students = new Student[c];
        for(int i = 0; i < c; i++) {
            getline(database, students[i].fullname);
            database >> students[i].sex;
            database >> students[i].age >> ws;
            getline(database, students[i].faculty);
            database >> students[i].courseId;
            database >> students[i].group;
            database >> students[i].id;
            for (int j = 0; j < 8; j++)
                database >> students[i].grades[j];
            database >> ws;
            getline(database, students[i].update_date);
        }
        database.close();

        cout 
            << "ID  Faculty  Course Group  Id   Sex  Age  Name                     Last Updated & Grades\n"
            << "----------------------------------------------------------------------------------------\n";

        int t = 0;
        for(int i = 0; i < c; i++) {
            if (students[i].group == group) {
                t++;
                cout
                    << setw(3) << left << i << ' '
                    << setw(8) << students[i].faculty << ' '
                    << setw(6) << students[i].courseId << ' '
                    << setw(6) << students[i].group << ' '
                    << setw(4) << students[i].id << ' '
                    << setw(4) << students[i].sex << ' '
                    << setw(4) << students[i].age << ' '
                    << setw(24) << students[i].fullname << ' '
                    << setw(24) << students[i].update_date << ' ';
                for(int j = 0; j < 8; j++)
                    cout << ' ' << students[i].grades[j];
                cout << '\n';
            }
        }
        if (t == 0)
            cout << "No students found.\n";

        delete[] students;
	}
	else
        cout << "Database read error!\n";
}

// Просмотр 5 лучших студентов с средней оценкой за прошедную сессию
void top5() {
    int c = countEntries();
    if (c == 0) {
        cout << "Database has no entries!\n";
        return;
    }

    cout << "Top 5 students with highest average grade.\n";
    ifstream database("students.txt");

    if (database.is_open())
	{
        Student* students = new Student[c];
        for(int i = 0; i < c; i++) {
            int s = 0;

            getline(database, students[i].fullname);
            database >> students[i].sex;
            database >> students[i].age >> ws;
            getline(database, students[i].faculty);
            database >> students[i].courseId;
            database >> students[i].group;
            database >> students[i].id;
            for (int j = 0; j < 8; j++) {
                database >> students[i].grades[j];
                s += students[i].grades[j];
            }
            database >> ws;
            getline(database, students[i].update_date);
            students[i].avg = (float)s / 8;
        }
        database.close();

        for (int i = 0; i < c - 1; i++)
            for (int j = 0; j < c - i - 1; j++)
                if (students[j].avg < students[j+1].avg)
                    swap(students[j], students[j + 1]);

        for(int i = 0; i < min(c, 5); i++) {
            cout << "Top " << i + 1 << ": " << students[i].group << " " << students[i].fullname << " with average " << setprecision(3) << students[i].avg << " -";
            for(int j = 0; j < 8; j++)
                cout << ' ' << students[i].grades[j];
            cout << '\n';
        }

        delete[] students;
	}
	else
        cout << "Database read error!\n";
}

// Подсчёт м/ж
void separateBySex() {
    int c = countEntries();
    if (c == 0) {
        cout << "Database has no entries!\n";
        return;
    }

    ifstream database("students.txt");

    if (database.is_open())
	{
        Student* students = new Student[c];
        int m = 0, f = 0;
        for(int i = 0; i < c; i++) {
            int s = 0;

            getline(database, students[i].fullname);
            database >> students[i].sex;
            database >> students[i].age >> ws;
            getline(database, students[i].faculty);
            database >> students[i].courseId;
            database >> students[i].group;
            database >> students[i].id;
            for (int j = 0; j < 8; j++) {
                database >> students[i].grades[j];
                s += students[i].grades[j];
            }
            database >> ws;
            getline(database, students[i].update_date);
            students[i].avg = (float)s / 8;
        }
        database.close();

        for (int i = 0; i < c; i++){
            if (students[i].sex == 'M')
                m++;
            else
                f++;
        }

        cout << "There is " << m << " male students and " << f << " female students.\n";

        delete[] students;
	}
	else
        cout << "Database read error!\n";
}


// Фильтрация студентов по их худщей оценке
void viewByGrades(int lowest = 3) {
    int c = countEntries();
    if (c == 0) {
        cout << "Database has no entries!\n";
        return;
    }

    cout << "Viewing students with lowest grade - " << lowest << ".\n";
    ifstream database("students.txt");

    if (database.is_open())
	{
        Student* students = new Student[c];
        for(int i = 0; i < c; i++) {
            getline(database, students[i].fullname);
            database >> students[i].sex;
            database >> students[i].age >> ws;
            getline(database, students[i].faculty);
            database >> students[i].courseId;
            database >> students[i].group;
            database >> students[i].id;
            for (int j = 0; j < 8; j++)
                database >> students[i].grades[j];
            database >> ws;
            getline(database, students[i].update_date);
        }
        database.close();

        cout 
            << "ID  Faculty  Course Group  Id   Sex  Age  Name                     Last Updated & Grades\n"
            << "----------------------------------------------------------------------------------------\n";

        int t = 0;
        for(int i = 0; i < c; i++) {
            int low = 5;
            for (int j = 0; j < 8; j++)
                low = min(students[i].grades[j], low);
            
            if (low == lowest) {
                t++;
                cout
                    << setw(3) << left << i << ' '
                    << setw(8) << students[i].faculty << ' '
                    << setw(6) << students[i].courseId << ' '
                    << setw(6) << students[i].group << ' '
                    << setw(4) << students[i].id << ' '
                    << setw(4) << students[i].sex << ' '
                    << setw(4) << students[i].age << ' '
                    << setw(24) << students[i].fullname << ' '
                    << setw(24) << students[i].update_date << ' ';
                for(int j = 0; j < 8; j++)
                    cout << ' ' << students[i].grades[j];
                cout << '\n';
            }
        }
        if (t == 0)
            cout << "No students found.\n";

        delete[] students;
	}
	else
        cout << "Database read error!\n";
}

// Фильтрация студентов по их номеру в списке
void viewById() {
    int c = countEntries();
    if (c == 0) {
        cout << "Database has no entries!\n";
        return;
    }

    cout << "Viewing students with specific IDs in list.\n";
    int eId = readValue<int>("Enter list ID: ");

    ifstream database("students.txt");

    if (database.is_open())
	{
        Student* students = new Student[c];
        for(int i = 0; i < c; i++) {
            getline(database, students[i].fullname);
            database >> students[i].sex;
            database >> students[i].age >> ws;
            getline(database, students[i].faculty);
            database >> students[i].courseId;
            database >> students[i].group;
            database >> students[i].id;
            for (int j = 0; j < 8; j++)
                database >> students[i].grades[j];
            database >> ws;
            getline(database, students[i].update_date);
        }
        database.close();

        cout 
            << "ID  Faculty  Course Group  Id   Sex  Age  Name                     Last Updated & Grades\n"
            << "----------------------------------------------------------------------------------------\n";

        int t = 0;
        for(int i = 0; i < c; i++) {
            if (students[i].id == eId) {
                t++;
                cout
                    << setw(3) << left << i << ' '
                    << setw(8) << students[i].faculty << ' '
                    << setw(6) << students[i].courseId << ' '
                    << setw(6) << students[i].group << ' '
                    << setw(4) << students[i].id << ' '
                    << setw(4) << students[i].sex << ' '
                    << setw(4) << students[i].age << ' '
                    << setw(24) << students[i].fullname << ' '
                    << setw(24) << students[i].update_date << ' ';
                for(int j = 0; j < 8; j++)
                    cout << ' ' << students[i].grades[j];
                cout << '\n';
            }
        }
        if (t == 0)
            cout << "No students found.\n";

        delete[] students;
	}
	else
        cout << "Database read error!\n";
}

void printEntries() {
    int c = countEntries();
    if (c == 0) {
        cout << "Database has no entries!\n";
        return;
    }

	ifstream database("students.txt");
	if (database.is_open())
	{
        cout 
            << "ID  Faculty  Course Group  Id   Sex  Age  Name                     Last Updated & Grades\n"
            << "----------------------------------------------------------------------------------------\n";

        for(int i = 0; i < c; i++) {
            Student student;
            getline(database, student.fullname, '\n');
            database >> student.sex;
            database >> student.age >> ws;
            getline(database, student.faculty, '\n');
            database >> student.courseId;
            database >> student.group;
            database >> student.id;
            for (int j = 0; j < 8; j++)
                database >> student.grades[j];
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
            for(int j = 0; j < 8; j++)
                cout << ' ' << student.grades[j];
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
            "2. Create student entry\n"
            "3. Edit student entry\n"
            "4. View students from group\n"
            "5. Top 5 students with highest average grades\n"
            "6. Count males/females\n"
            "7. View students with lowest grade 3 (no scholarship)\n"
            "8. View students with lowest grade 4\n"
            "9. View students with lowest grade 5\n"
            "10. View students with specific list id\n\n";
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
            case 4:
                viewGroupEntries();
                break;
            case 5:
                top5();
                break;
            case 6:
                separateBySex();
                break;
            case 7:
                viewByGrades(3);
                break;
            case 8:
                viewByGrades(4);
                break;
            case 9:
                viewByGrades(5);
                break;
            case 10:
                viewById();
                break;
            default:
                cout << "\nCategory with number " << choice << " does not exist." << endl;
                break;
        }
        system("pause");
    }
    return 0;
}
