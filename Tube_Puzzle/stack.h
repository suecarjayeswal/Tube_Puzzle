#pragma once
#include <iostream>
class Stack {
public:
	Stack(int limit); // Constructor
	~Stack(); // Destructor
	bool isEmpty() const; // Check if stack is empty
	bool isFull() const; // Check if stack is full
	void push(int data); // Push element to top of stack
	int pop(); // Remove and return element from top of stack
	int top() const; // Get value of top element without removing it
	int count() const; // Get count of elements
	void reverse(); // Reverse the elements in the stack
	//std::string traverse() const; // Traverse the stack and return a string of all elements
private:
	int MAX_LIMIT;// Maximum limit of elements
	int TOP; // Index of the top element in the stack
	int* elements; // Array of elements in the stack
};
