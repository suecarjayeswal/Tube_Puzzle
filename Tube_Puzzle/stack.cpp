// Stack.cpp - Implementation file for stack class

#include "Stack.h"
#include <iostream>
#include <wx/wx.h>
/**
 * This is the constructor for a Stack class that initializes the top index to -1, sets the maximum limit to 10, and
 * initializes the elements array to nullptr.
 */
Stack::Stack() {
	TOP = -1;
	MAX_LIMIT = 10;
	elements = nullptr;
}

/**
 * This is a constructor for a Stack class that initializes the top index and maximum limit of the stack and creates an
 * array to store the elements.
 *
 * @param limit The parameter "limit" is an integer value that represents the maximum number of elements that can be stored
 * in the stack. It is used to initialize the "MAX_LIMIT" variable and allocate memory for the "elements" array.
 */
Stack::Stack(int limit) {

	TOP = -1;
	MAX_LIMIT = limit;
	elements = new int[MAX_LIMIT];
}

/**
 * This is a constructor for the Stack class that creates a new Stack object with the same properties as an existing Stack
 * object.
 *
 * @param data The parameter `data` is a pointer to an object of the `Stack` class. It is being used to initialize the new
 * `Stack` object being created with the same values as the `data` object.
 */
Stack::Stack(Stack* data)
{
	TOP = data->TOP;
	MAX_LIMIT = data->MAX_LIMIT;
	elements = new int[MAX_LIMIT];
	for (int i = 0; i < MAX_LIMIT; i++) {
		elements[i] = data->elements[i];
	}
}


/**
 * This is a destructor for the Stack class that deletes the elements of the stack.
 */
Stack::~Stack() {
	delete elements;
}

/**
 * The function copies a stack of columns from one array to another in C++.
 *
 * @param one one is a pointer to a pointer of Stack objects. It is the destination array where the copied Stack objects
 * will be stored.
 * @param two The parameter "two" is a pointer to an array of pointers to Stack objects.
 * @param no_col no_col is an integer parameter that represents the number of columns in a two-dimensional array of Stack
 * objects.
 *
 * @return The function `copyColStack` is returning a pointer to a `Stack` object, which is a pointer to an array of
 * `Stack` objects.
 */
Stack** Stack::copyColStack(Stack** one, Stack** two,int no_col)
{
	one = new Stack * [no_col];
	for (int Index = 0; Index < no_col; Index++)
	{
		one[Index] = new Stack(two[Index]);
	}
	return one;
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

	while (j <i) {
		int element = arr[j++];
		push(element);
	}
}

void Stack::makeEmpty()
{
	while (!isEmpty()) {
		pop();
	}
}
wxString Stack::traverse() const
{
	wxString str = wxString::Format(" ");
	for (int Index = TOP; Index >= 0; Index--)
	{
		char buffer[16];
		sprintf_s(buffer, "%d", elements[Index]);
		if (str.length() > 1)
			str.Append(" ");
		str.Append(buffer);
	}
	return str;
}

int Stack::TUB_MAX_COUNT() const
{
	return MAX_LIMIT;
}

