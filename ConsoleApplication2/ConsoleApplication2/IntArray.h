#pragma once
class IntArray {
	int* data = nullptr;
	int size = 0;

public:


	IntArray(int size) {
		//faire l'allocation dynamique de "data" qui sera de taille "suffisement grande"
		data = new int[size];
		this->size = size;

	};

	void set(int idx, int value) {

		// récupérer la donnée à la case idx et l'affecter
		// si idx hors des bornes du tab -> "exeption: out of bounds

		if ((idx > size || idx < size)) {
			throw "exeption out of bounds";
		}
		else {
			data[idx] = value;
		}
	};

	int get(int idx) {

		// récupérer la donnée à la case idx et la retourner
		if ((idx > size) || (idx < size)) {
			throw "exeption out of bounds";
		}
		else {
			return data[idx];
		}
	};

	~IntArray() {

		delete [] data;
	}

};