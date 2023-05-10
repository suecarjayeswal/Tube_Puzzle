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
	TubeSet* topTubeArray() const;
	Stack** topColStack() const;
	int count() const;
	void makeEmpty();


private:
	class sNode {
	public:
		sNode( TubeSet* data, Stack** other,int no_col, sNode* next = nullptr) {
			// wxLogDebug("Entered sNode Construc%p Tubeset%p Stack%p noCol%d", this, data, other, no_col);
			this->tubeArray = new TubeSet(data);
			this->next = next;
			Stack jpt;
			colStack = jpt.copyColStack(colStack, other,no_col);

			// wxLogDebug("sNode Constr this;tube%p colsta%p",tubeArray,colStack);
			
		}

		~sNode()
		{
			// wxLogDebug("--------------------entered sNode Destruc%p tube%p Stack%p", this, tubeArray, colStack);;
			delete tubeArray;
			delete colStack;
		}
		TubeSet* tubeArray;
		sNode* next;
		Stack** colStack;
	};

	sNode* head;
	int count_;
	int COL_MAX_COUNT;
};

