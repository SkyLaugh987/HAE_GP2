#pragma once
class IntArray {
	int* data = nullptr;


public:


	IntArray() {
		//faire l'allocation dynamique de "data" qui sera de taille "suffisement grande"
		data = new int[1000];

	};

	void set(int idx, int value) {

		// r�cup�rer la donn�e � la case idx et l'affecter
		data[idx] = value;
		

	};
	int get(int idx) {

		// r�cup�rer la donn�e � la case idx et la retourner

		return data[idx];
	};

};