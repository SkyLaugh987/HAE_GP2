#include "Int64Array.hpp"
#include <cstdlib>
#include <cstdio>
#include <cstring>




void Int64Array::zero(int idx, int nb) {
	memset(data + idx, 0, nb * sizeof(int64_t));
}

void Int64Array :: ensure(int size) {
	if (size < maxSize) return;
	int oldsize = maxSize;
	maxSize = size*2;
	int64_t * oldData = data;
	data = new int64_t[size];
	memset(data, 0, sizeof(int64_t) * size);
	memcpy(data, oldData, oldsize * sizeof(int64_t));
	delete (oldData);
}

void Int64Array:: set_unsafe(int pos, int64_t elem) {
	data[pos] = elem;
}

void Int64Array::set(int pos, int64_t elem) {
	ensure(pos + 1);
	
	data[pos] = elem;
	if (pos >= curSize)
		curSize = pos + 1;
}
void Int64Array::push_back(int64_t elem) {
	
	set(curSize, elem);
}

void Int64Array::push_front(int64_t elem) {
	insert(0, elem);
}

void Int64Array :: insert(int pos, int64_t elem) {
	shiftRight(pos);
	set(pos, elem);
}


void Int64Array::shiftRight(int pos) {
	ensure(curSize + 1);
	shift_from_to(pos, curSize);
	curSize++;
}

void Int64Array::shift_from_to(int end, int cur) {
	if (cur <= end) return;
	data[cur] = data[cur - 1];
	shift_from_to(end, cur - 1);
}

void Int64Array::insert_ordered(int64_t elem) {

	int pos = searchPos(0, elem);
	insert(pos, elem);
}

int Int64Array::searchPos(int idx, int64_t elem) {
	if (idx >= curSize)
		return curSize;

	if (data[idx] >= elem) return idx;
	return searchPos(idx + 1, elem);
}

void Int64Array :: append_sorted(const int64_t* arr, int sz) {
	if (sz <= 0) return;
	insert_ordered(arr[0]);
	append_sorted(arr + 1, sz - 1);
}

void Int64Array::load(const int64_t* arr, int sz) {
	if (sz == 0) return;
	set(curSize, arr[0]);
	load(arr + 1, sz - 1);

}
void Int64Array::insertion_sort(int64_t* arr, int nbElem) {

	for (size_t i = 0; i < nbElem; i++)
	{
		int j = i;
		while( (arr[j] >= 0) && (arr[j] < arr[j - 1 ]) )
		{
			swap(&arr[j], &arr[j - 1]);
			j = j - 1;
		}
	}
}
void Int64Array::swap(int64_t * a, int64_t * b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

int Int64Array::bsearch(int64_t elem) {
	return _bsearch(elem, 0, curSize - 1);
}

int Int64Array::_bsearch(int64_t elem, int lo, int  hi) {
	if (hi < lo) return -1;

	if (elem == data[lo]) return lo;
	if (elem == data[hi]) return hi;
	int mid = (lo + hi) >> 1;          // c la moitié
	if (elem == data[mid]) return mid;

	if (elem <= (data[hi])) return _bsearch(elem, lo + 1, mid - 1);
	else return _bsearch(elem, mid + 1 , hi - 1);
	
}

int Int64Array::_bsearchIter(int64_t elem, int lo, int hi) {
	int lo = 0;
	int hi = curSize;
	if (lo >= hi) return -1;
	if (elem == data[lo]) return lo;
	if (elem == data[hi]) return hi;
	int mid = (lo + hi) >> 1;
	while (lo <= hi) {
		if (elem == data[mid]) return mid;
		if (elem >= data[mid]) {

		}
		if (elem <= data[mid]) {

		}
	}

}



