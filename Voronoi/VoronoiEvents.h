#pragma once
#include <vector>
#include "Shapes.h"

class voronoiEvent {
public:

	voronoiEvent(site* newEvent) {
		y = newEvent->getY();
		circleEvent = newEvent->isCircle();
	}

	voronoiEvent(circle* newEvent) {
		y = newEvent->getY();
		circleEvent = newEvent->isCircle();
	}

	int getIndex() { return index; }
	void setIndex(int index_) { index = index_; }

private:	
	float y;
	bool circleEvent;
	int index;
};


class voronoiEventQueue {
public:
	voronoiEventQueue() {

	};

	void push(voronoiEvent& newEvent);
	voronoiEvent pop();
	void erase(int index);
	void heapifyUp(int index);
	void heapifyDown(int index);

	int getParent(int index) { return ((index - 1) / 2); }
	int getLeftChild(int index) { return (2 * index + 1); }
	int getRightChild(int index) { return (2 * index + 2); }

	int getSize() { return eventQueue.size(); }
	bool isEmpty() { return getSize() == 0; }

private:
	std::vector<voronoiEvent> eventQueue;
};
