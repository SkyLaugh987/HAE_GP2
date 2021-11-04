#pragma once
template<typename Value>
class Tree {
public:
	Value v = {};
	Tree* l = nullptr;
	Tree* r = nullptr;

	Tree(Value val) {
		this->v = val;
	}

	Tree* insert(Value nu) {
		if (nu <= v) {
			if (l) {
				l->insert(nu);
			}
			else
				l = new Tree(nu);
		}
		else {
			if (r)
				r->insert(nu);
			else
				r = new Tree(nu);
		}
		return this;
	}

	Tree* search(Value o) {
		if (o == v) return this;

		else  {
			if (v < o) {

				if (l)
					l->search(o);

				else return nullptr;
			}

			else {
				if (r)
					r->search(o);

				else return nullptr;
			}
		}
	}

	Tree* remove(Value o) {
		if (o == v) {
			Tree* _l = l;
			Tree* _r = r;

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
				return _l;
			}
		}
		if (v < o) {
			if (l) {
				l = l->remove(o);
			}
		}
		else {
			if (r)
				r = r->remove(o;)
		}
		return this;
	}

	Tree* merge(Tree* other) {
		Value vo = other->v;
		insert(vo);
		if (other->l) merge(other->l);
		if (other->r) merge(other->r);
		delete other;
		return this;
	}
};