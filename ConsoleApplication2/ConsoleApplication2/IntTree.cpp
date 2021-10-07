#include"IntTree.h"
IntTree* create(int value) {
	
	IntTree* node = (IntTree*)malloc(sizeof(IntTree));
	node->value = value;
	node->left = node->right = nullptr;
	return node;
}

int count(IntTree* head) {
	
	if(!head) return 0;
	return 1 + count(head->left) + count(head->right);
}

IntTree* insert(IntTree* head, int val) {
	if (!head) return create(val);
	
	if (head->value > val) 
		head->left =  insert(head->left, val);
	else
		head->right = insert(head->right, val);
	return head;
}

IntTree* remove(IntTree* head, int val) {
	if (!head) return head;
	
	if (head->value == val) {
		IntTree* merged = merge(head->left, head->right);
	}
	else {
		head->left = remove(head->left, val);
		head->right = remove(head->right, val);
	}
	return head;
}
IntTree* merge(IntTree* a, IntTree* b) {
	if (!a)return b;
	if (!b)return a;

	IntTree* left = a->left;
	IntTree* right = a->right;
	int value = a->value;
	free(a);

	b = insert(b, value);
	b = merge(left, b);
	b = merge(right, b);
	return b;
}