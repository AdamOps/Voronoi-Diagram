#include "Draw.h"

void drawAll(sf::RenderWindow* window, parameters* settings, std::vector<site>* siteVector, sweepLine* line) {
	window->clear();

	for (int i = 0; i < siteVector->size(); i++) {
		window->draw(siteVector->at(i).siteShape);

		
		if (siteVector->at(i).getY() < line->getY()) {
			siteVector->at(i).updateArc(settings, line);
			window->draw(siteVector->at(i).siteArc);
		}
		
	}

	line->updatePos(window);

	window->draw(line->sweepLineShape);

	window->display();
}