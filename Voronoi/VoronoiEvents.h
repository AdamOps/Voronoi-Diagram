#pragma once
#include <vector>
#include "Shapes.h"

class voronoiEvent {
	float y;
	bool circle;

	voronoiEvent(site* newEvent) {
		y = newEvent->getY();
		circle = newEvent->isCircle();
	}

	voronoiEvent(circle* newEvent) {
		y = newEvent->getY();
		circle = newEvent->isCircle();
	}
};


class voronoiEventQueue {

};
