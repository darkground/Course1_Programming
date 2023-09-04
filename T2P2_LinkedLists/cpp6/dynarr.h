#pragma once
struct Dynarr {
	int* arr;
	int capacity;
	int length;
};

Dynarr* dynarrCreate();
void dynarrClear(Dynarr*);
void dynarrAdd(Dynarr*, int);
void dynarrResize(Dynarr*, int);
int dynarrItem(Dynarr*, unsigned);
void dynarrInsert(Dynarr*, int, int);
void dynarrRemove(Dynarr*, int);
void dynarrSwap(Dynarr*, int, int);