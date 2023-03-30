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

List* listCreate(int n = 0);
void listClear(List*);
ListNode* listAdd(List*, int n = 0);
void listRemove(List*, unsigned);
ListNode* listItem(List*, unsigned);
ListNode* listInsert(List*, unsigned, int n = 0);
unsigned listLength(List*);