#pragma once
template<typename Type>

class List {
public:
	Type  val = {};
	List*	next = nullptr;

	List(Type elem) {
		val = elem;
	}
	List(Type elem, List* _next) {
		val = elem;
		next = _next;
	}


	List* push_first(Type newElem) {
		List* l = new List(newElem);
		l->next = this;
		return l;
	}

	List* push_back(Type newElem) {
		if (!next) {
			next = new List(newElem);
		}
		else {
			next->push_back(newElem);
		}
		return this;
	}

	List* remove(Type elem) {
		if (val == elem) {
			List* n = next;
			delete this;
			return n;
		}
		else {
			if (next)
				next->remove(elem);
			return this;
		}
	};

};