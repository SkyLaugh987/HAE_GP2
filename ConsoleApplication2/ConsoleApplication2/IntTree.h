#pragma once
#include"cstdlib"
#include"cstring"

struct IntTree {

	int value = 0.0;
	// fils gauche tjrs < fils droite
	IntTree* left = nullptr;
	IntTree* right = nullptr;
	// relation d'ordre

	//val de fg<valeur<val fd


};
IntTree* create(int value);
int count(IntTree* head);
IntTree* insert(IntTree* head, int val);
IntTree* remove(IntTree* head, int val);
IntTree* merge(IntTree* a, IntTree* b);
