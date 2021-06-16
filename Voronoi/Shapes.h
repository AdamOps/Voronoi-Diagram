#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Parameters.h"

class sweepLine{
public:
	// Public features
	sf::RectangleShape sweepLineShape;

	// Constructors
	sweepLine();
	sweepLine(parameters* settings);

	// Avoid duplication
	sweepLine(const sweepLine&) = delete;

	// Public methods
	float getY() { return y; }

	void setThickness(float thickness);
	void updatePos(sf::RenderWindow* window);

private:
	float y;
};

class site {
public:
	// Public features
	sf::CircleShape siteShape;
	sf::VertexArray siteArc;

	// Constructors
	site();
	site(parameters* settings, int iterator);

	// Public methods
	int getX() { return this->x; }
	int getY() { return this->y; }
	bool getVisibility() { return visibleToBeach; }
	void setX(int x_) { this->x = x_; }
	void setY(int y_) { this->y = y_; }

	void updateArc(parameters* settings, sweepLine* line);
	void useArc() { this->visibleToBeach = true; }
	void skipArc() { this->visibleToBeach = false; }

private:
	int x, y;
	int siteID;
	bool visibleToBeach;
};

class beachLine {
public:
	// Public features
	sf::VertexArray beachLineArray;

	// Constructors
	beachLine();
	beachLine(std::vector<site>* siteVector, parameters* settings);

	// Avoid duplication
	beachLine(const beachLine&) = delete;

	// Public methods
	void updateBeachLine(std::vector<site>* siteVector, parameters* settings);
private:
};

class halfEdge {
public:
	halfEdge();

private:
};