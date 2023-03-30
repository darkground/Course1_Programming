#include "list.h"

/*
* Создание списка с N готовыми элементами
* int n - количество = 0
*/
List* listCreate(int n = 0) {
    List* list = new List{};
    if (n <= 0)
        return list;

    ListNode* current = 0;
    ListNode* next = 0;
    for (int i = 1; i <= n; i++) {
        current = new ListNode;
        current->next = next;
        if (next)
            next->prev = current;
        next = current;
    }

    list->head = current;
    list->length = n;

    return list;
}

/*
* Добавить элемент в конец списка
* List* list - указатель на список
* int value - число = 0
*/
ListNode* listAdd(List* list, int value = 0) {
    ListNode* newNode = new ListNode;
    newNode->data = value;

    if (list->head) {
        ListNode* node = list->head;
        while (node->next)
            node = node->next;
        newNode->prev = node;
        node->next = newNode;
    }
    else
        list->head = newNode;

    list->length++;
    return newNode;
}

/*
* Получить элемент по индексу. При индексе > length будет возвращён нулевой указатель.
* List* list - указатель на список
* unsigned index - индекс в списке
*/
ListNode* listItem(List* list, unsigned index)
{
    ListNode* node = list->head;
    while (node && (index--))
        node = node->next;
    return node;
}

/*
* Получить длину списка. Альтернатива list->length.
* List* list - указатель на список
*/
unsigned listLength(List* list)
{
    unsigned length = 0;
    ListNode* node = list->head;
    while (node)
    {
        length++;
        node = node->next;
    }
    return length;
}

/*
* Удалить элемент по индексу. При индексе > length список не будет изменён.
* List* list - указатель на список
* unsigned index - индекс в списке
*/
void listRemove(List* list, unsigned index)
{
    if (index == 0)
    {
        ListNode* item = list->head->next;
        delete list->head;
        item->prev = 0;
        list->head = item;
        list->length--;
    }
    else {
        ListNode* prevItem = listItem(list, index - 1);
        if (prevItem) {
            ListNode* delItem = prevItem->next;
            prevItem->next = delItem->next;
            prevItem->next->prev = prevItem;
            delete delItem;
            list->length--;
        }
    }
}

/*
* Удалить список И все его элементы.
* List* list - указатель на список
* unsigned index - индекс в списке
*/
void listClear(List* list)
{
    ListNode* next;
    ListNode* current = list->head;
    while (current)
    {
        next = current->next;
        delete current;
        current = next;
    }
    delete list;
}

/*
* Вставить элемент по индексу. При индексе > length элемент будет добавлен в конец списка.
* List* list - указатель на список
* unsigned index - индекс в списке
*/
ListNode* listInsert(List* list, unsigned index, int value)
{
    ListNode* item = new ListNode;
    item->data = value;
    if (!(list->head)) // Когда в списке нет элементов
        list->head = item;
    else if (index == 0) {
        ListNode* first = list->head;
        list->head = item;
        item->next = first;
        first->prev = item;
    }
    else {
        ListNode* prev = list->head;
        index--;
        while (prev->next && (index--))
            prev = prev->next;
        item->prev = prev;
        item->next = prev->next;
        if (prev->next) // Если prev->next == nullptr, то prev - последний элемент в списке
            prev->next->prev = item;
        prev->next = item;
    }
    list->length++;
    return item;
}
