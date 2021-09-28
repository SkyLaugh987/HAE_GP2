#pragma once


class LinkedList {

struct Node {

	int data;
	Node * next;
};

	Node *head, *tail;

public:

	LinkedList() {
		head = nullptr;
		tail = nullptr;
	}

	void Add(int n) {
		Node * newN = new Node;
		newN->data = n;
		newN->next = nullptr;

		if (head == nullptr) {
			head = newN;
			tail = newN;
		}
		else {
			tail->next = newN;
			tail = tail->next;
		}
	}
	void PrintList() {
		Node *node = head;
		while (node != NULL) {
			printf("%d ", node->data);
			node = node->next;
		}
	}

};