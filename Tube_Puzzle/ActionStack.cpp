// ActionStack Implemtation  file
#include "ActionStack.h"
#include <iostream>

/**
 * This is the default constructor for the ActionStack class in C++, which initializes the head pointer to null, sets the
 * count to 0, and sets the COL_MAX_COUNT to 0.
 */
ActionStack::ActionStack() {
	head = nullptr;
	count_ = 0;
	COL_MAX_COUNT = 0;
}

/**
 * This is the destructor for the ActionStack class in C++, which calls the makeEmpty() function to clear the stack.
 */
ActionStack::~ActionStack() {
	makeEmpty();

}

bool ActionStack::isEmpty() const {
	return count_ == 0;
}

/**
 * This function pushes a new node onto the top of the ActionStack with the given TubeSet data, Stack pointer, and number
 * of columns.
 *
 * @param data a pointer to a TubeSet object that will be added to the stack as the new top element.
 * @param other The "other" parameter is a pointer to a pointer of type Stack. It is used to keep track of the previous
 * state of the stack before the current push operation. This is useful for implementing undo/redo functionality, where the
 * user can go back and forth between different states of the stack.
 * @param no_col The parameter "no_col" is an integer that represents the number of columns in a TubeSet object. It is used
 * to set the maximum column count for the ActionStack object.
 */
void ActionStack::push( TubeSet* data, Stack** other,int no_col) {
	sNode* newNode = new sNode(data,other,no_col);
	newNode->next = head;
	head = newNode;
	count_++;
	COL_MAX_COUNT = data->getTotalColNo();
}


/**
 * This function pops an element from a stack and returns a pointer to a TubeSet object.
 *
 * @return A pointer to a TubeSet object.
 */
TubeSet* ActionStack::pop() {
	if (isEmpty()) {
		std::cerr << "Error: Stack is empty\n";
		return nullptr;
	}
	sNode* temp = head;
	head = head->next;
	TubeSet* data = new TubeSet(temp->tubeArray);
	delete temp;
	count_--;
	// wxLogDebug("inside later ActionStackpop data%p m_arr", data);
	return data;
}

/**
 * The function returns a pointer to the top element of the stack as a new TubeSet object.
 *
 * @return A pointer to a new `TubeSet` object that is a copy of the `tubeArray` of the `head` node of the stack.
 */
TubeSet* ActionStack::topTubeArray() const {
	if (isEmpty()) {
		std::cerr << "Error: Stack is empty\n";
		return nullptr;
	}
	TubeSet* data = new TubeSet(head->tubeArray);
	return data;
}

/**
 * The function returns a pointer to an array of pointers to Stack objects, each containing a copy of the column stacks in
 * the top node of the ActionStack.
 *
 * @return A dynamically allocated array of pointers to Stack objects, where each pointer points to a copy of the
 * corresponding column stack in the top element of the ActionStack.
 */
Stack** ActionStack::topColStack() const
{
	if (isEmpty()) {
		std::cerr << "Error: Stack is empty\n";
		return nullptr;
	}
	Stack** tmp = new Stack * [COL_MAX_COUNT];
	for (int i = 0;i < COL_MAX_COUNT;i++) {
		tmp[i] = new Stack(head->colStack[i]);
	}
	return tmp;
}

int ActionStack::count() const {
	return count_;
}

/**
 * The function "makeEmpty" deletes all nodes in a linked list until the list is empty.
 */
void ActionStack::makeEmpty() {
	// wxLogDebug("inside ActionStack makeEmpty %p head %p", this,head);
	while (!isEmpty()) {
		sNode* temp = head;
		// wxLogDebug("inside makeEmpty:tmp%p-head-%p to delete %p",temp,head, temp->tubeArray);
		head = head->next;
		delete temp;
		count_--;
	}
}
