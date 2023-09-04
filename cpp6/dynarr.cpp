#include <iostream>
#include "dynarr.h"

/*
* Создать и вернуть динамический массив.
*/
Dynarr* dynarrCreate() {
	Dynarr* dynarr = new Dynarr;
	dynarr->arr = new int[1];
	dynarr->capacity = 1;
	dynarr->length = 0;
	return dynarr;
}

/*
* Очистить динамический массив.
* Dynarr* arr - массив
*/
void dynarrClear(Dynarr* arr) {
	delete[] arr->arr;
	delete arr;
}

/*
* Добавить элемент в конец массива.
* Dynarr* arr - массив
* int data - данные
*/
void dynarrAdd(Dynarr* arr, int data) {
	if (arr->length == arr->capacity)
		dynarrResize(arr, arr->capacity * 2);
	arr->arr[arr->length] = data;
	arr->length++;
}


/*
* Изменить вместимость динамического массива.
* Dynarr* arr - массив
* int capacity - вместимость (< length)
*/
void dynarrResize(Dynarr* arr, int capacity) {
	if (capacity <= arr->capacity)
		return;
	int* temp = new int[capacity];

	for (int i = 0; i < arr->capacity; i++)
		temp[i] = arr->arr[i];

	delete[] arr->arr;
	arr->capacity = capacity;
	arr->arr = temp;
}


/*
* Получить элемент динамического массива по индексу.
* Dynarr* arr - массив
* unsigned index - индекс
*/
int dynarrItem(Dynarr* arr, unsigned index) {
	return arr->arr[index];
}

/*
* Вставить элемент в динамический массив по индексу.
* Dynarr* arr - массив
* unsigned index - индекс
* int data - элемент
*/
void dynarrInsert(Dynarr* arr, int index, int data) {
	if (arr->length == arr->capacity)
		dynarrResize(arr, arr->capacity * 2);
	arr->length++;

	for (int i = arr->length; i > index; i--)
		arr->arr[i] = arr->arr[i - 1];
	arr->arr[index] = data;
}

/*
* Удалить элемент из динамического массива по индексу.
* Dynarr* arr - массив
* unsigned index - индекс
*/
void dynarrRemove(Dynarr* arr, int index) {
	for (int i = index; i <= arr->length-1; i++)
	{
		arr->arr[i] = arr->arr[i + 1];
	}
	arr->arr[arr->length - 1] = 0;
	arr->length--;
}

/*
* Поменять элементы в динамическом массиве местами, зная их индексы.
* Dynarr* arr - массив
* unsigned index1 - индекс 1
* unsigned index2 - индекс 2
*/
void dynarrSwap(Dynarr* arr, int index1, int index2) {
	std::swap(arr->arr[index1], arr->arr[index2]);
}