#pragma once
#include <initializer_list>
#include <iterator>
#include <iostream>
#include <vector>

template <typename T>
struct Node {
	T elem;
	Node<T>* next;
	Node() {
		next = nullptr;
	}
	Node(T value) {
		elem = value;
		next = nullptr;
	}
};

template <typename T>
class List {
	Node<T>* first = nullptr;
	Node<T>* last = nullptr;
public:
	class iterator {				 //made an iterator and never used it im scared idk how to work with them

		Node<T>* ptr;

	public:

		iterator() {};

		iterator(Node<T>* p) {
			ptr = p;
		};

		iterator& operator++() {
			ptr = ptr->next;
			return *this;
		};

		iterator operator++(int) {
			iterator copy(this->ptr);
			ptr = ptr->next;
			return copy;
		};

		bool operator!=(const iterator& it2) {
			if (ptr != it2.ptr)
				return true;
			else
				return false;
		};

		bool operator==(const iterator& it2) {
			return !(*this != it2);
		};

		T& operator*() {
			return ptr->elem;
		};

		Node<T>* get_node() {
			return this->ptr;
		};
	};

	 iterator begin() const {
		return iterator(first);
	};

	 iterator end() const {
		return nullptr;
	};

	explicit List(size_t count) {
		first = new Node<T>();
		auto it = first;
		for (int i = 1; i < count; i++) {
			it->next = new Node<T>();
			last = it;
			it = it->next;
		}
	};

	List() :first(nullptr) {}

	List(const List<T>& list) {
		Node<T>* lptr = list.first;
		if (!list.first)
			return;
		first = new Node<T>(lptr->elem);
		last = first;
		lptr = lptr->next;	   
		while (lptr) {
			last->next = new Node<T>(lptr->elem);
			last = last->next;
			lptr = lptr->next; 
		}
	};

	List(List&& list) noexcept {
		this->first = list.first;
		list.first = nullptr;
	};

	List(Node<T>* list) {
		first = list;
	}

	List(const std::initializer_list<T>& list) {
		for (auto it = list.begin(); it != list.end(); ++it) {
			push_back(*it);
		}				
	};

	~List() {
		Node<T>* tmp = first;
		while (tmp) {
			Node<T>* tmp2 = tmp->next;
			delete tmp;
			tmp = tmp2;
		}
	};

	List& operator=(const List& list) {
		if (this == &list) return *this;
		List copy(list);
		this->clear();
		first = copy.first;
		last = copy.last;
		copy.first = nullptr;
		copy.last = nullptr;
		return *this;
	};

	List& operator=(List&& list) noexcept {
		Node<T>* tmp = list.first;
		list.first = this->first;
		this->first = tmp;
		return *this;
	};

	T& operator[](size_t n) const {
		Node<T>* it = first;
		for (int i = 0; i < n; i++) {
			it = it->next;
		}
		return it->elem;
	}

	T& operator[](size_t n) {
		Node<T>* it = first;
		for (int i = 0; i < n; i++) {
			it = it->next;
		}
		return it->elem;
	}

	bool operator==(const List& rlist) const{
		Node<T>* l = first;
		Node<T>* r = rlist.first;
		while (l && r) {
			if (l->elem != r->elem) return 0;
			l = l->next;
			r = r->next;
		}
		if (l == nullptr && r == nullptr) return 1;
		return 0;
	}

	bool empty() const {
		if (!first)
			return false;
		return true;
	};

	size_t size() const {
		Node<T>* tmp = first;
		size_t count = 0;
		while (tmp) {
			tmp = tmp->next;
			count++;
		}
		return count;
	};

	Node<T>* get_first() const { return this->first; }

	Node<T>* get_last() const { return this->last; }

	Node<T>* get_node(size_t pos) {
		Node<T>* tmp = first;
		for (int i = 0; i < pos; i++) tmp = tmp->next;
		return tmp;
	}

