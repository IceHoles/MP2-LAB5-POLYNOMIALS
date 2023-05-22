#pragma once
#include <iostream>
#include <sstream>	  

enum Color { RED, BLACK };

template <typename TKey, typename TValue>
class TSearchTreeTab1e {
	struct TTab1eRec {
		TKey key;
		TValue value;
	};
	struct TNode {
		TTab1eRec data;
		TNode* pLeft;
		TNode* pRight;
		TNode* pParent;
		Color color;
	};
	TNode* pRoot;		

	TNode* FindNode(TKey key, TNode* pNode) {
		if (pNode == nullptr) return nullptr;
		if (key < pNode->data.key) pNode = FindNode(key, pNode->pLeft);
		if (key > pNode->data.key) pNode = FindNode(key, pNode->pRight);
		return pNode;
	}

	void RotateLeft(TNode* x) {
		TNode* y = x->pRight;
		x->pRight = y->pLeft;
		if (y->pLeft != nullptr) {
			y->pLeft->pParent = x;
		}
		y->pParent = x->pParent;
		if (x->pParent == nullptr) {
			pRoot = y;
		}
		else if (x == x->pParent->pLeft) {
			x->pParent->pLeft = y;
		}
		else {
			x->pParent->pRight = y;
		}
		y->pLeft = x;
		x->pParent = y;
	}

	void RotateRight(TNode* x) {
		TNode* y = x->pLeft;
		x->pLeft = y->pRight;
		if (y->pRight != nullptr) {
			y->pRight->pParent = x;
		}
		y->pParent = x->pParent;
		if (x->pParent == nullptr) {
			pRoot = y;
		}
		else if (x == x->pParent->pRight) {
			x->pParent->pRight = y;
		}
		else {
			x->pParent->pLeft = y;
		}
		y->pRight = x;
		x->pParent = y;
	}

	void InorderTraversalHelper(TNode* pNode, std::stringstream& ss) {
		if (pNode != nullptr) {
			InorderTraversalHelper(pNode->pLeft, ss);
			ss << pNode->data.key << " = " << pNode->data.value << std::endl;
			InorderTraversalHelper(pNode->pRight, ss);
		}
	}

	void FixInsert(TNode* z) {
		while (z->pParent != nullptr && z->pParent->color == RED) {
			if (z->pParent == z->pParent->pParent->pLeft) {
				TNode* y = z->pParent->pParent->pRight;
				if (y != nullptr && y->color == RED) {
					z->pParent->color = BLACK;
					y->color = BLACK;
					z->pParent->pParent->color = RED;
					z = z->pParent->pParent;
				}
				else {
					if (z == z->pParent->pRight) {
						z = z->pParent;
						RotateLeft(z);
					}
					z->pParent->color = BLACK;
					z->pParent->pParent->color = RED;
					RotateRight(z->pParent->pParent);
				}
			}
			else {
				TNode* y = z->pParent->pParent->pLeft;
				if (y != nullptr && y->color == RED) {
					z->pParent->color = BLACK;
					y->color = BLACK;
					z->pParent->pParent->color = RED;
					z = z->pParent->pParent;
				}
				else {
					if (z == z->pParent->pLeft) {
						z = z->pParent;
						RotateRight(z);
					}
					z->pParent->color = BLACK;
					z->pParent->pParent->color = RED;
					RotateLeft(z->pParent->pParent);
				}
			}
		}
		pRoot->color = BLACK;
	}

