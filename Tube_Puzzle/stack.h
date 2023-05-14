// stack header file
#pragma once
#define _CRT_SECURE_NO_WARNINGS 1 
#define _WINSOCK_DEPRECATED_NO_WARNINGS 1 
#include <iostream>
#include <wx/wx.h>
class Stack {
public:
	Stack();
	Stack(int limit); // Constructor
	Stack(Stack* data); // Constructor
	~Stack(); // Destructor

	Stack** copyColStack(Stack** one, Stack** two, int no_col);

	bool isEmpty() const; // Check if stack is empty
	bool isFull() const; // Check if stack is full
	void push(int data); // Push element to top of stack
	int pop(); // Remove and return element from top of stack
	int top() const; // Get value of top element without removing it
	int count() const; // Get count of elements
	void reverse(); // Reverse the elements in the stack
	void makeEmpty(); // Make stack empty
	wxString traverse() const; // Traverse the stack and return a string of all elements

	int TUB_MAX_COUNT() const; // Get
private:
	int MAX_LIMIT;// Maximum limit of elements
	int TOP; // Index of the top element in the stack
	int* elements; // Array of elements in the stack
};
