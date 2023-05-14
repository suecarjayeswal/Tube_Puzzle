// Queue header file
#pragma once
#include "TubeSet.h"
#include "stack.h"
class Node {
public:
	TubeSet* tubeArray;
	Stack** colStack;
	Node* next;
	int no_col;
	Node(TubeSet* data, Stack** other, int no_col, Node* next = nullptr) {
		// wxLogDebug("entered qNode Constr%p tube%p stack%p nocol%d",this,data,other,no_col);
		this->tubeArray = new TubeSet(data);
		this->next = next;
		this->no_col = no_col;
		Stack jpt;
		colStack=jpt.copyColStack(colStack, other, no_col);
	}
	/*Node(TubeSet d) {
		tubeArray = new TubeSet(d);
		next = nullptr;
	}
	Node(TubeSet* d) {
		tubeArray = (d);
		next = nullptr;
	}*/
	~Node() {
		// wxLogDebug("---------------entered qNode Destr%p tube%p stack%p",this,tubeArray,colStack);
		delete tubeArray;
		//for (int Index = 0; Index < no_col; Index++)
		//{
		//	delete colStack[Index];
		//}
		//delete[] colStack;
	}
};

class Queue {
private:
	Node* front;
	Node* rear;
	int count;

public:
	Queue();
	~Queue();

	bool isEmpty() const;
	int size() const;
	void enqueue(TubeSet* data, Stack** other, int no_col);
	void dequeue();
	void makeEmpty();
	TubeSet* peekFrontTubeArray() const;
	TubeSet* peekRearTubeArray() const;
	Stack** peekFrontColStack() const;
	Stack** peekRearColStack() const;

	int getNoCol() const;
};




