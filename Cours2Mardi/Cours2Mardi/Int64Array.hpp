#pragma once
#include <stdint.h>
#include <cstdlib>

class Int64Array {
	public:
		int64_t * data = nullptr;

		int maxSize = 0;
		int curSize = 0;
		int64_t size = 0;

	public:
		Int64Array(int size = 0) {
			if (size < 0) size = 0;
			curSize = size;
			if (size <= 0)
				maxSize = 16;
			else
				maxSize = size;

			data = new int64_t[maxSize];

			zero(0, maxSize);
			//memset(data, 0, 70000 * sizeof(int64_t));
		}

		void zero(int idx, int nb);

		void ensure(int size);
		void set_unsafe(int pos, int64_t);
		void set(int pos, int64_t elem);
		void push_back(int64_t elem);
		void push_front(int64_t elem);

		int64_t& get(int pos) {
			ensure(pos + 1);
			if (pos >= curSize)
				curSize = pos + 1;
			return data[pos];
		}

		int64_t& operator[](int idx) {
			return get(idx);
		}

		void insert(int pos, int64_t elem);
		void insert_ordered(int64_t elem);
		void append_sorted(const int64_t* arr, int sz);
		static void insertion_sort(int64_t* arr, int sz);
		void load(const int64_t* arr, int sz);

		int bsearch(int64_t elem);
		int _bsearch(int64_t elem, int lo, int hi);
		int _bsearchIter(int64_t elem, int lo, int hi);


		~Int64Array() {
			delete(data);
			data = nullptr;
			maxSize = 0;
			curSize = 0;
		}
		
protected :

		void shiftRight(int pos);
		void shift_from_to(int end, int cur);
		int searchPos(int pos, int64_t elem);
		void clear() {
			curSize = 0;
		}
		static void swap( int64_t* a, int64_t* b);

		
};