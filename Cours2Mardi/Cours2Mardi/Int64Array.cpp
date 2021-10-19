#include "Int64Array.hpp"
#include <cstdlib>
#include <cstdio>
#include <cstring>




void Int64Array :: ensure(int size) {
	if (size < maxSize) return;
	int oldsize = maxSize;
	maxSize = size;
	int64_t * oldData = data;
	data = new int64_t[size];
	memcpy(data, oldData, oldsize * sizeof(int64_t));
	zero(0, maxSize);
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
	
	set(maxSize, elem);
}

void Int64Array::push_front(int64_t elem) {
	insert(0, elem);
}

void Int64Array :: insert(int pos, int64_t elem) {
	shiftRight(pos);
}

void Int64Array::shiftRight(int pos) {
	
	
	shiftRight(pos - 1);
}

