#include "ActionStack.h"
#include <iostream>

ActionStack::ActionStack() {
	head = nullptr;
	count_ = 0;
}

ActionStack::~ActionStack() {
	makeEmpty();
}

bool ActionStack::isEmpty() const {
	return head == nullptr;
}

void ActionStack::push( TubeSet* data, Stack** other,int no_col) {
	Node* newNode = new Node(data,other,no_col);
	newNode->next = head;
	head = newNode;
	count_++;
}


TubeSet* ActionStack::pop() {
	if (isEmpty()) {
		std::cerr << "Error: Stack is empty\n";
		return nullptr;
	}

	Node* temp = head;
	head = head->next;
	TubeSet* data = temp->tubeArray;
	delete temp;
	count_--;
	return data;
}

TubeSet* ActionStack::top() const {
	if (isEmpty()) {
		std::cerr << "Error: Stack is empty\n";
		return nullptr;
	}
	return head->tubeArray;
}

int ActionStack::count() const {
	return count_;
}

void ActionStack::makeEmpty() {
	while (!isEmpty()) {
		Node* temp = head;
		wxLogDebug("inside makeEmpty: to delete %p", temp->tubeArray);
		head = head->next;
		delete temp;
		count_--;
	}
}