	void pop_front() {
		if (first) {
			Node<T>* tmp = first;
			if (last == first) last = nullptr;
			first = first->next;
			delete tmp;
		}
	}

	void clear() {
		Node<T>* tmp = this->first;
		while (tmp) {
			Node<T>* tmp2 = tmp->next;
			delete tmp;
			tmp = tmp2;
		}
		first = nullptr;
		last = nullptr;
	};

	void erase_after(Node<T>* prev) {
		if (prev && prev->next) {
			Node<T>* tmp = prev->next;
			prev->next = prev->next->next;
			delete tmp;
		}
	};

	void erase(Node<T>* curr) {
		Node<T>* tmp = first; 
		if (curr->next) {
			while (tmp->next != curr) {
				tmp = tmp->next;
			}
			curr->next = curr->next->next;
			delete curr;
		}
		else if (tmp->next) {
			while (tmp->next != curr) {
				tmp = tmp->next;
			}
			last = tmp;
			tmp->next = nullptr;
			delete curr;
		}
		else {
			first = nullptr;
			last = nullptr;
			delete curr;
		}
	};

	List merge(const List& list) const {
		List res(*this);
		List temp(list);
		if (res.last) {
			res.last->next = temp.first;
			temp.first = nullptr;
		}
		else {
			res.first = temp.first;
			temp.first = nullptr;
		}  
		temp.first = temp.last = nullptr;
		return res;
	};

	//void sort();		// O(n log n)	merge sort task12

	void insert_after(Node<T>* prev, T value) {
		if (!prev) throw std::invalid_argument("L");
		Node<T>* tmp = prev->next;
		prev->next = new Node<T>();
		prev->next->elem = value;
		prev->next->next = tmp;
		if (prev == last) last = last->next;
	};

	void push_front(T value) {
		Node<T>* tmp = new Node<T>(value);
		tmp->next = first;
		first = tmp;
	}

	void push_back(T value) {
		if (last) {
			last->next = new Node<T>(value);
			last = last->next;
		}
		else first = last = new Node<T>(value);
	}

	void reverse() {
		Node<T>* tmp = first;
		Node<T>* it = first;
		Node<T>* tmp1 = nullptr;
		while (it) {
			tmp = it->next;
			it->next = tmp1;
			tmp1 = it;
			it = tmp;
		}
		first = tmp1;
	};

	void reverse_print() {
		this->reverse();
		for (auto it = first; it != it.end(); ++it) {
			std::cout << it->elem << ' ';
		}
		std::cout << std::endl;
		this->reverse;
	};

	T front() const { return first->elem; }

	T front() { return first->elem; }

	std::vector<T> middle() {
		Node<T>* tmp1 = first;
		Node<T>* tmp2 = first;
		Node<T>* prev = first;
		std::vector<T> res;
		bool odd = 0;
		while (tmp2) {
			if (tmp2->next)
				tmp2 = tmp2->next->next;
			else {
				odd = 1;
				break;
			}
			prev = tmp1;
			tmp1 = tmp1->next;
		}
		if (odd) {
			res.push_back(tmp1->elem);
		}
		else {
			res.push_back(prev->elem);
			res.push_back(tmp1->elem);
		}
		return res;
	}

	void erase_middle() {
		Node<T>* tmp1 = first;
		Node<T>* tmp2 = first;
		Node<T>* prev = first;
		bool odd = 0;
		while (tmp2) {
			if (tmp2->next)
				tmp2 = tmp2->next->next;
			else {
				odd = 1;
				break;
			}
			prev = tmp1;
			tmp1 = tmp1->next;
		}
		if (odd) {
			erase_after(tmp1);
		}
		else {
			erase_after(tmp1);
			erase_after(prev);
		}
	}

