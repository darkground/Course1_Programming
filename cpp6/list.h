#pragma once
struct ListNode {
    int data = 0;
    ListNode* prev = 0;
    ListNode* next = 0;
};

struct List {
    int length;
    ListNode* head;
};

List* listCreate(int);
void listClear(List*);
ListNode* listAdd(List*, int);
void listRemove(List*, unsigned);
ListNode* listItem(List*, unsigned);
ListNode* listInsert(List*, unsigned, int);
unsigned listLength(List*);