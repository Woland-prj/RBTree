#pragma once

class RBTree {
private:
	using DataType = int;
	enum Situation {
		rightRotate, leftRotate, bigRightRotate, bigLeftRotate, colorSwap, none
	};
	enum NodeColor {	
		red, black
	};
	struct Node {
		DataType key;
		NodeColor color;
		Node* lhs;
		Node* rhs;
	};

	Node* root;

	Situation CheckBalanced(Node* ptr) {
		if (ptr->lhs && ptr->rhs && ptr->lhs->color == red && ptr->rhs->color == red)
			if ((ptr->lhs->lhs && ptr->lhs->lhs->color == red) || (ptr->lhs->rhs && ptr->lhs->rhs->color == red) || (ptr->rhs->lhs && ptr->rhs->lhs->color == red) || (ptr->rhs->rhs && ptr->rhs->rhs->color == red))
				return colorSwap;
		if (ptr->lhs && ptr->lhs->color == red) {
			if (ptr->lhs->lhs && ptr->lhs->lhs->color == red)
				return rightRotate;
			if (ptr->lhs->lhs && ptr->lhs->lhs->color == red)
				return bigRightRotate;
		}
		if (ptr->rhs && ptr->rhs->color == red) {
			if (ptr->rhs->rhs && ptr->rhs->rhs->color == red)
				return leftRotate;
			if (ptr->rhs->lhs && ptr->rhs->lhs->color == red)
				return bigLeftRotate;
		}
		return none;
	}

	void BalanceTree(Node*& ptr, Node*& parent) {
		switch (CheckBalanced(ptr))
		{
		case colorSwap:
			//ColorSwap(parent);
			break;
		case rightRotate:
			//RightRotate(parent);
			break;
		case leftRotate:
			//LeftRotate(parent);
			break;
		case bigRightRotate:
			//LeftRotate(parent->rhs);
			//RightRotate(parent);
			break;
		case bigLeftRotate:
			//RightRotate(parent->lhs);
			//LeftRotate(parent);
			break;
		default:
			break;
		}
	}

	void RightRotate(Node*& ptr) {
		
	}

	void InsertRecursive(DataType key, Node*& ptr) {
		if (ptr == nullptr) {
			ptr = new Node;
			ptr->key = key;
			ptr->lhs = nullptr;
			ptr->rhs = nullptr;
			ptr->color = red;
		}
		else {
			InsertRecursive(key, ptr);
			BalanceTree(ptr->l);
			BalanceTree(ptr->rhs);
		}
	}

public:
	RBTree() {
		root = nullptr;
	}

	void Insert(DataType key) {
		InsertRecursive(key, root);
	}
};