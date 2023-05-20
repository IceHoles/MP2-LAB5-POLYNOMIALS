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

	monomial operator*(const monomial& m) const {
		return monomial(coef * m.coef, a + m.a, b + m.b, c + m.c);
	};

	monomial operator*(const double k) const {
		return monomial(coef * k, a, b, c);
	};

	bool is_divisible_by(const monomial& m) const {
		return (m.coef != 0 && this->a >= m.a && this->b >= m.b && this->c >= m.c);
	}
	monomial operator/(const monomial& m) const {
		return monomial(coef / m.coef, a - m.a, b - m.b, c - m.c);
	};

	bool equal_powers(monomial& r) {
		return (this->a == r.a && this->b == r.b && this->c == r.c);
	};

	double get_coef() { return coef; };

	bool operator>(monomial& r) {
		if (this->a == r.a) {
			if (this->b == r.b) {
				if (this->c == r.c) {
					return this->coef > r.coef;
				}
				else return this->c > r.c;
			}
			else return this->b > r.b;
		}
		else return this->a > r.a;
	};

	bool operator>=(monomial& r) {
		if (this->a == r.a) {
			if (this->b == r.b) {
				if (this->c <= r.c) { 
					return this->coef >= r.coef;
				}
				else return this->c >= r.c;
			}
			else return this->b >= r.b;
		}
		else return this->a >= r.a;
	};

	bool operator==(monomial& r) {
		return (this->a == r.a && this->b == r.b && this->c == r.c && this->coef == r.coef);
	};

	bool operator!=(monomial& r) {
		return !(*this == r);
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
		pol = p.pol;  
		pol.merge_sort();
	}

	polynomial(const monomial& m) {
		if (m.coef != 0) {
			pol.push_back(m);
		}
	};

	polynomial(const List<monomial>& l) {
		pol = l;
		pol.merge_sort();
	};

	~polynomial() {};

	polynomial(const std::initializer_list<monomial>& list) {
		for (auto m : list) {
			if (m.coef != 0) {
				pol.push_back(m);
			}
		}
		pol.merge_sort();
	}

	void add_monomial(monomial m) {
		if (m.coef != 0) {
			pol.push_back(m);
			pol.merge_sort();
		}
	}

	size_t size() const {
		return pol.size();
	}

	polynomial integ(char h) {
		polynomial res;
		for (auto mon : pol) {
			res.add_monomial(mon.integ(h));
		}
		return res;
	}

	polynomial diff(char h) {
		polynomial res;
		for (auto mon : pol) {
			if(mon.get_coef() != 0) res.add_monomial(mon.diff(h));			
		}
		return res;
	}

	monomial operator[](size_t pos) {
		return pol[pos];
	}
	polynomial operator=(const polynomial& rp) {
		pol = rp.pol;
		return pol;
	};

	polynomial operator=(const List<monomial>& list)  {
		pol = list;
		return pol;
	};

	bool operator==(const polynomial& rp) const {
		return pol == rp.pol;
	};

	bool is_divisible_by(const polynomial& divisor) const {
		auto m = pol.front();
		for (const auto n : divisor.pol) {
			if (!m.is_divisible_by(n)) return 0;
		}
		return 1;
	};

	polynomial operator+(const polynomial& rp) const {
		polynomial res = pol.merge_sorted_lists(rp.pol);
		Node<monomial>* tmp = res.pol.get_first();
		while(tmp && tmp->next) {
			if (tmp->elem.equal_powers(tmp->next->elem) ) {
				tmp->elem.coef += tmp->next->elem.coef;
				if (tmp->elem.coef == 0) {
					if (tmp == res.pol.get_first()) {
						res.pol.pop_front();
						res.pol.pop_front();
						tmp = res.pol.get_first();
					}
					else {
						Node<monomial>* tmp2 = res.pol.get_first();
						while (tmp2->next != tmp) { tmp2 = tmp2->next; }
						tmp2->next = tmp->next->next;
						delete tmp->next;
						delete tmp;
						tmp = tmp2;
					}
				}
				else {
					auto tmp1 = tmp->next->next;
					delete tmp->next;
					tmp->next = tmp1;
				}
			}
			else {
				tmp = tmp->next; 
			}
		}
		return res;
	};

	polynomial operator-(polynomial rp) const {
		return *this + (rp * (-1));
	};

	polynomial operator*(double k) {
		if (!pol.get_first()) return *this;
		Node<monomial>* tmp = pol.get_first();
		while (tmp) {
			tmp->elem.coef *= k;
			tmp = tmp->next;
		}
		return *this;
	};

	polynomial operator*(monomial& m) const {
		polynomial res;
		for (auto it : pol) {
			res.add_monomial(m * (it));
		}
		return res;
	}

	polynomial operator*(polynomial rp) const {
		polynomial res;
		for (Node<monomial>* tmp1 = pol.get_first(); tmp1; tmp1 = tmp1->next) {
			for (Node<monomial>* tmp2 = rp.pol.get_first(); tmp2; tmp2 = tmp2->next) {
				monomial m = tmp1->elem * tmp2->elem;
				res.pol.push_back(m);
			}
		}
		res.pol.merge_sort();
		Node<monomial>* tmp = res.pol.get_first();
		while (tmp && tmp->next) {
			if (tmp->elem.equal_powers(tmp->next->elem)) {
				tmp->elem.coef += tmp->next->elem.coef;
				auto tmp1 = tmp->next->next;
				delete tmp->next;
				tmp->next = tmp1;
			}
			else {
				tmp = tmp->next;
			}
		}
		return res;
	};

	polynomial operator/(const polynomial& divisor) const {	 
		polynomial quotient;
		polynomial div = *this;
		monomial dividend = div.pol.front();
		monomial divisorm = divisor.pol.front();
		while (div.is_divisible_by(divisor)) {
			monomial quotientm = dividend / divisorm;
			div = div - (divisor * quotientm);
			quotient.add_monomial(quotientm);
			dividend = div.pol.front();
		} 
		return quotient;
	}
};