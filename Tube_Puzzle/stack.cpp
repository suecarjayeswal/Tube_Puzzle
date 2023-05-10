// Stack.cpp - Implementation file for stack class

#include "Stack.h"
#include <iostream>
#include <wx/wx.h>
Stack::Stack() {
	// wxLogDebug("Entered stack defConstructor %p", this);
	TOP = -1;
	MAX_LIMIT = 10;
	elements = nullptr;
}
Stack::Stack(int limit) {
	
	TOP = -1;
	MAX_LIMIT = limit;
	elements = new int[MAX_LIMIT];
	// wxLogDebug("Entered stackLimitConstr%d %p elem%p", limit, this,elements);
}

Stack::Stack(Stack* data)
{
	// wxLogDebug("Entered stack PointConstructorData%p,MAX%d ele%p this%p ele%p \n%s", data,data->MAX_LIMIT,data->elements, this, elements,data->traverse());
	TOP = data->TOP;
	MAX_LIMIT = data->MAX_LIMIT;
	elements = new int[MAX_LIMIT];
	for (int i = 0; i < MAX_LIMIT; i++) {
		elements[i] = data->elements[i];
		/*if (data->elements[i] > 0) elements[i] = data->elements[i];
		else elements[i] = 0;*/
		// wxLogDebug("\t\t%d %d",elements[i],data->elements[i]);
	}
	// wxLogDebug("Entered later stack PointConstructorData%p %p ele%p",data, this,elements);
}


Stack::~Stack() {
	// wxLogDebug("------------------Entered stack destructr %p ele%p", this, elements);
	delete elements;
}

Stack** Stack::copyColStack(Stack** one, Stack** two,int no_col)
{
	// wxLogDebug("Entered stack colStackCopier one%p two%p noCol%d %p",one,two,no_col, this);
	one = new Stack * [no_col];
	for (int Index = 0; Index < no_col; Index++)
	{
		one[Index] = new Stack(two[Index]);
	}
	// wxLogDebug("colCopier newOne %p", one);
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

