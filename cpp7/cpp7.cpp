#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <stdexcept>
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

void reversePolishNotation(string& inpt_str) {
	ofstream ofs("out.txt");
	string current_str;
    vector<string> str_tokens = tokenize(inpt_str);
	StackNode* outStack = NULL;
    StackNode* opStack = NULL;
	for (const auto& token : str_tokens) {
		std::cout << "Token: " << token;
		ofs << "Token: " << token;
		std::cout << "\nOut: ";
		ofs << "\nOut: ";
		stackPrint(outStack, std::cout);
		stackPrint(outStack, ofs);
		std::cout << "\nOps: ";
		ofs << "\nOps: ";
		stackPrint(opStack, std::cout);
		stackPrint(opStack, ofs);
		cout << "\n" << endl;
		ofs << "\n" << endl;
		if (isNumber(token))
			stackAdd(outStack, token);
		else if (isOperation(token)) {
			if (!opStack)
				stackPush(opStack, token);
			else if (token == "(")
				stackAdd(opStack, token);
			else if (token == ")") {
				while (opStack && current_str != "(") {
					current_str = stackSize(opStack) > 1 ? stackPopBack(opStack) : stackPop(opStack);
					stackAdd(outStack, current_str);
					current_str = stackLast(opStack)->value;
				}
				if (!opStack)
					throw "Unpaired bracket encountered";
				current_str.clear();
				stackSize(opStack) > 1 ? stackPopBack(opStack) : stackPop(opStack);
			} else if (shouldMoveOperation(token, opStack)) {
				stackPushBack(outStack, stackSize(opStack) > 1 ? stackPopBack(opStack) : stackPop(opStack));
				stackAdd(opStack, token);
			} else
				stackPushBack(opStack, token);
		}
		else if (isLiteral(token))
			stackAdd(outStack, std::to_string(variables.find(token)->second));
		else
			throw "Unexpected token " + token;
	}
	cout << "Moving operations to main stack." << endl;
	ofs << "Moving operations to main stack." << endl;
	while (opStack)
		stackPushBack(outStack, stackSize(opStack) > 1 ? stackPopBack(opStack) : stackPop(opStack));
	cout << "Result: ";
	ofs << "Result: ";
	stackPrint(outStack, cout);
	stackPrint(outStack, ofs);
	cout << endl;
	ofs << endl;
}

int main()
{
    string x = "3 + 4 * 2 / ( 1 - 5 ) ^ x";
	reversePolishNotation(x);
	return 0;
}