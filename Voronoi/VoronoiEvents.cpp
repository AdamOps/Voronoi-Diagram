#include <SFML/Graphics.hpp>
#include <algorithm>

#include "Shapes.h"
#include "VoronoiEvents.h"
#include "Parameters.h"

void voronoiEventQueue::push(voronoiEvent& newEvent) {
	eventQueue.push_back(newEvent);
	int index = getSize() - 1;
	heapifyUp(index);
}

voronoiEvent voronoiEventQueue::pop() {
	voronoiEvent toReturn = eventQueue.at(0);
	eventQueue.at(0) = eventQueue.back();
	eventQueue.pop_back();
	heapifyDown(0);
	return toReturn;
}

voronoiEvent voronoiEventQueue::peek() {
	return eventQueue.at(0);
}

void voronoiEventQueue::erase(int index) {
	eventQueue.at(index) = eventQueue.back();
	eventQueue.pop_back();
	heapifyDown(index);
}

void voronoiEventQueue::heapifyUp(int index) {
	if (getParent(index) >= 0) {
		if (eventQueue.at(index).getY() < eventQueue.at(getParent(index)).getY()) {
			std::swap(eventQueue.at(index), eventQueue.at(getParent(index)));
			heapifyUp(getParent(index));
		}
	}
}

void voronoiEventQueue::heapifyDown(int index) {
	int leftIndex = getLeftChild(index);
	int rightIndex = getRightChild(index);

	int smallestIndex = index;
	float currentY = eventQueue.at(index).getY();
	float smallestY = currentY;

	if (leftIndex < getSize()) {
		float leftY = eventQueue.at(leftIndex).getY();
		if (leftY < smallestY) {
			smallestY = leftY;
			smallestIndex = leftIndex;
		}
	}
	if (rightIndex < getSize()) {
		float rightY = eventQueue.at(rightIndex).getY();
		if (rightY < smallestY) {
			smallestY = rightY;
			smallestIndex = rightIndex;
		}
	}

	if (smallestIndex != index) {
		std::swap(eventQueue.at(index), eventQueue.at(smallestIndex));
		heapifyDown(smallestIndex);
	}

}

void voronoiEventQueue::printQueue() {
	for (int i = 0; i < eventQueue.size(); i++) {
		std::cout << "Heap element #" << i << ": " << eventQueue.at(i).getY() << std::endl;
	}
}