	void FixDelete(TNode* x) {
		while (x != pRoot && x->color == BLACK) {
			if (x == x->pParent->pLeft) {
				TNode* w = x->pParent->pRight;
				if (w->color == RED) {
					w->color = BLACK;
					x->pParent->color = RED;
					RotateLeft(x->pParent);
					w = x->pParent->pRight;
				}
				if (w->pLeft->color == BLACK && w->pRight->color == BLACK) {
					w->color = RED;
					x = x->pParent;
				}
				else {
					if (w->pRight->color == BLACK) {
						w->pLeft->color = BLACK;
						w->color = RED;
						RotateRight(w);
						w = x->pParent->pRight;
					}
					w->color = x->pParent->color;
					x->pParent->color = BLACK;
					w->pRight->color = BLACK;
					RotateLeft(x->pParent);
					x = pRoot;
				}
			}
			else {
				TNode* w = x->pParent->pLeft;
				if (w->color == RED) {
					w->color = BLACK;
					x->pParent->color = RED;
					RotateRight(x->pParent);
					w = x->pParent->pLeft;
				}
				if (w->pRight->color == BLACK && w->pLeft->color == BLACK) {
					w->color = RED;
					x = x->pParent;
				}
				else {
					if (w->pLeft->color == BLACK) {
						w->pRight->color = BLACK;
						w->color = RED;
						RotateLeft(w);
						w = x->pParent->pLeft;
					}
					w->color = x->pParent->color;
					x->pParent->color = BLACK;
					w->pLeft->color = BLACK;
					RotateRight(x->pParent);
					x = pRoot;
				}
			}
		}
		x->color = BLACK;
	}

	void Transplant(TNode* u, TNode* v) {
		if (u->pParent == nullptr) {
			pRoot = v;
		}
		else if (u == u->pParent->pLeft) {
			u->pParent->pLeft = v;
		}
		else {
			u->pParent->pRight = v;
		}
		if (v != nullptr) {
			v->pParent = u->pParent;
		}
	}
public:

	TSearchTreeTab1e() : pRoot(nullptr) {}

	TValue* Find(TKey key) {				  
		TNode* pNode = FindNode(key, pRoot);
		if (pNode== nullptr) return nullptr;
		return &pNode->data.value;	 
	}


	void Insert(const TKey& key, const TValue& value) {
		TNode* z = new TNode{ {key, value}, nullptr, nullptr, nullptr, RED };
		TNode* y = nullptr;
		TNode* x = pRoot;
		while (x != nullptr) {
			y = x;
			if (z->data.key == x->data.key) {
				x->data.value = z->data.value;
				delete z;
				return;
			}
			else if (z->data.key < x->data.key) {
				x = x->pLeft;
			}
			else {
				x = x->pRight;
			}
		}
		z->pParent = y;
		if (y == nullptr) {
			pRoot = z;
		}
		else if (z->data.key < y->data.key) {
			y->pLeft = z;
		}
		else {
			y->pRight = z;
		}
		FixInsert(z);
	}

	std::stringstream InorderTraversal() {
		std::stringstream ss;
		InorderTraversalHelper(pRoot, ss);
		return ss;
	}

	void print() {
		std::stringstream ss;
		InorderTraversalHelper(pRoot, ss);
		std::cout << "tree contains: " << std::endl << ss.str();
	}

	void Delete(const TKey& key) {
		TNode* z = FindNode(key,pRoot);
		if (z == nullptr) {
			return;
		}
		TNode* x = nullptr;
		TNode* y = nullptr;
		Color yOriginalColor = z->color;

		if (z->pLeft == nullptr || z->pRight == nullptr) {
			y = z;
		}
		else {
			y = z->pRight;
			while (y->pLeft != nullptr) {
				y = y->pLeft;
			}
		}
		if (y->pLeft != nullptr) {
			x = y->pLeft;
		}
		else {
			x = y->pRight;
		}
		if (x != nullptr) {
			x->pParent = y->pParent;
		}
		if (y->pParent == nullptr) {
			pRoot = x;
		}
		else {
			if (y == y->pParent->pLeft) {
				y->pParent->pLeft = x;
			}
			else {
				y->pParent->pRight = x;
			}
		}
		if (y != z) {
			z->data = y->data;
		}
		if (yOriginalColor == BLACK && x != nullptr) {
			FixDelete(x);
		}
		else if (yOriginalColor == BLACK) {
			FixDelete(y->pParent);
		}
		delete y;
	}
};