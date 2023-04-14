#pragma once
#include "list.h"
#include <cmath>
#include <iostream>


class monomial {
public:
	double coef;
	int a = 0, b = 0, c = 0;
	monomial() :coef(1), a(0), b(0), c(0) {};
	monomial(double coef1, int a1, int b1, int c1) : coef(coef1), a(a1), b(b1), c(c1) {};

	double value(double x, double y, double z) {
		return coef * (pow(x, a) * pow(y, b) * pow(z, c));
	};

	monomial diff(char h) {
		switch (h) {
		case('x'):
			if (a == 0) return monomial(0, 0, 0, 0);
			else return monomial(coef * a, a - 1, b, c);
			break;
		case('y'):
			if (b == 0) return monomial(0, 0, 0, 0);
			else return monomial(coef * b, a, b - 1, c);
			break;
		case('z'):
			if (c == 0) return monomial(0, 0, 0, 0);
			else return monomial(coef * c, a, b, c - 1);
			break;
		}
	};

	monomial integ(char h) {
		switch (h) {
		case('x'):
			return monomial(coef / (a + 1), a + 1, b, c);
			break;
		case('y'):
			return monomial(coef / (b + 1), a, b + 1, c);
			break;
		case('z'):
			return monomial(coef / (c + 1), a, b, c + 1);
			break;
		}
	};
	monomial operator*(monomial& m) {
		return monomial(coef * m.coef, a + m.a, b + m.b, c + m.c);
	};
	monomial operator*(double k) {
		return monomial(coef * k, a, b, c);
	};

	bool equal_powers(monomial& r) {
		if (this->a == r.a && this->b == r.b && this->c == r.c) return 1;
		else return 0;
	};

	double get_coef() { return coef; };

	bool operator<(monomial& r) {
		if (this->a < r.a) return 1;
		else if (this->b < r.b) return 1;
		else if (this->c < r.c) return 1;
		else if (this->a == r.a && this->b == r.b && this->c == r.c && this->coef < r.coef) return 1;
		else return 0;
	};

	bool operator<=(monomial& r) {
		if (this->a <= r.a) return 1;
		else if (this->b <= r.b) return 1;
		else if (this->c <= r.c) return 1;
		else if (this->a == r.a && this->b == r.b && this->c == r.c && this->coef <= r.coef) return 1;
		else return 0;
	};

	bool operator==(monomial& r) {
		if (this->a == r.a && this->b == r.b && this->c == r.c && this->coef == r.coef) return 1;
		else return 0;
	};

	bool operator!=(monomial& r) {
		return !(this == &r);
	};

	void print() {
		std::cout << coef << ' ' << a << ' ' << b << ' ' << c << std::endl;
	}
};
class polynomial {
private:
	List<monomial> pol;
public:
	polynomial() {};

	polynomial(double coef) { pol.push_front(monomial(coef, 0, 0, 0)); };

	polynomial(const polynomial& p) {
		List<monomial>pol(p.pol);
	};

	polynomial(const List<monomial>& l) {
		List<monomial> pol(l);
		pol.merge_sort();
	};

	~polynomial() {};

	polynomial(const std::initializer_list<monomial>& list) {
		for (auto it = list.begin(); it != list.end(); ++it) {
			pol.push_back(*it);
		}
		pol.merge_sort();
	};

	void add_monomial(monomial m) {
		pol.push_back(m);
		pol.merge_sort();
	}

	size_t size() {
		return pol.size();
	}

	monomial operator[](size_t pos) {
		return pol[pos];
	}
	polynomial operator=(const polynomial& rp) {
		pol = rp.pol;
		return pol;
	};

	polynomial operator=(const List<monomial>& list) {
		pol = list;
		return pol;
	};

	bool operator==(const polynomial rp) const {
		return pol == rp.pol;
	}

	polynomial operator+(const polynomial& rp) {
		polynomial res = pol.merge_sorted_lists(rp.pol);
		Node<monomial>* tmp = res.pol.get_first();
		while(tmp->next) {
			if (tmp->elem.equal_powers(tmp->next->elem) ) {
				tmp->elem.coef += tmp->next->elem.coef;
				auto tmp1 = tmp->next->next;
				delete tmp->next;
				tmp->next = tmp1;
			};
		}
		return res;
	};

	polynomial operator-(polynomial rp) {
		return *this + (rp * (-1));
	};

	polynomial operator*(double k) {
		Node<monomial>* tmp = pol.get_first();
		while (tmp->next) {
			tmp->elem.coef *= k;
		}
	};

	polynomial operator*(polynomial rp) {
		Node<monomial>* tmp1 = pol.get_first();
		Node<monomial>* tmp2 = rp.pol.get_first();
		polynomial res;
		while (tmp1) {
			while (tmp2) {
				res.pol.sorted_insert(tmp1->elem * tmp2->elem);
			}
		}				
		Node<monomial>* tmp = res.pol.get_first();
		while (tmp->next) {
			if (tmp->elem.equal_powers(tmp->next->elem)) {
				tmp->elem.coef += tmp->next->elem.coef;
				auto tmp1 = tmp->next->next;
				delete tmp->next;
				tmp->next = tmp1;
			};
		}
		return res;
	};

	//polynomial operator/(polynomial rp) {};
	
	//explicit polynomial(string str) {
	//	
	//};
};