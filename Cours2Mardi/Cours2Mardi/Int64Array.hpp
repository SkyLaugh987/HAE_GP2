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

		void zero(int idx, int nb) {
			if (idx >= nb) return;
			
			else {
				data[idx] = 0;
				zero(idx + 1, nb);
			}
		}

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
		void insert(int pos, int64_t elem) {

		}
		void shiftRight(int pos);

};