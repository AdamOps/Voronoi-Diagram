#pragma once
#include <vector>
#include <iostream>

#include "Shapes.h"

class voronoiEvent {
public:

	voronoiEvent(site& newEvent) {
		x = newEvent.getX();
		y = newEvent.getY();
		circleEvent = newEvent.isCircle();
	}

	voronoiEvent(circle& newEvent) {
		x = newEvent.getX();
		y = newEvent.getY();
		circleEvent = newEvent.isCircle();
	}

	float getY() { return this->y; }
	float getX() { return this->x; }
	bool isCircle() { return this->circleEvent; }
	void printEvent() { std::cout << "y = " << this->y << std::endl; }

private:
	float x, y;
	bool circleEvent;
};


class voronoiEventQueue {
public:
	voronoiEventQueue() {

	};

	void push(voronoiEvent& newEvent);
	voronoiEvent pop();
	voronoiEvent peek();
	void erase(int index);
	void heapifyUp(int index);
	void heapifyDown(int index);

	int getParent(int index) { return ((index - 1) / 2); }
	int getLeftChild(int index) { return (2 * index + 1); }
	int getRightChild(int index) { return (2 * index + 2); }

	int getSize() { return eventQueue.size(); }
	bool isEmpty() { return eventQueue.empty(); }

	void printQueue();

private:
	std::vector<voronoiEvent> eventQueue;
};
