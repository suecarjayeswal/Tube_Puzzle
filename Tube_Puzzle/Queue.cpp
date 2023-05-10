#include "Queue.h"
#include "TubeSet.h"

Queue::Queue() {
	front = nullptr;
	rear = nullptr;
	count = 0;
	// wxLogDebug("Entered queue defConstructor %p front%p rear%p", this,front,rear);
}

Queue::~Queue() {
	// wxLogDebug("-----------------inside queue destructor %p front%p rear%p", this,front,rear);
	while (!isEmpty()) {
		// wxLogDebug("---------------Entered queue defConstructor isEmpty", this);
		dequeue();
	}
}

bool Queue::isEmpty() const {
	return (count == 0);
}

int Queue::size() const {
	return count;
}

void Queue::enqueue(TubeSet* data, Stack** other, int no_col) {
	// wxLogDebug("  Inside enqueue%p tube%p Stack%p NoCO%d",this,data,other,no_col);
	// wxLogDebug("%s",data->traverseTubeSet());
	Node* newNode = new Node(data,other,no_col);
	//// wxLogDebug("%s", newNode->data->traverseTubeSet());
	if (isEmpty()) {
		front = newNode;
	}
	else {
		rear->next = newNode;
	}
	rear = newNode;
	count++;
}

void Queue::dequeue() {
	// wxLogDebug("inside dequeue %p", this);
	if (isEmpty()) {
		return;
	}
	Node* temp = front;
	front = front->next;
	// wxLogDebug("inside dequeue temp%p front%p",temp,front);
	delete temp;
	count--;
}

void Queue::makeEmpty() {
	while (!isEmpty()) {
		dequeue();
	}
}


TubeSet* Queue::peekFrontTubeArray() const {
	if (isEmpty()) {
		return nullptr;
	}
	TubeSet* data = new TubeSet(front->tubeArray);
	return data;
}

TubeSet* Queue::peekRearTubeArray() const {
	if (isEmpty()) {
		return nullptr;
	}
	TubeSet* data = new TubeSet(rear->tubeArray);
	return data;
}

Stack** Queue::peekFrontColStack() const
{
	if (isEmpty()) {
		return nullptr;
	}
	int no_cols = getNoCol();
	Stack** tmp = new Stack * [no_cols];
	for (int i = 0;i < no_cols;i++) {
		tmp[i] = new Stack(front->colStack[i]);
	}
	return tmp;
}
Stack** Queue::peekRearColStack() const
{
	if (isEmpty()) {
		return nullptr;
	}
	int no_cols = getNoCol();
	Stack** tmp = new Stack * [no_cols];
	for (int i = 0;i < no_cols;i++) {
		tmp[i] = new Stack(rear->colStack[i]);
	}
	return tmp;
}

int Queue::getNoCol() const
{
	return front->no_col;
}
