#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include "stack.h"

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

map<string, int> weights = { 
    {"+", 1},
    {"-", 1},
    {"*", 2},
    {"/", 2},
	{"^", 3},
    {"(", 0},
    {")", 0}
};

map<string, int> variables = {
	{"x", 5}
};

bool isOperation(const string& str) {
	auto res = weights.find(str);
	return res != weights.end();
}

bool isLiteral(const string& str) {
	auto res = variables.find(str);
	return res != variables.end();
}

bool isNumber(const string& str) {
    string::const_iterator it = str.begin();
    while (it != str.end() && isdigit(*it)) ++it;
    return !str.empty() && it == str.end();
}

vector<string> tokenize(const string& text) {
	vector<string> tokens{};
	istringstream input(text);

	for (string token; getline(input, token, ' ');)
		tokens.push_back(token);
	return tokens;
}

bool shouldMoveOperation(string token, StackNode* opstack) {
	StackNode* last = stackLast(opstack);
	return weights.find(last->value)->second >= weights.find(token)->second;
}

void print(string str, ostream& os1, ostream& os2) {
	os1 << str;
	os2 << str;
}

string reversePolishNotation(string& inpt_str) {
	ofstream ofs("out.txt");
	string current_str;
    vector<string> str_tokens = tokenize(inpt_str);
	StackNode* outStack = NULL;
    StackNode* opStack = NULL;
	for (const auto& token : str_tokens) {
		print("Token: " + token + "\nOut: ", cout, ofs);
		stackPrint(outStack, cout); stackPrint(outStack, ofs);
		print("\nOps: ", cout, ofs);
		stackPrint(opStack, cout); stackPrint(opStack, ofs);
		print("\n\n", cout, ofs);
		if (isNumber(token))
			stackAdd(outStack, token);
		else if (isOperation(token)) {
			if (!opStack)
				stackPush(opStack, token);
			else if (token == "(")
				stackAdd(opStack, token);
			else if (token == ")") {
				while (opStack && current_str != "(") {
					current_str = stackTake(opStack);
					stackAdd(outStack, current_str);
					StackNode* last = stackLast(opStack);
					if (!last)
						throw "Unpaired bracket encountered";
					current_str = last->value;
				}
				if (!opStack)
					throw "Unpaired bracket encountered";
				current_str.clear();
				stackTake(opStack);
			} else if (shouldMoveOperation(token, opStack)) {
				stackPushBack(outStack, stackTake(opStack));
				stackAdd(opStack, token);
			} else
				stackPushBack(opStack, token);
		}
		else {
			auto found = variables.find(token);
			if (found == variables.end()) {
				print("Enter value for " + token + ": ", cout, ofs);
				int var = readValue<int>();
				ofs << var << endl;
				variables[token] = var;
				stackAdd(outStack, to_string(var));
			} else {
				stackAdd(outStack, to_string(found->second));
			}
		}
	}
	print("Moving operations to main stack.\n", cout, ofs);
	while (opStack)
		stackPushBack(outStack, stackTake(opStack));
	print("Result: ", cout, ofs);
	stackPrint(outStack, cout); stackPrint(outStack, ofs);
	print("\n", cout, ofs);
	string outp;
	while (outStack) {
		outp += outStack->value + ' ';
		outStack = outStack->next;
	}
	return outp;
}

void polishNotation(string& inpt_str) {
	ofstream ofs("out.txt");
	string inp;
	for(int i = inpt_str.length() - 1; i >= 0; i--) {
		if (inpt_str[i] == '(')
			inp.push_back(')');
		else if (inpt_str[i] == ')')
			inp.push_back('(');
		else
			inp.push_back(inpt_str[i]);
	}
	reverse(inpt_str.begin(), inpt_str.end());
	string outp = reversePolishNotation(inp);
	reverse(outp.begin(), outp.end());
	cout << outp << endl;
}

int computeRpn(string& rpn) {
	istringstream reader(rpn);
	StackNode* outStack = NULL;
	string token;
	while (!reader.eof()) {
		reader >> token;
		if (isNumber(token)) {
			stackAdd(outStack, token);
		} else {
			if (stackSize(outStack) < 2)
				throw "Invalid operation order";
			int right = stoi(stackTake(outStack)), left = stoi(stackTake(outStack));
			switch (token[0]) {
				case '+': 
					stackAdd(outStack, to_string(left + right));
					break;
				case '-': 
					stackAdd(outStack, to_string(left - right));
					break;
				case '/': 
					stackAdd(outStack, to_string(left / right));
					break;
				case '*': 
					stackAdd(outStack, to_string(left * right));
					break;
				case '^': 
					stackAdd(outStack, to_string(pow(left, right)));
					break;
				default:
					throw "Unknown operator " + token;
			}
		}
	}
	if (stackSize(outStack) != 1)
		throw "Invalid stack size";
	return stoi(stackPop(outStack));
}

int computePn(string& rpn) {
	vector<string> tokens = tokenize(rpn);
	reverse(tokens.begin(), tokens.end());
	string rev;
	for(const auto& token : tokens)
		rev += token + ' ';
	rev.pop_back();
	return computeRpn(rev);
}

int main()
{
	while (true) {
        system("cls");
        cout <<
            "Choose a category from below:\n"
            "0. Exit\n"
            "1. Convert expression into polish notation\n"
            "2. Convert expression into reverse polish notation\n"
            "3. Compute expression given in polish notation\n"
            "4. Compute expression given in reverse polish notation\n\n";
        int choice = readValue<int>("Type a number to continue: ");
        cout << endl;
        switch (choice) {
            case 0:
                return 0;
			case 1: {
				string inp;
				cout << "Enter mathematical expression: ";
				getline(cin, inp);
				try {
					polishNotation(inp);
				} catch (const char* data) {
					cout << "Error! " << data << endl;
				}
			}
				break;
			case 2: {
				string inp;
				cout << "Enter mathematical expression: ";
				getline(cin, inp);
				try {
					reversePolishNotation(inp);
				} catch (const char* data) {
					cout << "Error! " << data << endl;
				}
			}
				break;
			case 3: {
				string inp;
				cout << "Enter polish notation expression: ";
				getline(cin, inp);
				try {
					cout << "Result: " << computePn(inp) << endl;
				} catch (const char* data) {
					cout << "Parsing error! " << data << endl;
				}
			}
				break;
			case 4: {
				string inp;
				cout << "Enter reverse polish notation expression: ";
				getline(cin, inp);
				try {
					cout << "Result: " << computeRpn(inp) << endl;
				} catch (const char* data) {
					cout << "Parsing error! " << data << endl;
				}
			}
				break;
            default:
                cout << "\nCategory with number " << choice << " does not exist." << endl;
                break;
        }
        system("pause");
    }
}