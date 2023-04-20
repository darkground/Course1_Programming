#include <iostream>
#include <fstream>
#include "stack.h"

int stackSize(StackNode* head) {
	int count = 0;
	while (head) {
		count++;
		head = head->next;
	}
	return count;
}

StackNode* stackCreate(const string& data) {
	StackNode* node = new StackNode;
	node->value = data;
	node->next = NULL;
	return node;
}

void stackAdd(StackNode*& head, const string& data) {
	if (!head)
		stackPush(head, data);
	else
		stackPushBack(head, data);
}

void stackPush(StackNode*& head, string data) {
	StackNode* first = new StackNode;
	first->value = data;
	first->next = head;
	head = first;
}

void stackPushBack(StackNode* head, string data) {
	StackNode* last = stackLast(head);
	StackNode* next = new StackNode;
	next->value = data;
	next->next = NULL;
	last->next = next;
}

string stackPop(StackNode*& head) {
	StackNode* prev = NULL;
	if (head == NULL) {
		exit(-1);
	}
	prev = head;
	string val = head->value;
	head = head->next;
	delete prev;
	return val;
}

string stackPopBack(StackNode* head) {
	string value;
	StackNode* lastbn = NULL;
	if (!head)
		return NULL;

	lastbn = stackGetLastButOne(head);
	value = lastbn->next->value;

	if (lastbn == NULL) {
		delete head;
		head = NULL;
	}
	else {
		delete lastbn->next;
		lastbn->next = NULL;
	}
	return value;
}

StackNode* stackLast(StackNode* head) {
	if (head == NULL)
		return NULL;
	while (head->next)
		head = head->next;
	return head;
}

void stackClear(StackNode* head) {
	StackNode* prev = NULL;
	while (head->next) {
		prev = head;
		head = head->next;
		delete prev;
	}
	delete head;
}

StackNode* stackGetLastButOne(StackNode* head) {
	if (head == NULL || head->next == NULL)
		return NULL;
	while (head->next->next)
		head = head->next;
	return head;
}

void stackPrint(const StackNode* head, ostream& sout) {
	while (head) {
		sout << head->value << " ";
		head = head->next;
	}
	sout << endl;
}