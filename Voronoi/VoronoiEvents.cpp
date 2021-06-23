#include <SFML/Graphics.hpp>
#include <iostream>

#include "Shapes.h"
#include "VoronoiEvents.h"
#include "Parameters.h"

void voronoiEventQueue::push(voronoiEvent& newEvent) {
	eventQueue.push_back(newEvent);

}

voronoiEvent voronoiEventQueue::pop() {
	return eventQueue.at(0);
}

void voronoiEventQueue::erase(int index) {

}

void voronoiEventQueue::heapifyUp(int index) {

}

void voronoiEventQueue::heapifyDown(int index) {

}