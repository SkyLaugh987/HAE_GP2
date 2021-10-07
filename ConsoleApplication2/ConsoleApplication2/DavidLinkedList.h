#pragma once
#include"cstdlib"
#include"cstring"

struct Intlist {
	int data = 0.0;
	Intlist* next = nullptr;
	

};

Intlist* appendFirst(Intlist* l, int value);
	

Intlist* appendLast(Intlist* l, int value);


Intlist* remove(Intlist* l, int value);


int length(Intlist* l);

