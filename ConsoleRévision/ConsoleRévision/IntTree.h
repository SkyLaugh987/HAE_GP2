#pragma once
#include"cstdlib"
#include"cstring"

struct IntTreeRevision {

	int value = 0.0;
	// fils gauche tjrs < fils droite
	IntTreeRevision* left = nullptr;
	IntTreeRevision* right = nullptr;
	// relation d'ordre

	//val de fg<valeur<val fd


};
IntTreeRevision* create(int value);
int count(IntTreeRevision* head);
IntTreeRevision* insert(IntTreeRevision* head, int val);
IntTreeRevision* remove(IntTreeRevision* head, int val);
IntTreeRevision* merge(IntTreeRevision* a, IntTreeRevision* b);