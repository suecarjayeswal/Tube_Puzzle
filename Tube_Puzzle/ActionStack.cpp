#include "ActionStack.h"
#include <iostream>

ActionStack::ActionStack() {
	head = nullptr;
	count_ = 0;
	COL_MAX_COUNT = 0;
	// wxLogDebug("Entered ActionStack defConstructor %p head%p ", this,head);
}

ActionStack::~ActionStack() {
	// wxLogDebug("---------------inside ActionStack Destructor %p",this);
	makeEmpty();

}

bool ActionStack::isEmpty() const {
	return count_ == 0;;
}

void ActionStack::push( TubeSet* data, Stack** other,int no_col) {
	// wxLogDebug("inside ActionStack%p push data%p stack%p noCol%d=================%d", this, data, other, no_col,count());
	sNode* newNode = new sNode(data,other,no_col);
	newNode->next = head;
	head = newNode;
	count_++;
	COL_MAX_COUNT = data->getTotalColNo();
}


TubeSet* ActionStack::pop() {
	// wxLogDebug("inside ActionStack pop%p head%p=================%d",this,head,count());
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

TubeSet* ActionStack::topTubeArray() const {
	if (isEmpty()) {
		std::cerr << "Error: Stack is empty\n";
		return nullptr;
	}
	return head->tubeArray;
}

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
