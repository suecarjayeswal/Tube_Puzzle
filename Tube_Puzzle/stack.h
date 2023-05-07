#pragma once
// Stack.h - Header file for stack class
#include <iostream>
class Stack
{
public:
	Stack();            // Constructor
	~Stack();           // Destructor
	void push(int data);    // Push an element onto the stack
	void pop();         // Pop an element off the stack
	int top() const;    // Return the top element of the stack
	bool isEmpty() const;   // Check if the stack is empty
	void traverse() const;  // Traverse and print all elements in the stack
	void reverseStack();
	//std::string traverse();
private:
	struct Node
	{
		int data;
		Node* next;
	};

	Node* head;         // Pointer to the top of the stack
};


