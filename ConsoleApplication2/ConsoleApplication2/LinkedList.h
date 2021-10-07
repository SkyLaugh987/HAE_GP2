#pragma once
class LinkedList {

	struct Node {

		int data;
		Node* next;
	};

	Node* head, * tail;
	Node* current;
	int numberOfNodes;

public:

	LinkedList() {
		head = nullptr;
		tail = nullptr;
		current = nullptr;
		numberOfNodes = 0;
	}

	void AddFront(int newData) {
		Node* newNode = new Node;
		newNode->data = newData;
		newNode->next = head;
		if (head == NULL) {

			head = newNode;
			tail = newNode;
		}
		else {

			head = newNode;
		}
		numberOfNodes++;
	}

	void AddLast(int n) {
		Node* newN = new Node;
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
		numberOfNodes++;
	}

	void Insert(int newData, int pos) {
		Node* newN = new Node;
		newN->data = newData;
		newN->next = nullptr;
		current = head;

		if (pos <= 0) {
			AddFront(newData);
		}
		if (pos >= numberOfNodes) {
			AddLast(newData);
		}

		for (int i = 0; i < pos - 1; i++) {

			current = current->next;
		}
		newN->next = current->next;
		current->next = newN;
	}

	void RemoveFirst() {
		if (head == NULL)
			return;
		if (head->next == NULL) {
			delete head;
			return;
		}
		Node* newFirst = head->next;
		delete head;
		head = newFirst;
		numberOfNodes--;
	}

	void RemoveLast() {

		if (head == NULL)
			return;
		if (head->next == NULL) {
			delete head;
			return;
		}

		Node* secondLast = head;

		while (secondLast->next->next != NULL) {
			secondLast = secondLast->next;
		}
		delete secondLast->next;
		secondLast->next = NULL;
		numberOfNodes--;
	}
	void RemoveAll() {
		while (numberOfNodes > NULL) {
			RemoveFirst();
		}
	}



	void PrintList() {
		Node* node = head;
		while (node != NULL) {
			printf("%d ", node->data);
			node = node->next;
		}
	}

};