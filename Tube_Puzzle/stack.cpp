// Stack.cpp - Implementation file for stack class

#include "Stack.h"
#include <iostream>
// Constructor
Stack::Stack()
{
	head = nullptr;
}

// Destructor
Stack::~Stack()
{
	while (!isEmpty())
	{
		pop();
	}
}

// Push an element onto the stack
void Stack::push(int data)
{
	Node* newNode = new Node;
	newNode->data = data;
	newNode->next = head;
	head = newNode;
}

// Pop an element off the stack
void Stack::pop()
{
	if (isEmpty())
	{
		std::cout << "Error: Stack is empty!\n";
		return;
	}

	Node* temp = head;
	head = head->next;
	delete temp;
}

// Return the top element of the stack
int Stack::top() const
{
	if (isEmpty())
	{
		std::cout << "Error: Stack is empty!\n";
		return -1;
	}

	return head->data;
}

// Check if the stack is empty
bool Stack::isEmpty() const
{
	return head == nullptr;
}

//Traverse and print all elements in the stack
void Stack::traverse() const
{
	if (isEmpty())
	{
		std::cout << "Error: Stack is empty!\n";
		return;
	}

	Node* current = head;
	while (current != nullptr)
	{
		std::cout << current->data << " ";
		current = current->next;
	}
	std::cout << "\n";
}
void Stack::reverseStack() {
	int arr[20];
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
//std::string Stack::traverse() {
//	std::string msg;
//	if (isEmpty())
//	{
//		msg= "Error: Stack is empty!\n";
//		return msg;
//	}
//
//	Node* current = head;
//	while (current != nullptr)
//	{
//		msg = current->data + " ";
//		current = current->next;
//	}
//	msg+= "\n";
//	return msg;
//}
