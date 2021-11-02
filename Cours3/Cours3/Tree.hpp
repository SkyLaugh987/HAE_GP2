#pragma once
template<typename Value>
class Tree
{
public:
	Value v;
	Tree* l = nullptr;
	Tree* r = nullptr;
	
	Tree(Value v) {
		this->v = v;
	}


	Tree* insert(Value elem) {
		if (elem < v) {
			if (l)
				l->insert(elem);
			else
				l = new Tree(elem);
		}
		else {
			if (r) {
				r->insert(elem);
			}
			else
				r = new Tree(elem);
		}
		return this;
	}

	Tree* search(Value o) {
		if (v == o) {
			return this;
		}
		else {
			if (o < v) {
				if (l) {
					return l->search(o);
				}
				else return nullptr;
			}
			else {
				if (r) {
					return r->search(o);
				}
				else return this;
			}
		}
	}


	Tree* remove(Value o) {
		if (v == o) {
			auto _l = l;
			auto _r = r;

			if (!l) {
				delete this;
				return _r;
			}

			else if (!r) {
				delete this;
				return _l;
			}

			else {
				l->merge(r);
				delete this;
				return _l;
			}

		}

		else {
			if (o < v) {
				if (l) {
					l = l->remove(o);
				}
				if (r)
					r = r->remove(o);
			}
			return this;
		}
	}

	Tree* merge(Value other) {
		Value vo = other->v;

		insert(vo);

		if (other->l) merge(other->l);
		if (other->r) merge(other->r);
		delete other;
		return this;
	}
};