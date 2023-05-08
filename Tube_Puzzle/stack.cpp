// Stack.cpp - Implementation file for stack class

#include "Stack.h"
#include <iostream>
Stack::Stack(int limit) {
	TOP = -1;
	MAX_LIMIT = limit;
	elements = new int(MAX_LIMIT);
}

Stack::~Stack() {
	delete[] elements;
}

bool Stack::isEmpty() const {
	return TOP == -1;
}

bool Stack::isFull() const {
	return TOP == MAX_LIMIT - 1;
}

void Stack::push(int data) {
	if (isFull()) {
		std::cerr << "Error: Stack is full\n";
		return;
	}
	TOP++;
	elements[TOP] = data;
}

int Stack::pop() {
	if (isEmpty()) {
		std::cerr << "Error: Stack is empty\n";
		return -1;
	}
	int data = elements[TOP];
	TOP--;
	return data;
}

int Stack::top() const {
	if (isEmpty()) {
		std::cerr << "Error: Stack is empty\n";
		return -1;
	}
	return elements[TOP];
}

int Stack::count() const
{
	return TOP;
}

void Stack::reverse() {
	int arr[20]{};
	int j = 0, i = 0;
	while (!isEmpty()) {
		int element = top();
		pop();
		arr[i++] = element;
	}
	while (j < i) {
		int element = arr[j++];
		push(element);
	}
}