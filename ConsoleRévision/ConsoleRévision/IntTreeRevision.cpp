#include"IntTreeRevision.h"

IntTreeRevision * create(int value)
{
	IntTreeRevision* node = (IntTreeRevision*)malloc(sizeof(IntTreeRevision));
	node->value = value;
	node->left = node->right = nullptr;
	return node;
}

int count(IntTreeRevision* head) {
	if (!head) return 0;
	return 1 + count(head->left) + count(head->right);
}

IntTreeRevision* insert(IntTreeRevision* head, int val) {
	if (!head) return create(val);
	if (head->value < val)
		return insert(head->right, val);
	if (head->value > val)
		return insert(head->left, val);
	return head;
}
IntTreeRevision* remove(IntTreeRevision* head, int val) {
	if (!head) return head;
	if (head->value == val) {
		IntTreeRevision* merged = merge(head->left, head->right);
	}
	else
	{
		head->left = remove(head->left, val);
		head->right = remove(head->right, val);
	}
	return head;
}

IntTreeRevision* merge(IntTreeRevision* a, IntTreeRevision* b) {
	if (!a) return b;
	if (!b) return a;
	IntTreeRevision * left = a->left;
	IntTreeRevision * right = a->right;
	int value = a->value;
	free(a);

	b = insert(b, value);
	b = merge(left, b);
	b = merge(right, b);
}