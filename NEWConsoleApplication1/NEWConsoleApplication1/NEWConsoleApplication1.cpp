// NEWConsoleApplication1.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include "pch.h"
#include <iostream>
#include "Toto.h"
#include "IntArray.h"
#include "LinkedList.h"


//--------------------------------------------- 1er exo --------------------------
/*int main()
{
	printf("0\n");

	int zero = 0;
	printf("%i\n", zero);

	float decimal = 0.5f;
	printf("%f\n", decimal);

	printf("%s\n", "toto");
	printf("%lli\n", 132456789);

	std::cout << "123465789" << "\n";
}*/

//-------------------------------------------------------Pointeur sur Tab------------------------
	/*int main()
	{
		int tab[] = { 66,1,2,3 };
		int* c = &tab[0];
		*c = 0;

		//printf("%d\n", *c++);
		//afficher c  incremente c et prend le contenu

		//printf("%d\n", (*c)++);
		//prend le contenu de c et incrémente le

		//printf("%d\n", *++c);
		// incremente c et prend le contenu

		//printf("%d\n", ++*c);
		// prend le contenu de c et incremente le
	}*/


	//--------------------------------------------------------------- Struct manipulation Pointeur  exple-------------------------------------------
	/*struct Vec {

		float x = 0;
		float y = 0;
		float z = 0;
	};

	int main() {
		//Vec toto;

		Vec* toto = new Vec();
		toto->y = 67;
		(*toto).x = 69;
		printf("%f %f %f", toto->x, toto->y, toto->z);
	};*/
	//-------------------------------------------------------------------------- Struct V4  fonction-------------------------
struct Vec4 {

	float x = 0;
	float y = 0;
	float z = 0;
	float w = 0;

	Vec4 add(Vec4 A) {

		Vec4 res;

		res.x = x + A.x;
		res.y = y + A.y;
		res.z = z + A.z;
		res.w = w + A.w;

		return res;
	}

	Vec4 add(float f) {

		Vec4 res;

		res.x = x + f;
		res.y = y + f;
		res.z = z + f;
		res.w = w + f;

		return res;
	}

	Vec4 div(Vec4 A) {

		Vec4 res;

		res.x = x / A.x;
		res.y = y / A.y;
		res.z = z / A.z;
		res.w = w / A.w;

		return res;
	}


};

/*int main() {

	Vec4* toto = new Vec4;
	Vec4* tata = new Vec4;

	toto->x = 1;
	toto->y = 1;
	toto->z = 1;
	toto->w = 1;

	tata->x = 1;
	tata->y = 1;
	tata->z = 1;
	tata->w = 5;

	//Vec4 res = toto->add(*tata);
	Vec4 res = toto->div(*tata);
	printf("%f\n %f\n %f\n %f\n", res.x, res.y, res.z, res.w);
}*/


//----------------------------------------------------------------- Exo IntArray----------------------------------------------

/*int main() {

	int* bobData = nullptr;

	IntArray bob(10);

	for (int i = 0; i < 10; i++) {
		bob.set(i, i * i);
	}
	for (int i = 0; i < 10; i++) {
		printf("%d ", bob.get(i));
	}
	printf("\n");

	//bob.set(20, 10);

	return 0;
}*/

//-------------------------------------------------------------------CHAR------------------------------------------


int Strlen(const char* maChaine) {

	//declarer le resultat
	
	// parcourir la chaine
	int i = 0;
		while (maChaine[i] != 0) {
			//avancer mo,n index
			i++;
		}
		//si on trouve le character == 0
		
		return i;
	



}
int Countc(const char* maChaine, char c) {


	// renvoie le nombre d'occurence de c dans machaine 

	// machaine est un tableau de char

	// si l'element de l'idx courant = c 

	// inc le resultat

	// renvoyer le resultat

	int res = 0;
	int stringLength = strlen(maChaine);

	for (int i = 0; i < (stringLength); i++) {
		if (maChaine[i] == c) {
			res++;
		};
	}
	return res;
}

void Strcpy(char * Copy, const char* Origin) {

	int OriginLength = Strlen(Origin);

	for (int i = 0; i <= (OriginLength); i++) {
		Copy[i] = Origin[i];
	}

}

void Strncpy(char * Copy, const char * Origin, int nchars) {

	for (int i = 0; i < nchars; i++) {
		Copy[i] = Origin[i];
	}
}

int main() {
	/*//int nbB = Strlen("sapin");
	//int nbA = Countc("sapin", 'a');
	char oui[4] = "oui";
	char non[4] = " ";
	int o = 2;
	//Strcpy(non, oui);
	Strncpy(non, oui, o);
	//printf("%d\n", nbA);
	//printf("%d\n", nbB);

	printf("%s\n", oui);
	printf("%s", non);

	return 0;*/
	LinkedList myList;
	
	myList.AddFront(10);
	myList.AddLast(14);
	myList.AddLast(16);
	myList.AddLast(18);
	myList.AddFront(9);
	/*myList.AddLast(14);
	myList.AddLast(16);
	myList.AddLast(19);
	myList.AddLast(20);
	myList.RemoveLast(head);*/
	myList.RemoveFirst();
	myList.RemoveLast();
	myList.Insert(20, 3);
	myList.Insert(15, 2);
	myList.RemoveAll();
	myList.PrintList();
	
};
