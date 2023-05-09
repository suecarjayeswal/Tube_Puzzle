#pragma once
#include "TubeSet.h"
#include "stack.h"
class ActionStack {
public:
	ActionStack();
	~ActionStack();

	bool isEmpty() const;
	void push( TubeSet* data, Stack** other,int no_col) ;
	TubeSet* pop();
	TubeSet* top() const;
	int count() const;
	void makeEmpty();

private:
	class Node {
	public:
		Node( TubeSet* data, Stack** other,int no_col, Node* next = nullptr) {
			this->tubeArray = new TubeSet(data);
			this->next = next;
			colStack = new Stack * [no_col];
			for (int Index = 0; Index < no_col; Index++)
			{
				colStack[Index] = new Stack(other[Index]);
			}
			
		}
		~Node()
		{
			delete tubeArray;
			delete colStack;
		}
		TubeSet* tubeArray;
		Node* next;
		Stack** colStack;
	};

	Node* head;
	int count_;
};

