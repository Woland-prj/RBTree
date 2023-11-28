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

	bool isColorSwap(Node* ptr) {
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
		if (isColorSwap(ptr)) {
			ColorSwap(ptr);
			return;
		}
		if (isRightRotate(ptr)) {
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
			if (isRed(ptr->rhs->rhs)) {
				LeftRotate(ptr);
				ptr->color = black;
				ptr->lhs->color = red;
				return;
			}
			if (isRed(ptr->rhs->lhs)){
				RightRotate(ptr->rhs);
				LeftRotate(ptr);
				ptr->color = black;
				ptr->lhs->color = red;
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

	std::string GetLvl(int lvl) {
		std::string strlvl = "";
		for (int i = 0; i < lvl; i++)
			strlvl += '.';
		return strlvl;
	}

	void PrintRecursive(Node* ptr, int& lvl) {
		if (ptr != nullptr) {
			std::string color;
			ptr->color == red ? color = " red": color = " black";
			std::cout 
				<< GetLvl(lvl)
				<< ptr->key 
				<< color
				<< std::endl;
			lvl++;
			PrintRecursive(ptr->lhs, lvl);
			PrintRecursive(ptr->rhs, lvl);
			lvl--;
		}
	}

	void DestructRecursive(Node*& ptr) {
		if (ptr != nullptr) {
			DestructRecursive(ptr->lhs);
			DestructRecursive(ptr->rhs);
			delete ptr;
			ptr = nullptr;
		}
	}

	DataType findNextKey(Node*& ptr) {
		if (ptr->lhs) {
			findNextKey(ptr->lhs);
		} else {
			Node* temp = ptr->rhs;
			DataType key = ptr->key;
			delete ptr;
			ptr = temp;
			return key;
		}
	}

	void DeleteRecursive(Node*& ptr, Node*& delPtr, DataType delKey) {
		if (ptr != nullptr) {
			DeleteRecursive(ptr, delPtr, delKey);
			if (delPtr != nullptr) {
				if (!delPtr->lhs || !delPtr->rhs) {
					if (!delPtr->lhs)
						ptr = delPtr->rhs;
					if (!delPtr->rhs) 
						ptr = delPtr->lhs;
					if (!delPtr->lhs && !delPtr->rhs) 
						ptr = nullptr;
					NodeColor delColor = delPtr->color;
					delete delPtr;
					delPtr = nullptr;
					if (delColor == black)
						//TODO: fixDeleating;
					return;
				}
				DataType nextKey = findNextKey(delPtr->rhs);
				ptr->key = nextKey;
			}
			if (ptr->key == delKey)
				delPtr = ptr;
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
		int lvl = 0;
		PrintRecursive(root, lvl);
	}

	~RBTree() {
		DestructRecursive(root);
	}

	void Delete(DataType delKey) {
		Node* delPtr = nullptr;
		DeleteRecursive(root, delPtr, delKey);
	}
};