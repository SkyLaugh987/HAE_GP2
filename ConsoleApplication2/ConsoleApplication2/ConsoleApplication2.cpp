// ConsoleApplication2.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include "pch.h"
#include <iostream>
#include "Toto.h"


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

struct Vec4 {

	float x = 0;
	float y = 0;
	float z = 0;
	float w = 0;

	Vec4 add(Vec4 A ) {

		Vec4 res;

		res.x = x + A.x;
		res.y = y + A.y;
		res.z = z + A.z;
		res.w = w + A.w;
		
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

int main() {

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
}



// Exécuter le programme : Ctrl+F5 ou menu Déboguer > Exécuter sans débogage
// Déboguer le programme : F5 ou menu Déboguer > Démarrer le débogage

// Conseils pour bien démarrer : 
//   1. Utilisez la fenêtre Explorateur de solutions pour ajouter des fichiers et les gérer.
//   2. Utilisez la fenêtre Team Explorer pour vous connecter au contrôle de code source.
//   3. Utilisez la fenêtre Sortie pour voir la sortie de la génération et d'autres messages.
//   4. Utilisez la fenêtre Liste d'erreurs pour voir les erreurs.
//   5. Accédez à Projet > Ajouter un nouvel élément pour créer des fichiers de code, ou à Projet > Ajouter un élément existant pour ajouter des fichiers de code existants au projet.
//   6. Pour rouvrir ce projet plus tard, accédez à Fichier > Ouvrir > Projet et sélectionnez le fichier .sln.
