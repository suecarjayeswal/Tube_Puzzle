#pragma once
#include "TubeSet.h"

class Node {
public:
	TubeSet data;
	Node* next;

	Node(TubeSet d) {
		data = d;
		next = nullptr;
	}
	Node(TubeSet* d) {
		data = TubeSet(d);
		next = nullptr;
	}
	~Node() {
		delete next;
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
	void enqueue(TubeSet* data);
	void dequeue();
	TubeSet peekFront() const;
	TubeSet peekRear() const;
};




