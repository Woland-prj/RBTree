#pragma once

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
			else
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

	void BalanceTree(Node*& ptr) {
		if (isSwapColor(ptr)) {
			// TODO: ColoorSwap
			return;
		}
		if (isRightRotate(ptr)) {
			if (isRed(ptr->lhs->lhs))
				// TODO: RightRotate
				return;
			if (isRed(ptr->lhs->rhs))
				// TODO: LeftRotate
				// TODO: RightRotate
				return;
		}
		if (isLeftRotate(ptr)) {
			if (isRed(ptr->rhs->rhs))
				// TODO: LeftRotate
				return;
			if (isRed(ptr->rhs->lhs))
				// TODO: RightRotate
				// TODO: LeftRotate
				return;
		}
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
			BalanceTree(ptr);
			BalanceTree(ptr);
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