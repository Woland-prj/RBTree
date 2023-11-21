#pragma once
#include <iostream>

class RBTree {
private:
	using DataType = int;
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

	bool isSwapColor(Node* ptr) {
		if (ptr->lhs && ptr->rhs && ptr->lhs->color == red && ptr->rhs->color == red)
			if ((ptr->lhs->lhs && ptr->lhs->lhs->color == red) || (ptr->lhs->rhs && ptr->lhs->rhs->color == red) || (ptr->rhs->lhs && ptr->rhs->lhs->color == red) || (ptr->rhs->rhs && ptr->rhs->rhs->color == red))
				return true;
		return false;
	}

	bool isRightRotate(Node* ptr) {
		return ptr->lhs && ptr->lhs->color == red && (ptr->lhs->lhs || ptr->lhs->rhs);
	}

	bool isLeftRotate(Node* ptr) {
		return ptr->rhs && ptr->rhs->color == red && (ptr->rhs->rhs || ptr->rhs->lhs);
	}

	bool isRed(Node* ptr) {
		return ptr && ptr->color == red;
	}

	void RightRotate(Node*& ptr) {
		Node* temp = ptr->lhs->rhs;
		ptr->lhs->rhs = ptr;
		ptr = ptr->lhs;
		ptr->rhs->lhs = temp;
	}

	void LeftRotate(Node*& ptr) {
		Node* temp = ptr->rhs->lhs;
		ptr->rhs->lhs = ptr;
		ptr = ptr->rhs;
		ptr->lhs->rhs = temp;
	}

	void ColorSwap(Node*& ptr) {
		ptr->color = red;
		ptr->lhs->color = black;
		ptr->rhs->color = black;
	}

	void BalanceTree(Node*& ptr) {
		if (isSwapColor(ptr)) {
			std::cout << "color swap" << std::endl;
			ColorSwap(ptr);
			return;
		}
		if (isRightRotate(ptr)) {
			std::cout << "right rotate" << std::endl;
			if (isRed(ptr->lhs->lhs)) {
				RightRotate(ptr);
				ptr->color = black;
				ptr->rhs->color = red;
				return;
			}
			if (isRed(ptr->lhs->rhs)){
				LeftRotate(ptr->lhs);
				RightRotate(ptr);
				ptr->color = black;
				ptr->rhs->color = red;
				return;
			}
		}
		if (isLeftRotate(ptr)) {
			std::cout << "left rotate" <<std::endl;
			if (isRed(ptr->rhs->rhs)) {
				LeftRotate(ptr);
				ptr->color = black;
				ptr->lhs->color = red;
				std::cout << ptr->color << ' ' << ptr->lhs->color << ' ' << ptr->key << ' ' << ptr->lhs->key <<std::endl;
				return;
			}
			if (isRed(ptr->rhs->lhs)){
				std::cout << "big rotate " << ptr->rhs->lhs->key << ' ' << ptr->key <<std::endl;
				RightRotate(ptr->rhs);
				LeftRotate(ptr);
				ptr->color = black;
				ptr->rhs->color = red;
				return;
			}
		}
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
			key <= ptr->key 
				? InsertRecursive(key, ptr->lhs) 
				: InsertRecursive(key, ptr->rhs);
			BalanceTree(ptr);
		}
	}

	void PrintRecursive(Node* ptr) {
		if (ptr != nullptr) {
			std::cout 
				<< ptr->key 
				<< ' ' 
				<< ptr->color 
				<< std::endl;
			PrintRecursive(ptr->lhs);
			std::cout << std::endl;
			PrintRecursive(ptr->rhs);
			std::cout << std::endl;
		}
	}

public:
	RBTree() {
		root = nullptr;
	}

	void Insert(DataType key) {
		InsertRecursive(key, root);
		if (root->color == red) 
			root->color = black;
	}

	void Print() {
		PrintRecursive(root);
	}
};