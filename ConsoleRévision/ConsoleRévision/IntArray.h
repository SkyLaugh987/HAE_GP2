#pragma once
#include"utility"
#include <cstdio>
#include <algorithm>


class IntArray {
	int* data = nullptr;
	int size = 0;

public:
	IntArray(int size) {
		//faire l'allocation dynamique de "data" qui sera de taille "suffisement grande"
		data = new int[size];
		memset(data, 0, size * sizeof(int));
		this->size = size;
	};

	void set(int idx, int value) {
		// récupérer la donnée à la case idx et l'affecter
		// si idx hors des bornes du tab -> "exeption: out of bounds
		Resize(idx + 1);
		data[idx] = value;
	};

	int get(int idx) {
		// récupérer la donnée à la case idx et la retourner
		if ((idx > size) || (idx < size)) {
			throw "exception out of bounds";
		}
		else {

			return data[idx];
		}
	};

	void Resize(int newSize) {
		if (newSize <= size)
			return;
		int * ndata = new int[newSize];
		for (int i = 0; i < size; i++)
		{
			ndata[i] = data[i];
		}
		for (int i = size; i < newSize; i++)
		{
			ndata[i] = 0;
		}
		int * olddata = data;
		this->data = ndata;
		delete olddata;
		size = newSize;
	};

	void Insert(int value) {
		int i = 0;
		while ((i < size) && (data[i] < value)) {
			i++;
		}
		InsertAt(i, value);
	}

	void InsertAt(int idx, int value) {
		int oldSize = size;
		Resize(std::max<int>(idx + 1, size + 1));

		for (int i = oldSize; i > idx; i--)
		{
			data[i] = data[i - 1];
		}
		data[idx] = value;

	}

	static int cmp(const void * v0, const void * v1) {
		return *(int*)v1 - *(int*)v0;
	}

	void qsort() {
		::qsort(data, size, sizeof(int), cmp);
	}

	~IntArray() {

		delete[] data;
	}

};