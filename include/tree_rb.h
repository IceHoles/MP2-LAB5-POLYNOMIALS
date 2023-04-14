#pragma once
#include <iostream>

	//  This implementation includes the `Insert` function to insert a key - value pair into the tree, 
	//  as well as the `FixInsert` function to balance the tree according to Red - Black Tree rules.
	//  It also includes the `RotateLeft` and `RotateRight` functions to perform left and right rotations, respectively.
	//	Finally, it includes the `InorderTraversal` function to traverse the tree in - order and print out the key - value pairs.
	//	Note that this implementation assumes that the `TKey` type has an overloaded `<` operator for comparison.

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

	// Essentialy a print() function
	void InorderTraversalHelper(TNode* node) {
		if (node != nullptr) {
			InorderTraversalHelper(node->pLeft);
			std::cout << node->data.key << ": " << node->data.value << std::endl;
			InorderTraversalHelper(node->pRight);
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

	// The `Delete` function works by first finding the node to delete using the `FindNode` function.
	//If the key is not found, the function returns immediately without doing anything.
	//Otherwise, the function saves a pointer to the node to be deleted as `z`,and it saves a pointer to its child node as `x`.
	//If `z` has only one child, the function calls the `Transplant` function to replace `z` with `x`.
	//If `z` has two children, the function finds the successor node `y` 
	//(i.e., the node with the smallest key in the right subtree of `z`), saves a pointer to `y`'s right child as `x`,
	//and replaces `z` with `y` using the `Transplant` function.
	//Then, the function copies `z`'s data into `y`,and updates `y`'s left child to be `z`'s left child.
	//If `y` is not a direct child of `z`, the function updates `y`'s right child to be `z`'s right child, 
	//and updates the parent pointer of `x` to point to `y`.
	//Finally, if the original color of `y` was black, the function calls `FixDelete` to restore
	//the properties of the Red - Black Tree.
	//The `FixDelete` function works by repeatedly performing rotations and color flips on the nodes in the path
	//from `x` to the root of the tree until the Red - Black Tree properties are restored.

	void FixDelete(TNode* x) {
		while (x != pRoot && x->isRed == false) {
			if (x == x->pParent->pLeft) {
				TNode* w = x->pParent->pRight;
				if (w->isRed) {
					w->isRed = false;
					x->pParent->isRed = true;
					RotateLeft(x->pParent);
					w = x->pParent->pRight;
				}
				if (w->pLeft->isRed == false && w->pRight->isRed == false) {
					w->isRed = true;
					x = x->pParent;
				}
				else {
					if (w->pRight->isRed == false) {
						w->pLeft->isRed = false;
						w->isRed = true;
						RotateRight(w);
						w = x->pParent->pRight;
					}
					w->isRed = x->pParent->isRed;
					x->pParent->isRed = false;
					w->pRight->isRed = false;
					RotateLeft(x->pParent);
					x = pRoot;
				}
			}
			else {
				TNode* w = x->pParent->pLeft;
				if (w->isRed) {
					w->isRed = false;
					x->pParent->isRed = true;
					RotateRight(x->pParent);
					w = x->pParent->pLeft;
				}
				if (w->pRight->is   false && w->pLeft->isRed == false) {
					w->isRed = true;
					x = x->pParent;
				}
				else {
					if (w->pLeft->isRed == false) {
						w->pRight->isRed = false;
						w->isRed = true;
						RotateLeft(w);
						w = x->pParent->pLeft;
					}
					w->isRed = x->pParent->isRed;
					x->pParent->isRed = false;
					w->pLeft->isRed = false;
					RotateRight(x->pParent);
					x = pRoot;
				}
			}
		}
		x->isRed = false;
	}

public:

	TSearchTreeTab1e() : pRoot(nullptr) {}

	void Print() {
		std::cout << "Table\n";
		Print(pRoot);
	}

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
			if (z->data.key < x->data.key) {
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

	void InorderTraversal() {
		InorderTraversalHelper(pRoot);
	}

	void Delete(const TKey& key) {
		TNode* z = FindNode(key);
		if (z == nullptr) {
			return; // key not found, nothing to delete
		}
		TNode* x = nullptr;
		TNode* y = z;
		bool yOriginalColor = y->isRed;
		if (z->pLeft == nullptr) {
			x = z->pRight;
			Transplant(z, z->pRight);
		}
		else if (z->pRight == nullptr) {
			x = z->pLeft;
			Transplant(z, z->pLeft);
		}
		else {
			y = MinimumNode(z->pRight);
			yOriginalColor = y->isRed;
			x = y->pRight;
			if (y->pParent == z) {
				x->pParent = y;
			}
			else {
				Transplant(y, y->pRight);
				y->pRight = z->pRight;
				y->pRight->pParent = y;
			}
			Transplant(z, y);
			y->pLeft = z->pLeft;
			y->pLeft->pParent = y;
			y->isRed = z->isRed;
		}
		if (yOriginalColor == false) {
			FixDelete(x);
		}
		delete z;
	}
};