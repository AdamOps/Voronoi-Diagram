#include <iostream>

#include "Draw.h"

void drawAll(sf::RenderWindow* window, parameters* settings, std::vector<site>* siteVector, sweepLine* line, beachLine* beach) {
	window->clear();

	for (int i = 0; i < siteVector->size(); i++) {
		window->draw(siteVector->at(i).siteShape);
	
		// Only update and draw parabolic arcs if the corresponding site is above the sweeping line. 
		if (siteVector->at(i).getY() < line->getY()) {
			siteVector->at(i).useArc();
			siteVector->at(i).updateArc(settings, line);
			if (settings->drawArcs) {
				window->draw(siteVector->at(i).siteArc);
			}
		}
		else {
			siteVector->at(i).skipArc();
		}
	}

	// Draw the beach line, if the draw toggle is on.
	beach->updateBeachLine(siteVector, settings);
	if (settings->drawBeach) {
		window->draw(beach->beachLineArray);
	}

	// The sweeping line is updated based on the mouse position
	line->updatePos(window);
	window->draw(line->sweepLineShape);

	window->display();
}