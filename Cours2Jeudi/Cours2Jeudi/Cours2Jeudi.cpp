// Cours2Jeudi.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include "Int64Array.hpp"
#include "tools.hpp"

int StrLenRec(const char* chaine) {
	if (!chaine) return 0;
	if (chaine[0] == 0) return 0;
	return 1 + StrLenRec(chaine + 1);
}


int StrCmpRec(const char* a, const char* b) {
	if (!a) return 0;
	if (!b) return 0;
	if ((*a == 0) && (*b == 0)) return 0;

	if (*a == 0) return 1;
	if (*b == 0) return -1;

	if (a[0] == b[0]) return StrCmpRec(a + 1, b + 1);
	else if (*a > * b) return 1;
	else return -1;
}


const char* StrStrRec(const char* str, const char* pattern) {
	if (!str) return nullptr;
	if (*str == 0) return nullptr;
	if (0 == StrCmpRec(str, pattern)) return str;
	else return StrStrRec(str + 1, pattern);
}


void StrCpyRec(char* dst, const char* src) {
	if (!src) return;
	if (!dst) return;
	if (src[0] == 0) {
		dst[0] = 0;
		return;
	}

	*dst = *src;
	return StrCpyRec(dst + 1, src + 1);
}


char* StrCatRec(char* dst, const char* src) {
	if (!src) return 0;
	if (!dst) return 0;
	if (*src == 0) return nullptr;

	if (dst[0] == 0) {
		StrCpyRec(dst, src);
	}
	else
	{
		return StrCatRec(dst + 1, src);
	}
}


const char* StrChrRec(const char* chaine, char c) {
	if (!chaine) return nullptr;
	if (chaine[0] == 0) return 0;
	if (*chaine == c) return  chaine;
	return StrChrRec(chaine + 1, c);
}


int main()
{
	/*const char* toto = "chat";
	char tata[1024] = {};
	strcpy_s(tata, "chient");

	int count = StrLenRec(toto);
	printf("%d\n", count);

	const char* tutu = StrChrRec(toto , 't');
	printf("%s\n", tutu);

	char * titi = StrCatRec(tata, toto);
	printf("%s\n", titi);*/

	Int64Array tab(10);
	Int64Array ti;
	Int64Array ti2;
	Int64Array ti3;

	int64_t tt[] = { 465,548,12,0,999 };
	int sz = sizeof(tt) / sizeof(int64_t);

	tab.ensure(16);
	tab.set(15, 20);
	tab.set(16, 21);
	tab.push_back(22);
	tab.insert(5, 10);
	ti.insert(0, 1);
	ti.insert(0, 2);
	ti.insert(0, 3);
	ti.insert(2, 5);
	ti.insert(1, 6);
	ti.insert(0, 7);
	ti2.insert_ordered(106);
	ti2.insert_ordered(6);
	ti2.insert_ordered(66);
	ti2.insert_ordered(6666);
	ti3.append_sorted(tt, sz);


	int64_t tt2[] = { 465,548,12,0,999 };
	int sz2 = sizeof(tt2) / sizeof(int64_t);

	//Int64Array::insertion_sort(tt2, 5);

	//srand(0);
	Int64Array ti4;
	double t0 = getTimeStamp();
	for (size_t i = 0; i < 1000000; i++)
	{
		ti4.push_back(rand() % 135479658);
	}
	double t1 = getTimeStamp();
	printf("time elapsed %11f s\n", (t1 - t0));


	Int64Array ti5;
	double t2 = getTimeStamp();
	for (size_t i = 0; i < 1000000; i++) {
		ti5.insert_ordered(rand() % 135479658);

	}
	double t3 = getTimeStamp();
	printf("time elapsed %11f s", (t3 - t2));
	return 0;
}
