#include "Queue.h"
#include "TubeSet.h"

Queue::Queue() {
	front = nullptr;
	rear = nullptr;
	count = 0;
}

Queue::~Queue() {
	while (!isEmpty()) {
		dequeue();
	}
}

bool Queue::isEmpty() const {
	return (count == 0);
}

int Queue::size() const {
	return count;
}

void Queue::enqueue(TubeSet* data) {
	Node* newNode = new Node(data);
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
	if (isEmpty()) {
		return;
	}
	Node* temp = front;
	front = front->next;
	delete temp;
	count--;
}

TubeSet Queue::peekFront() const {
	if (isEmpty()) {
		return TubeSet();
	}
	return front->data;
}

TubeSet Queue::peekRear() const {
	if (isEmpty()) {
		return TubeSet();
	}
	return rear->data;
}
