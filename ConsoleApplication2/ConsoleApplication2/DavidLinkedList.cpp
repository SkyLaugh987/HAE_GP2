#include"DavidLinkedList.h"

Intlist* appendFirst(Intlist* l, int value) {
	Intlist* newN = (Intlist*)malloc(sizeof(Intlist));
	newN->data = value;
	newN->next = l;
	return newN;
}

int length(Intlist* l) {
	if (!l) return 0;
	else return 1 + length(l->next);
}

Intlist* appendLast(Intlist* l, int value) {
	
	if (!l) {
		return appendFirst(l, value);
	}
	if (l->next) {
		appendLast(l->next, value);
	}
	else {
		l->next = appendFirst(nullptr, value);
	}
	return l;
}
Intlist* remove(Intlist* l, int value) {
	if (!l) {
		return nullptr;
	}
	if (l->data == value) {
		Intlist* rest = l->next;
		free(l);
		return rest;
	}
	else {
		l->next = remove(l->next, value);
		return l;
	}
}