	List<T> merge_sorted_lists(const List& list) const {
		List<T> l;
		Node<T>* ptr1 = first;
		Node<T>* ptr2 = list.first;
		while (ptr1 && ptr2) {
			if (ptr1->elem >= ptr2->elem) {
				l.push_back(ptr1->elem);
				ptr1 = ptr1->next;
			}
			else {
				l.push_back(ptr2->elem);
				ptr2 = ptr2->next;
			}
		}
		while (ptr2) {
			l.push_back(ptr2->elem);
			ptr2 = ptr2->next;
		}
		while (ptr1) {
			l.push_back(ptr1->elem);
			ptr1 = ptr1->next;
		}
		return l;
	};

	void sorted_insert(T value) {
		if (first != nullptr) {
			Node<T>* tmp = first;
			while (tmp != last && tmp->elem < value) {
				tmp = tmp->next;
			}			 
			insert_after(tmp, value);
		}
		else push_back(value);
	}

	void erase_last_duplicate(T value) {
		if (first != nullptr) {
			Node<T>* tmp = first;
			auto prev = tmp;
			while (tmp->next) {
				if (tmp->next->elem == value) {
					prev = tmp;
				}
				tmp = tmp->next;
			}
			prev->next = prev->next->next;
		}
	}

	T& at_end(size_t n) {
		Node<T>* it = first;
		Node<T>* fast = first;
		size_t i = 1;
		while (fast) {
			if (i > n) {
				it = it->next;
			}
			fast = fast->next;
			i++;
		}
		return it->elem;
	}

	void cyclic_shift(size_t n) {
		if (first != nullptr) {
			Node<T>* it = first;
			Node<T>* fast = first;
			Node<T>* prev = first;
			Node<T>* itprev = first;
			size_t i = 1;
			while (fast) {
				if (i > n) {
					itprev = it;
					it = it->next;
				}
				prev = fast;
				fast = fast->next;
				i++;
			}
			prev->next = first;
			first = it;
			itprev->next = nullptr;
		}
	}

	void reverse_nodes(size_t sz, size_t pos) {
		Node<T>* tmp = first;
		Node<T>* it = first;
		Node<T>* prev = nullptr;
		Node<T>* tmp1 = nullptr;
		Node<T>* tmp2 = nullptr;
		for (int i = 1; i < pos; i++) {
			prev = tmp;
			tmp = tmp->next;
		}
		it = tmp;
		tmp2 = tmp;	   // 10  -> 15
		for (int i = 0; i < sz; i++) {
			tmp = it->next;
			it->next = tmp1;
			tmp1 = it;
			it = tmp;
		}
		prev->next = tmp1;
		tmp2->next = tmp;
	}

	void erase_duplicates() {
		if (first == nullptr) return;
		Node<T>* tmp = first;
		Node<T>* tmp1;
		Node<T>* prev;
		while (tmp) {
			tmp1 = tmp;
			while (tmp1->next) {
				prev = tmp1;
				tmp1 = tmp1->next;
				if (tmp1->elem == tmp->elem) {
					tmp1 = prev;
					erase_after(prev);
				}
			}
			tmp = tmp->next;
		}
	}

	void print() {
		auto tmp = first;
		while (tmp) {
			std::cout << tmp->elem << ' ';
			tmp = tmp->next;
		}
		std::cout << std::endl;
	}

	void merge_sort() {
		if (!first) return;
		if (!first->next) return;
		else {
			Node<T>* center = first;
			Node<T>* tmp = first;
			Node<T>* prev = first;
			while (tmp && tmp->next) {
				tmp = tmp->next->next;
				prev = center;
				center = center->next;
			}
			List rightList(prev->next);
			prev->next = nullptr;
			merge_sort();
			rightList.merge_sort();
			*this = merge_sorted_lists(rightList);
			last = first;
			while (last->next) last = last->next;
		}
	};
	void node_print(Node<T>* nod) {
		Node<T>* tmp = nod;
		while (tmp) {
			std::cout << tmp->elem << ' ';
			tmp = tmp->next;
		}
		std::cout << std::endl;
	}
};